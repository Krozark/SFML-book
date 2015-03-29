namespace orm
{
    
    template<typename T>
    Register<T>::Register()
    {
        #if ORM_DEBUG & ORM_DEBUG_REGISTER
        std::cerr<<MAGENTA<<"[Register] Table "<<T::table<<BLANC<<std::endl;
        #endif

        static T tmp;
        for(VAttr* attr: tmp.attrs)
        {
            #if ORM_DEBUG & ORM_DEBUG_REGISTER
            //std::cerr<<MAGENTA<<"[Register] Attr "<<attr->column<<BLANC<<std::endl;
            #endif
            SqlObject<T>::column_attrs.emplace_back(attr);
        }
        for(VFK* fk: tmp.fks)
        {
            #if ORM_DEBUG & ORM_DEBUG_REGISTER
            //std::cerr<<MAGENTA<<"[Register] Fk "<<fk->column<<BLANC<<std::endl;
            #endif
            SqlObject<T>::column_fks.emplace_back(fk);
        }

        Tables::_create.push_back(
                                 []()->bool{
                                    return SqlObject<T>::create();
                                 }
                                );

        Tables::_drop.push_back(
                               []()->bool{
                                return SqlObject<T>::drop();
                                }
                            );

        Tables::_clear.push_back(
                                   []()->bool{
                                    return SqlObject<T>::clear();
                                    }
                                );

        #if ORM_DEBUG & ORM_DEBUG_REGISTER
        std::cerr<<MAGENTA<<"[Register] END Table "<<T::table<<BLANC<<std::endl;
        #endif
    }
}
