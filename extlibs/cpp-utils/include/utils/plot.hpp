#ifndef UTILS_PLOT_HPP
#define UTILS_PLOT_HPP

#include <cstdio>
#include <cstdlib>

#include <string>
#include <fstream>
#include <vector>
#include <stdexcept>

namespace utils
{
    /**
     * \brief a namspace for ploting class
     */
    namespace plot
    {
        class Gnuplot;
        class Graph;
        /**
         * \brief internal serie representation.
         * Each serie is stor in a separate tmp file
         */
        class Serie
        {
            public:

                /**
                 * \brief could throw a std::runtime_error
                 * \param title the serie title
                 */
                explicit Serie(const std::string& title="");

                ~Serie();

                enum class Style
                {
                    points,
                    lines, //< default
                    linespoints,
                    impulses,
                    dots,
                    steps,
                    errorbars,
                    boxes,
                    boxerrorbars,
                };

                /**
                 * \return the title
                 */
                const std::string& title()const;

                /**
                 * \brief ste the title
                 */
                void title(const std::string&);

                /**
                 * \return the style
                 * Note : default is lines
                 */
                Style style()const;

                /**
                 * \brief set the style
                 * Note : default is lines
                 */
                void style(Style);

                /**
                 * \return the style as string
                 */
                std::string style_str()const;

                /**
                 * \brief add one point to the graph
                 */
                template<typename X,typename Y>
                void addPoint(X&& x,Y&& y);

                /**
                 * \brief add multiple points
                 * \param x must be a container
                 * \param y must be a container
                 */
                template<typename X,typename Y>
                void addPoints(X&& x,Y&& y);

                /**
                 * \add a value to the inner file
                 */
                template<typename T>
                friend Serie& operator<<(Serie& self,const T& value);


                /**
                 * \add a value to the inner file
                 */
                template<typename T>
                friend Serie& operator<<(Serie& self,T&& value);

                /**
                 * \return tru if the filestream is open
                 */
                bool isOpen()const;

                /**
                 * \brief open th file stream
                 * \return true on success
                 */
                bool open(std::ofstream::openmode mode = std::ofstream::out | std::ofstream::app);

                /***
                 * \brief close the file stream
                 */
                void close();


            private:
                friend class Graph;

                std::string _title; //< title
                std::ofstream _out; //< output file
                Style _style; //< style
                std::string _filename; ///< filename

                /**
                 * \brief plot the serie
                 */
                friend Gnuplot& operator<<(Gnuplot& plot,const Serie& self);
        };

        /**
         * \brief a class to manage a graph
         */
        class Graph
        {
            public:
                /**
                 * \brief construct a graph of title title
                 */
                Graph(const std::string& title="");
                ~Graph();

                /**
                 * \return the title
                 */
                const std::string& title()const;

                /**
                 * \brief set the title
                 */
                void title(const std::string&);

                /**
                 * \return the style
                 * Note : default is lines
                 */
                Serie::Style style()const;

                /**
                 * \brief set the style to all series.
                 * Note : default is lines
                 */
                void style(Serie::Style);

                /**
                 * \return the number of series
                 */
                unsigned int size()const;

                /**
                 * \return the serie in index i
                 */
                Serie& operator[](unsigned int i);

                /**
                 * \return the serie in index i
                 */
                const Serie& operator[](unsigned int)const;

                /**
                 * \return the first serie with title=title
                 */
                Serie& operator[](const std::string& title);

                /**
                 * \return the first serie with title=title
                 */
                const Serie& operator[](const std::string& title)const;

                /**
                 * \brief remove serie in index i.
                 * All the other series with index > i will be move by -1
                 * \return true on success
                 */
                bool remove(unsigned int i);

                /**
                 * \brief remove the first serie with title=tilte.
                 * All the other series with index > i will be move by -1
                 * \return true on success
                 */
                bool remove(const std::string& title);

                /**
                 * \brief construct a new serie
                 * \param args is forward to Serie constructor
                 */
                template<typename ... Args>
                bool add(Args&& ... args);

