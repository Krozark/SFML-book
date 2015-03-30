#ifndef ORM_VFK_HPP
#define ORM_VFK_HPP

#include <ORM/fields/private/VAttr.hpp>

namespace orm
{
    class SqlObjectBase;
    template<typename T> class SqlObject;

    /**
     * \brief base classe of all FK stored in database
     **/
    class VFK : public VAttr
    {
        public:
            /**
             * \brief Construct a FK
             *
             * \param column Column where the object fk is stored
             * \param nullable if the fk can be null
             **/
            VFK(const std::string& column,const bool nullable=true);

            /**
             * \brief add the attr to the object
             *
             * \param obj The owner of the attr
             **/
            virtual void registerAttr(SqlObjectBase&) final;

             /**
             * \brief Save or update the object on the fk
             *
             * \param db the db to fetch
             * \param recursive save recursively
             *
             * \return false if fail
             **/
            virtual bool save(bool recursive, DB&) = 0; 

            /**
             * \brief Delete the object from the db and cache
             *  
             *  Note : whe use on object linked in other object with fks can cause trouble because of the remove of the cache
             *  Set the pk to -1
             *
             * \param db the db to fetch
             *
             * \return fale if fail
             **/      
            virtual bool del(bool recursive, DB&) = 0;

            /**
             * \return the fk value 
             */
            inline int getFk()const{return fk;}


        protected:
            template<typename T> friend class SqlObject;

            int fk; ///< the fk value (if fk <=0 => null)
            //bool loaded; ///< as a loaded object
            const bool nullable; ///< is nullable

            /**
             * \brief Use for increment the column number without construction.
             * Note : this is use with the cache if the object is find in it
             *
             * \param depth column nuber to increment
             * \param max_depth maximun depth of construction
             **/
            virtual void incDepth(int& depth,int max_depth)const = 0;

            /**
             * \brief get the stored object
             *
             * \param db the db to fetch
             * \param max_depth maximun depth of construction if object not existe
             *
             * \return the stored object
             **/
            virtual const SqlObjectBase& getObject(DB& db,int max_depth=ORM_DEFAULT_MAX_DEPTH)= 0;



    };
}
#endif
