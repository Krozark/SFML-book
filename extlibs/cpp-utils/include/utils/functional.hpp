#ifndef UTILS_FUNCTIONAL_HPP
#define UTILS_FUNCTIONAL_HPP

#include <utility>
#include <tuple>

namespace utils
{
    /**
     * \brief try namespace (for tests)
     */
    namespace func
    {
        
        /***
         * \brief the c++14 apply function
         * Call a function with there param in a tuple
         */
        template<typename Ret,typename ... Args>
        constexpr Ret apply(Ret(*f)(Args...),const std::tuple<Args...>& t);

        /**
         * \brief gererique function class.
         * Use to store generic functions types
         */
        class VFunc
        {
            public:
                /**
                 * \brief call the function
                 * \param args the function params
                 * \return the return value
                 */
                template<typename Ret,typename ... Args>
                Ret call(Args&& ... args)const;

                virtual ~VFunc(){};

            protected:
                void* func; //< the function ptr

                VFunc(void* f); //< constuctor
        };

        /**
         * \brief same as VFunc, but with construct specified function type
         */
        template<typename Ret,typename ... Args>
        class Func: public VFunc
        {
            public:
                typedef Ret(*ftype)(Args...); //< the inner function type

                Func(ftype f); //< constructor
                Ret operator()(Args&& ... args)const; //< call the function

                operator ftype()const; ///<cast operator

                virtual ~Func(){};

            private:

        };

        /**
         * \return a constructed Func by deducing his type
         */
        template<typename Ret,typename ... Args>
        constexpr Func<Ret,Args...> make_func(Ret (*f)(Args...));
    }
}
#include <utils/functional.tpl>
#endif
