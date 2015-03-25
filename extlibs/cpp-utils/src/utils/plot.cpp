#include <utils/plot.hpp>
#include <utils/sys.hpp>

#include <string.h>
#include <cmath>

#ifdef _WIN32
#include <io.h>
#include <stdio.h>
#else
#include <unistd.h>
#endif

namespace utils
{
    namespace plot
    {
        /********* Serie **************/
        Serie::Serie(const std::string& title) : _title(title), _style(Style::lines)
        {
            if(utils::sys::dir::create("./plot") == 0)
                throw std::runtime_error("Unable to create tempory dir plot");


            #ifdef _WIN32
            char tmpname[] = "./plot/serie_XXXXXX";
            if(::_mktemp(tmpname)==0)
            {
            #else
            char *tmpname = ::strdup("./plot/serie_XXXXXX");
            int fd = ::mkstemp(tmpname);
            if(fd == -1)
            {
                ::free(tmpname);
            #endif
                throw std::runtime_error("Unable to create tempory file");
            }

            _filename = tmpname;
            _out.open(_filename);
            #ifndef _WIN32
            ::free(tmpname);
            ::close(fd);
            #endif
        }

        Serie::~Serie()
        {
            _out.close();
            utils::sys::file::rm(_filename);
        }

        const std::string& Serie::title()const
        {
            return _title;
        }

        void Serie::title(const std::string& title)
        {
            _title = title;
        }

        Serie::Style Serie::style()const
        {
            return _style;
        }

        void Serie::style(Serie::Style style)
        {
            _style = style;
        }

        std::string Serie::style_str()const
        {
            switch(_style)
            {
                case Style::points : return {"points"};
                case Style::lines : return {"lines"};
                case Style::linespoints : return {"linespoints"};
                case Style::impulses : return {"impulses"};
                case Style::dots : return {"dots"};
                case Style::steps : return {"steps"};
                case Style::errorbars : return {"errorbars"};
                case Style::boxes : return {"boxes"};
                case Style::boxerrorbars : return {"boxerrorbars"};
            }
            return {"points"};
        }

        Gnuplot& operator<<(Gnuplot& plot,const Serie& self)
        {
            plot<<"\""<<self._filename<<"\"";
            if(not self._title.empty())
                plot<<" title \""<<self._title<<"\"";
            plot<<" with "<<self.style_str();
            return plot;
        }

        bool Serie::isOpen()const
        {
            return _out.is_open();
        }

        bool Serie::open(std::ofstream::openmode mode)
        {
            if(_out.is_open())
                return false;
            _out.open(_filename,mode);
            return _out.good();
        }

        void Serie::close()
        {
            return _out.close();
        }

        /************* Graph *****************/
        Graph::Graph(const std::string& title) : _title(title), _style(Serie::Style::lines)
        {
        }

        Graph::~Graph()
        {
            for(Serie* s : _series)
                delete s;
        }

        const std::string& Graph::title()const
        {
            return _title;
        }

        void Graph::title(const std::string& title)
        {
            _title = title;
        }

        Serie::Style Graph::style()const
        {
            return _style;
        }

        void Graph::style(Serie::Style style)
        {
            _style = style;
            const unsigned int _size = _series.size();
            for(unsigned int i=0;i<_size;++i)
                _series[i]->style(_style);
        }

        unsigned int Graph::size()const
        {
            return _series.size();
        }

        Serie& Graph::operator[](unsigned int i)
        {
            return *_series[i];
        }

        const Serie& Graph::operator[](unsigned int i)const
        {
            return *_series[i];
        }

        Serie& Graph::operator[](const std::string& title)
        {
            Serie* serie=nullptr;
            const unsigned int _size = _series.size();
            for(unsigned int i=0;i<_size;++i)
            {
                if(_series[i]->_title==title)
                {
                    serie = _series[i];
                    break;
                }
            }
            return *serie;
        }

        const Serie& Graph::operator[](const std::string& title) const
        {
            Serie* serie=nullptr;
            const unsigned int _size = _series.size();
            for(unsigned int i=0;i<_size;++i)
            {
                if(_series[i]->_title==title)
                {
                    serie = _series[i];
                    break;
                }
            }
            return *serie;
        }

        bool Graph::remove(unsigned int i)
        {
            delete _series[i];
            _series.erase(_series.begin()+i);
            return true;
        }

        bool Graph::remove(const std::string& title)
        {
            bool res = false;
            const unsigned int _size = _series.size();
            for(unsigned int i=0;i<_size;++i)
            {
                if(_series[i]->_title==title)
                {
                    res = this->remove(i);
                    break;
                }
            }
            return res;
        }

        Gnuplot& operator<<(Gnuplot& plot,const Graph& self)
        {
            unsigned int _size = self._series.size();
            if(_size>0)
            {
                plot<<"set key ins vert\n"
                    <<"set key bot right\n";

                if(not self._title.empty())
                    plot<<"set title \""<<self._title<<"\"\n";

                plot<<"plot "<<*self._series[0];
                for(unsigned int i=1;i<_size;++i)
                    plot<<", "<<*self._series[i];
                plot<<"\n";
                plot.flush();
            }
            return plot;
        }


        /********** Gnuplot ********************/
        Gnuplot::Gnuplot() : pipe(nullptr), _mod(Mod::MULTI)
        {
            open();
        }

        Gnuplot::~Gnuplot()
        {
            for(Graph* g : _graphs)
                delete g;
            close();
        }

        void Gnuplot::flush()
        {
            if(pipe!=nullptr)
                ::fflush(pipe);
        }


        void Gnuplot::clear()
        {
            for(Graph* g: _graphs)
                delete g;
            _graphs.clear();
            (*this)<<"reset\nclear\n";
        }

        bool Gnuplot::isOpen()const
        {
            return pipe != nullptr;
        }

        bool Gnuplot::open()
        {
            if(pipe != nullptr)
                return false;

            #ifdef WIN32
            pipe = ::_popen("gnuplot.exe", "w");
            #else
            pipe = ::popen("gnuplot", "w");
            #endif

            if(pipe == nullptr)
            {
                throw std::runtime_error("gnuplot not found. Is gnuplot"
                #ifdef WIN32
                ".exe"
                #endif
                " in your path?");
            }
            return true;
        }

        bool Gnuplot::close()
        {
            if(pipe == nullptr or
            #ifdef WIN32
            ::_pclose(pipe)
            #else
            ::pclose(pipe)
            #endif
            == -1)
                return false;
            pipe= nullptr;
            return true;
        }


        void Gnuplot::draw()
        {

            (*this)<<"reset\nclear\n";
            //set mod
            if(_mod == Mod::MULTI)
            {
                draw_multi(0);
            }
            else if (_mod == Mod::WINDOW)
            {
                draw_window(0);
            }
            else //HYBRID
            {
                draw_window(0);
                draw_multi(_graphs.size());
            }
        }

        void Gnuplot::draw_multi(unsigned int window)
        {
            const unsigned int _size = _graphs.size();
            float sq = sqrt(_size);
            (*this)<<"set term wxt title \"\""<<window<<"\n";
            (*this)<<"set multiplot layout "<<::round(sq)<<","<<::ceil(sq)<<"\n";
            flush();

            for(unsigned int i=0;i<_size;++i)
                draw(i);

            (*this)<<"unset multiplot\n";
            flush();
        }

        void Gnuplot::draw_window(unsigned int window_start)
        {
            const unsigned int _size = _graphs.size();
            for(unsigned int i=0;i<_size;++i)
            {
                (*this)<<"set term wxt title \""<<_graphs[i]->_title<<"\" "<<i+window_start<<"\n";
                draw(i);
            }
        }

        void Gnuplot::draw(unsigned int i)
        {
            //set mod
            (*this)<<*_graphs[i];
            flush();
        }

        void Gnuplot::draw(const std::string& graph)
        {
            const unsigned int _size = _graphs.size();
            for(unsigned int i=0;i<_size;++i)
            {
                if(_graphs[i]->_title==graph)
                {
                    draw(i);//forward to draw(unsigned int)
                    break;
                }
            }
        }

        Gnuplot::Mod Gnuplot::mod()const
        {
            return _mod;
        }

        void Gnuplot::mod(Gnuplot::Mod mod)
        {
            _mod = mod;
        }

        bool Gnuplot::remove(unsigned int i)
        {
            delete _graphs[i];
            _graphs.erase(_graphs.begin()+i);
            return true;
        }

        bool Gnuplot::remove(const std::string& title)
        {
            bool res = false;
            const unsigned int _size = _graphs.size();
            for(unsigned int i=0;i<_size;++i)
            {
                if(_graphs[i]->_title==title)
                {
                    res = this->remove(i);
                    break;
                }
            }
            return res;
        }

        Graph& Gnuplot::operator[](unsigned int i)
        {
            return *_graphs[i];
        }

        const Graph& Gnuplot::operator[](unsigned int i)const
        {
            return *_graphs[i];
        }

        Graph& Gnuplot::operator[](const std::string& title)
        {
            Graph* res=nullptr;
            const unsigned int _size = _graphs.size();
            for(unsigned int i=0;i<_size;++i)
            {
                if(_graphs[i]->_title==title)
                {
                    res = _graphs[i];
                    break;
                }
            }
            return *res;
        }

        const Graph& Gnuplot::operator[](const std::string& title)const
        {
            Graph* res=nullptr;
            const unsigned int _size = _graphs.size();
            for(unsigned int i=0;i<_size;++i)
            {
                if(_graphs[i]->_title==title)
                {
                    res = _graphs[i];
                    break;
                }
            }
            return *res;
        }

        unsigned int Gnuplot::size()const
        {
            return _graphs.size();
        }

    }
}
