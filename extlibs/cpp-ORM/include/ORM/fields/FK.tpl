namespace orm
{
    /*template<typename T,bool NULLABLE>
    FK<T,NULLABLE>::FK(const int& id,const std::string& column) : FKBase<T>(id,column,NULLABLE)
    {
    }*/

    template<typename T,bool NULLABLE>
    FK<T,NULLABLE>::FK(const std::string& column) : FKBase<T>(column,NULLABLE)
    {
    }
}
