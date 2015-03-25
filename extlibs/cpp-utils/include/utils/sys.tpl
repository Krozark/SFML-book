namespace utils
{
    /**
     * \brief try namespace (for tests)
     */
    namespace sys
    {
        template<typename Ret,typename ... Args>
        bool Library::load_f(const std::string& name)
        {
            if (lib == nullptr)
                return false;

            auto value = funcs.find(name);
            if(value != funcs.end())
            {
                utils::log::error("utils:sys::Library::load_f","function of name",name,"already exists");
                return false;
            }

            void* f = get_f(name);
            if(f == nullptr)
                return false;

            funcs.emplace(name,new utils::func::Func<Ret,Args...>(reinterpret_cast<Ret(*)(Args...)>(f)));
            return true;
        }

        template<typename ... Args>
        Compiler& Compiler::input(Args&& ... args)
        {
            char tmp[] = {(_inputs.push_back(args),'0')...};
            ((void)(tmp));

            return *this;
        }

        template<typename ... Args>
        Compiler& Compiler::flags(Args&& ... args)
        {
            char tmp[] = {(_flags.push_back(args),'0')...};
            ((void)(tmp));

            return *this;
        }

        template<typename ... Args>
        Compiler& Compiler::link(Args&& ... args)
        {
            char tmp[] = {(_links.push_back(args),'0')...};
            ((void)(tmp));

            return *this;
        }
    }
}