                /**
                 * \brief add point to the first serie.
                 * Create a new serie if there is no.
                 * \param args forward to serie.addPoint
                 * \return true on success
                 */
                template<typename ... Args>
                bool addPoint(Args&& ... args);

                /**
                 * \brief add points to the first serie.
                 * Create a new serie if there is no.
                 * \param args forward to serie.addPoints
                 * \return true on success
                 */
                template<typename ... Args>
                bool addPoints(Args&& ... args);


            private:
                friend class Gnuplot;

                std::string _title; //< title
                std::vector<Serie*> _series; //< inner series
                Serie::Style _style; ///< style

                friend Gnuplot& operator<<(Gnuplot& plot,const Graph& self); //< plot the graph

        };

        /**
         * \brief a class to deal with gnuplot.
         * You must have gnuplot install in your system and in the PATH.
         * on linux do not forget to install gnuplot-X11
         * Internaly use pipe to communicate with gnuplot
         */
        class Gnuplot
        {
            public:
                
                /**
                 * \brief creati a pipe with gnuplot
                 */
                Gnuplot();
                ~Gnuplot();

                /**
                 * \brief send a direct command to gnuplot.
                 * Using a plot command will result in undefine beavior
                 * Note : the pipe is flush
                 */
                template<typename ... Args>
                void cmd(Args&& ... args);
                
                /**
                 * \brief flush the pipe
                 */
                void flush();

                /**
                 * \brief delete all the iner graphs
                 */
                void clear();

                /**
                 * \return true if the pipe is open
                 */
                bool isOpen()const;

                /**
                 * \brief open the pipe.
                 * Note : this function is call in the constructor
                 */
                bool open();

                /**
                 * \brief close thre pipe
                 * Note : this function is call in the destructor
                 */
                bool close();

                /**
                 * \brief send value to gnuplot pipe. same as .cmd()
                 * Note : thi pipe is not flush
                 */
                template<typename T>
                friend Gnuplot& operator<<(Gnuplot& self,const T& value);

                /**
                 * \brief draw all the inner graph
                 */
                void draw();


                /**
                 * \brief draw the first grapth with title title
                 */
                void draw(const std::string& graph);

                enum class Mod{
                    MULTI, //< default. use mltiplot
                    WINDOW, //< each graph is plot in a separate window
                    HYBRID //< each graph is plot in a separate window + a window with all
                };

                /**
                 * \return the draw mod
                 * default is MULTI
                 */
                Mod mod()const;

                /**
                 * \brief set the mod
                 * default is MULTI
                 */
                void mod(Mod mod);


                /**
                 * \brief construct a new graph
                 * \param args is forward to Graph constructor
                 */
                template<typename ... Args>
                bool add(Args&& ... args);

                /**
                 * \brief remove graph in index i.
                 * All the other graph with index > i will be move by -1
                 * \return true on success
                 */
                bool remove(unsigned int);

                /**
                 * \brief remove the first graph with title*title.
                 * All the other graph with index > i will be move by -1
                 * \return true on success
                 */
                bool remove(const std::string& title);

                /**
                 * \return the graph in index i
                 */
                Graph& operator[](unsigned int i);

                /**
                 * \return the graph in index i
                 */
                const Graph& operator[](unsigned int)const;

                /**
                 * \return the first graph with title=title
                 */
                Graph& operator[](const std::string& title);

                /**
                 * \return the first graph with title=title
                 */
                const Graph& operator[](const std::string& title)const;

                /**
                 * \return the number of graph
                 */
                unsigned int size()const;

            private:
                FILE* pipe; //< pipe to communicate with gnuplot
                std::vector<Graph*> _graphs; //< graphs

                Mod _mod; //< mod

                /**
                 * \brief draw the graph in index graph
                 */
                void draw(unsigned int graph);

                void draw_multi(unsigned int window);
                void draw_window(unsigned int window_start);
        };
    }
}
#include <utils/plot.tpl>
#endif
