namespace orm
{
    template<typename T>
    int Query::getObj(T& obj,int max_depth)
    {
        if(not executed)
            execute();
        
        if (next())
            return obj.loadFromDB(*this,max_depth);

        ORM_PRINT_WARNING("Query::getObj(T& obj,int max_depth) failed : No raw return")
        return 0;
    };

    template<typename T>
    int Query::getObj(std::list<std::shared_ptr<T> >& objs,int max_depth)
    {
        if(not executed)
            execute();
        int res = 0;
        while(next())
        {
            auto tmp = T::cache.getOrCreate(*this,max_depth);
            //TODO
            //if(tmp)
            {
                objs.emplace_back(tmp);
                ++res;
            }
        }   
        return res;     
    };
};
