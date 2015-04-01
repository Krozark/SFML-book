#ifndef ORM_CACHE_HPP
#define ORM_CACHE_HPP

#include <ORM/backends/Query.hpp>
#include <string>
#include <memory>

//#include <mutex>

#ifdef ORM_USE_CACHE
    #include <unordered_map>
#endif


namespace orm
{
    template<typename T> class SqlObject;
    template<typename T> class FKBase;

    /**
     * \brief Class to store object tha have already be query
     * \todo colector that clear unused obj of the Cache every ... minutes
     **/
    template<typename T>
    class Cache
    {
        public:
            typedef std::shared_ptr<T> type_ptr; ///< Type of the stored object
            /***
             * \brief Construct a Cache for T
             *
             * Note: T have to be a SqlObject
             **/
            explicit Cache();

            /**
             * \brief Destructor
             **/
            ~Cache();

            //Cache(const Cache<T>&)=delete;
            //Cache<T>& operator=(const Cache<T>&)=delete;
            
            
            /**
             * \brief make query to get object if not in cache
             *
             * \param pk PK of the object
             * \param max_depth Maximum depth of construction
             *
             * \return a shared_ptr to tho object stored in cache
             **/
            type_ptr getOrCreate(const unsigned int& pk,DB& bd,int max_depth);

            /**
             * \brief construct object from query if pk not in cache
             *
             * \param pk PK of the object
             * \param query Query to use for construction
             * \param index colum in the query to start
             * \param max_depth Maximum depth of construction
             *
             * \return a shared_ptr to tho object stored in cache
             **/
            type_ptr getOrCreate(const unsigned int& pk,const Query& query,int& prefix,int max_depth);

            /**
             * \brief construct object from query if not in cache after extracting pk from query
             *
             * \param query Query to use for construction
             * \param max_depth Maximum depth of construction
             *
             * \return a shared_ptr to tho object stored in cache
             **/
            type_ptr getOrCreate(const Query& query,int max_depth);

            /**
             * \brief Print the cache content
             **/
            void __print__();

            /**
             * \brief clear the entire cash
             * Delete all the objects from the cache
             * All future references for the same PK of
             * object will be errored
             * \param reset_pk if true, all the pk are set to default (-1)
             */
            void clear(bool reset_pk=true);

        private:
            friend class SqlObject<T>;
            friend class FKBase<T>;

            //std::recursive_mutex _mutex;
            /*
             * \brief stuct that hold an object
             * and the date that hit was added to the cache.
             */
            /*class time_obj {
                std::time_t added;
                type_ptr obj;
            };*/

            /**
             * \brief Add a object in the cache
             *
             * \param obj Object to add
             *
             * \return the shared_ptr of the stored object
             **/
            type_ptr& add(type_ptr& obj);

            /**
             * \brief Add a object in the cache
             *
             * \param obj Object to add
             *
             * \return the shared_ptr of the stored object
             **/
            //type_ptr& add(T& obj);

#ifdef ORM_USE_CACHE
            std::unordered_map<int,type_ptr> map; ///< store all the objects
#endif

            /**
             * \brief delete object of specified pk
             **/
            void del(const unsigned int& pk);

    };
}
#include <ORM/core/Cache.tpl>
#endif
