#ifndef ORM_FK_HPP
#define ORM_FK_HPP

#include <ORM/fields/private/FKBase.hpp>

namespace orm
{
    /**
     * \brief exactly like FKBase, but make nullable as template param
     **/
    template<typename T,bool NULLABLE=true>
    class FK : public FKBase<T>
    {
        public:
            /**
             * \brief Construct a FK
             *
             * \param column colum where the fk is stored
             **/
            FK(const std::string& column);

            FK(const FK&) = delete;

            using FKBase<T>::operator=;
            using FKBase<T>::operator*;
    };
}

#include <ORM/fields/FK.tpl>

#endif
