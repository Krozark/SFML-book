#ifndef UTILS_MATHS_HPP
#define UTILS_MATHS_HPP

#include <functional>

namespace utils
{
    /**
     * \brief regroup some math utility
     */
    namespace maths
    {
        /**
         * \return -1 if < T(0), 1 if > T(0) else 0
         */
        template <typename T>
        int sign(T val);

        /**
         * \return a if a<, else b
         */
        template <typename T>
        inline const T& min(const T& a,const T& b);

        /**
         * \brief call min(a,b) recusivly
         */
        template <typename T, typename ... Args>
        inline const T& min(const T& a,const T& b,const T& c,const Args& ... args);

        /**
         * \return a if a>b else b
         */
        template <typename T>
        inline const T& max(const T& a,const T& b);

        /**
         * \brief call max(a,b) recusivly
         */
        template <typename T, typename ... Args>
        inline const T& max(const T& a,const T& b, const Args& ... args);

        /**
         * \return the abolute value of a
         */
        template <typename T>
        inline T abs(const T& a);

        template <typename T>
        inline T clamp(T value, T min, T max);

        /**
         * \brief usage power<N>::of(number)
         * \return the power on number at N
         */
        template <int N>
        struct power;


        /**
         * \brief call discretize<T>(tab.begin(),tab.end(),f) 
         */
        template<typename T>
        T discretize(const T& tab,std::function<double(double)> f);

        /**
         * \brief f is a repartition function defined between [-1 .. 1], an must return a result > 0
         * the index between first, last are convert in a [-1 .. 1] value passed to f. The result
         * of f is store in a cumulator.
         * Each time that the cumulator is >= 1, the value is append to the new T.
         */
        template<typename T,typename Iterator>
        T discretize(Iterator first,Iterator last,std::function<double(double)> f);

        namespace ker
        {
            //unaire
            inline double uniform(double _1);

            inline double triangular(double _1);

            inline double epanechnikov(double _1);

            inline double quartic(double _1);

            inline double triweight(double _1);

            inline double tricube(double _1);

            inline double gaussian(double _1,double _2=1,double _3=0);

            inline double cosine(double _1);

            //binary
            inline double mul(double _1,double _2);

            inline double div(double _1,double _2);

            inline double add(double _1,double _2);

            inline double sub(double _1,double _2);
        }
    }
}
#include <utils/maths.tpl>
#endif
