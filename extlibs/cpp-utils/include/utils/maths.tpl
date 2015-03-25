#ifdef _WIN32
#define M_PI           3.14159265358979323846  /* pi */
#define M_PIl          3.141592653589793238462643383279502884L /* pi */
#endif

#include <cmath>
#include <iterator>

namespace utils
{
namespace maths
{
    template <typename T>
    int sign(T val)
    {
        return (T(0) < val) - (val < T(0));
    }

    template <typename T>
    inline const T& min(const T& a,const T& b)
    {
        return (a<b)?a:b;
    }

    template <typename T, typename ... Args>
    inline const T& min(const T& a,const T& b,const T& c, const Args& ... args)
    {
        return min(min(a,b),c,args ...);
    }

    template <typename T>
    inline const T& max(const T& a,const T& b)
    {
        return (a>b)?a:b;
    }

    template <typename T, typename ... Args>
    inline const T& max(const T& a,const T& b, const Args& ... args)
    {
        return max(max(a,b),args ...);
    }

    template <typename T>
    inline T abs(const T& a)
    {
        return (a<T(0))?-a:a;
    }

    template <typename T>
    inline T clamp(T value, T min, T max)
    {
        return value < min ? min : (value > max ? max : value);
    }

    template <int N>
    struct power
    {
        template <typename NUMERIC_TYPE>
        static inline NUMERIC_TYPE of(const NUMERIC_TYPE& x){return x * power<N-1>::of(x);}
    };

    template <>
    struct power<0>
    {
        template <typename NUMERIC_TYPE>
        static inline NUMERIC_TYPE of(const NUMERIC_TYPE& x) {return 1;}
    };

    template<typename T>
    T discretize(const T& tab,std::function<double(double)> f)
    {
        return discretize<T>(tab.begin(),tab.end(),f);
    }

    template<typename T,typename Iterator>
    T discretize(Iterator first,Iterator last,std::function<double(double)> f)
    {
        const size_t size = std::distance(first,last);
        T res;
        double store = 0;
        for(unsigned int i=0; first != last;++first,++i)
        {
            store += f((i*2.0)/size-1);
            if(store > 1)
            {
                res.emplace_back(*first);
                do{
                    store -=1;
                }while(store >= 1);
            }
        }

        return res;
    }

    namespace ker
    {
        //unaire
        inline double uniform(double _1)
        {
            if(abs(_1) <=1)
                return _1/2.0;
            return 0;
        };

        inline double triangular(double _1)
        {
            double ab = abs(_1);
            if(ab <=1)
                return 1 - ab;
            return 0;
        };

        inline double epanechnikov(double _1)
        {
            if(abs(_1) <=1)
                return 3.0/4.0*(1-utils::maths::power<2>::of(_1));
            return 0;
        };

        inline double quartic(double _1)
        {

            if(abs(_1) <=1)
            {
                double c = 1-_1*_1;
                return 15.0/16.0*utils::maths::power<2>::of(c);
            }
            return 0;
        };

        inline double triweight(double _1)
        {
            if(abs(_1) <=1)
            {
                double c = 1-_1*_1;
                return 35.0/32.0*utils::maths::power<3>::of(c);
            }
            return 0;
        };

        inline double tricube(double _1)
        {
            double ab = abs(_1);
            if(ab <=1)
            {
                double c = 1-ab*ab*ab;
                return 70.0/81.0*utils::maths::power<3>::of(c);
            }
        };

        inline double gaussian(double _1,double _2,double _3)
        {
            return (1.0/_2*sqrt(2*M_PI))*exp(-utils::maths::power<2>::of(_1-_3)/(2*utils::maths::power<2>::of(_2)));
        };

        inline double cosine(double _1)
        {
            if(abs(_1)<=  1)
                return M_PI/4.0*cos(M_PI/2.0*_1);
            return 0;
        };

        //binary
        inline double mul(double _1,double _2)
        {
            return _1*_2;
        };

        inline double div(double _1,double _2)
        {
            return _1 / _2;
        };

        inline double add(double _1,double _2)
        {
            return _1 + _2;
        };

        inline double sub(double _1,double _2)
        {
            return _1 - _2;
        };
    }
}
}
