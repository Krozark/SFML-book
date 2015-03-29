namespace orm
{
    template<typename T>
    T DB::formatValue(const std::string& ope,T value) const
    {
        return value;
    }
    template<>
    std::string DB::formatValue(const std::string& filter,std::string value) const;

    template<typename ... Args>
    std::string DB::makecolumname(DB& db,const std::string& prefix,const std::string& column,Args&& ...args)
    {
        return makecolumname(db,JOIN_ALIAS(prefix,column),std::forward<Args>(args)...);
    }
}
