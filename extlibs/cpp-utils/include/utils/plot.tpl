#include <sstream>
#include <iostream>

namespace utils
{
    namespace plot
    {
        /*********** Serie *******************/
        template<typename X,typename Y>
        void Serie::addPoint(X&& x, Y&& y)
        {
            (*this)<<x<<" "<<y<<"\n";
            _out<<std::flush;
        }

        template<typename X,typename Y>
        void Serie::addPoints(X&& x, Y&& y)
        {
            auto begin_x = x.begin();
            const auto end_x = x.end();
            
            auto begin_y = y.begin();
            const auto end_y = y.end();

            while(begin_x != end_x and begin_y != end_y)
            {
                (*this)<<(*begin_x)<<" "<<(*begin_y)<<"\n";
                ++begin_x;
                ++begin_y;
            }
            _out<<std::flush;
        }

        template<typename T>
        Serie& operator<<(Serie& self,const T& value)
        {
            self._out<<value;
            return self;
        }

        template<typename T>
        Serie& operator<<(Serie& self,T&& value)
        {
            self._out<<value;
            return self;
        }

        /************* Graph ******************/
        template<typename ... Args>
        bool Graph::add(Args&& ... args)
        {
            try{
                _series.emplace_back(new Serie(std::forward<Args>(args)...));
                _series.back()->style(_style);
                return true;
            }catch(std::exception& e){
                return false;
            }
        }

        template<typename ... Args>
        bool Graph::addPoint(Args&& ... args)
        {
            if(this->_series.size()<=0)
                if(not this->add())
                    return false;
            _series[0]->addPoint<Args...>(std::forward<Args>(args)...);
            return true;
        }

        template<typename ... Args>
        bool Graph::addPoints(Args&& ... args)
        {
            if(this->_series.size()<=0)
                if(not this->add())
                    return false;
            _series[0]->addPoints<Args ...>(std::forward<Args>(args)...);
            return true;
        }

        /************* Gnuplot *****************/

        void __cmd_healper(Gnuplot& self)
        {
        }   

        template<typename T,typename ... Args>
        void __cmd_healper(Gnuplot& self,T&& t,Args&& ... args)
        {
            self<<t;
            __cmd_healper(self,std::forward<Args>(args)...);
        }


        template<typename ... Args>
        void Gnuplot::cmd(Args&& ... args)
        {
            __cmd_healper(*this,std::forward<Args>(args)...);
            *this<<"\n";
            flush();
        }

        template<typename T>
        Gnuplot& operator<<(Gnuplot& self,const T& value)
        {
            if(self.isOpen())
            {
                std::stringstream ss;
                ss<<value;
                ::fprintf(self.pipe,"%s",ss.str().c_str());
            }
            return self;
        }

        template<typename ... Args>
        bool Gnuplot::add(Args&& ... args)
        {
            try{
                _graphs.emplace_back(new Graph(std::forward<Args>(args)...));
                return true;
            }catch(std::exception& e){
                return false;
            }
        }
    }
}
