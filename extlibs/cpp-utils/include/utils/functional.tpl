namespace utils
{
    /**
     * \brief try namespace (for tests)
     */
    namespace func
    {
        template<int N>
        struct __apply_helper
        {
            template<typename Ret,typename ... FArgs,typename ... Args>
            static constexpr Ret apply(Ret(*f)(FArgs...),const std::tuple<FArgs...>& t,Args ... args)
            {
                return __apply_helper<N-1>::apply(f,t,std::get<N-1>(t),std::forward<Args>(args)...);
            }
        };

        template<>
        struct __apply_helper<0>
        {
            template<typename Ret,typename ... FArgs,typename ... Args>
            static constexpr Ret apply(Ret(*f)(FArgs...),const std::tuple<FArgs...>& t,Args ... args)
            {
                return f(std::forward<Args>(args)...);
            }
        };
        
        
        template<typename Ret,typename ... Args>
        constexpr Ret apply(Ret(*f)(Args...),const std::tuple<Args...>& t)
        {
            return __apply_helper<sizeof...(Args)>::apply(f,t);
        }
        
        /*
         //C++14 version
        template <typename F, typename Tuple, size_t... I>
        decltype(auto) __apply_helper(F&& f, Tuple&& t, std::index_sequence<I...>)
        {
            return std::forward<F>(f)(std::get<I>(std::forward<Tuple>(t))...);
        }

        template <typename F, typename Tuple>
        decltype(auto) apply(F&& f, Tuple&& t)
        {
            using Indices = std::make_index_sequence<std::tuple_size<decay_t<Tuple>>::value>;
            return __apply_helper(std::forward<F>(f),std::forward<Tuple>(t),Indices{});
        }
        */

        /*** VFunc ***/

        template<typename Ret,typename ... Args>
        Ret VFunc::call(Args&& ... args)const
        {
            typedef Ret(*t)(Args...);
            return ((t)func)(std::forward<Args>(args)...);
        }

        /*** Func ***/
        template<typename Ret,typename ... Args>
        Func<Ret,Args...>::Func(ftype f) : VFunc((void*)f){}

        template<typename Ret,typename ... Args>
        Ret Func<Ret,Args...>::operator()(Args&& ... args)const
        {
            return call<Ret,Args...>(std::forward<Args>(args)...);
        }

        template<typename Ret,typename ... Args>
        Func<Ret,Args...>::operator ftype()const
        {
            typedef Ret(*t)(Args...);
            return (t)func;;
        }


        template<typename Ret,typename ... Args>
        constexpr Func<Ret,Args...> make_func(Ret (*f)(Args...))
        {
            return {f};
        }
    }
}
