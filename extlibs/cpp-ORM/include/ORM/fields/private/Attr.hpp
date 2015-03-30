#ifndef ORM_ATTR_HPP
#define ORM_ATTR_HPP

#include <ostream>
#include <utility>
#include <string>

#include <ORM/fields/private/VAttr.hpp>

namespace orm
{
    class Query;

    /**
     * \brief Store a value ass database row
     **/
    template<typename T>
    class Attr : public VAttr
    {
        protected:
            T _value; ///< value stored

        public:
            /**
             * \brief Make a Attr
             *
             * \param value value to store
             * \param column Column in db
             **/
            Attr(const T& value,const std::string& column);

            /**
             * \brief Make a Attr
             *
             * \param column Column in db
             **/
            Attr(const std::string& column);

            Attr(const Attr&) = delete;

            typedef T type; ///< type of stored object
            
            /**
             * \brief assignement operator
             *
             * \param v value to copy
             *
             * \return value
             **/
            template<typename U> T& operator=(const U& v);

            /**
             * \brief assignement operator
             *
             * \param v value to copy
             *
             * \return *this
             **/
            Attr<T>& operator=(const Attr<T>& v);
            
            /**
             * \brief addition operator
             *
             * \param v value to add
             *
             * \return value+v
             **/
            template<typename U> auto operator+(const U& v) -> decltype(_value+v);

            /**
             * \brief sub operator
             *
             * \param v value to sub
             *
             * \return value-v
             **/
            template<typename U> auto operator-(const U& v) -> decltype(_value-v);

            /**
             * \brief  multiply operator
             *
             * \param v value to multiply by
             *
             * \return value*v
             **/
            template<typename U> auto operator*(const U& v) -> decltype(_value*v);

            /**
             * \brief div operator
             *
             * \param v value to div by
             *
             * \return value/v
             **/
            template<typename U> auto operator/(const U& v) -> decltype(_value/v);

            /**
             * \brief mod operator
             *
             * \param v value to mod by
             *
             * \return v%value
             **/
            template<typename U> auto operator%(const U& v) -> decltype(_value%v);

            /**
             * \brief post increment operator
             *
             * \return *this
             **/
            Attr<T>& operator++();

            /**
             * \brief pre increment operator
             *
             * \return *this
             **/
            Attr<T>& operator++(int);

            /**
             * \brief post deincrement operator
             *
             * \return *this
             **/
            Attr<T>& operator--();

            /**
             * \brief pre deincrement operator
             *
             * \return *this
             **/
            Attr<T>& operator--(int);
            
            /**
             * \brief Comparaison operator
             *
             * \param v value to compare with
             *
             * \return value == v
             **/
            template<typename U> bool operator==(const U& v);

            /**
             * \brief Comparaison operator
             *
             * \param v value to compare with
             *
             * \return value != v
             **/
            template<typename U> bool operator!=(const U& v);

            /**
             * \brief Comparaison operator
             *
             * \param v value to compare with
             *
             * \return value > v
             **/
            template<typename U> bool operator>(const U& v);

            /**
             * \brief Comparaison operator
             *
             * \param v value to compare with
             *
             * \return value < v
             **/
            template<typename U> bool operator<(const U& v);

            /**
             * \brief Comparaison operator
             *
             * \param v value to compare with
             *
             * \return value >= v
             **/
            template<typename U> bool operator>=(const U& v);
            
            /**
             * \brief Comparaison operator
             *
             * \param v value to compare with
             *
             * \return value <= v
             **/
            template<typename U> bool operator<=(const U& v);

            /**
             * \brief negation operator
             *
             * \return !value
             **/
            bool operator!();


            /**
             * \brief addition operator
             *
             * \param v value to add
             *
             * \return *this
             **/
            template<typename U> Attr<T>& operator+=(const U& v);

            /**
             * \brief sub operator
             *
             * \param v value to sub
             *
             * \return *this
             **/
            template<typename U> Attr<T>& operator-=(const U& v);

            /**
             * \brief multiply operator
             *
             * \param v value to multiply
             *
             * \return *this
             **/
            template<typename U> Attr<T>& operator*=(const U& v);

            /**
             * \brief div operator
             *
             * \param v value to div
             *
             * \return *this
             **/
            template<typename U> Attr<T>& operator/=(const U& v);
            
            /**
             * \brief mod operator
             *
             * \param v value to mod
             *
             * \return *this
             **/
            template<typename U> Attr<T>& operator%=(const U& v);

            /**
             * \brief cast operator
             *
             * \cast this in value
             **/
            operator T();

            /**
             * \brief addition operator
             *
             * \param v value to add
             *
             * \return value+v.value
             **/
            T operator+(Attr<T>& v);

            /**
             * \brief sub operator
             *
             * \param v value to sub
             *
             * \return value-v.value
             **/
            T operator-(Attr<T>& v);

            /**
             * \brief multiply operator
             *
             * \param v value to multiply
             *
             * \return value*v.value
             **/
            T operator*(Attr<T>& v);

            /**
             * \brief div operator
             *
             * \param v value to div
             *
             * \return value/v.value
             **/
            T operator/(Attr<T>& v);

            /**
             * \brief mod operator
             *
             * \param v value to mod
             *
             * \return value%v.value
             **/
            T operator%(Attr<T>& v);

            /**
             * \brief Comparaison operator
             *
             * \param v value to compare with
             *
             * \return value == v.value
             **/
            template<typename U> bool operator==(Attr<U>& v);

            /**
             * \brief Comparaison operator
             *
             * \param v value to compare with
             *
             * \return value != v.value
             **/
            template<typename U> bool operator!=(Attr<U>& v);

            /**
             * \brief Comparaison operator
             *
             * \param v value to compare with
             *
             * \return value > v.value
             **/
            template<typename U> bool operator>(Attr<U>& v);

            /**
             * \brief Comparaison operator
             *
             * \param v value to compare with
             *
             * \return value < v.value
             **/
            template<typename U> bool operator<(Attr<U>& v);

            /**
             * \brief Comparaison operator
             *
             * \param v value to compare with
             *
             * \return value >= v.value
             **/
            template<typename U> bool operator>=(Attr<U>& v);

            /**
             * \brief Comparaison operator
             *
             * \param v value to compare with
             *
             * \return value <= v.value
             **/
            template<typename U> bool operator<=(Attr<U>& v);

            /**
             * \brief addition operator
             *
             * \param v value to add
             *
             * \return *this
             **/
            template<typename U> Attr<T>& operator+=(Attr<U>& v);

            /**
             * \brief sub operator
             *
             * \param v value to sub
             *
             * \return *this
             **/
            template<typename U> Attr<T>& operator-=(Attr<U>& v);

            /**
             * \brief multiply operator
             *
             * \param v value to multiply
             *
             * \return *this
             **/
            template<typename U> Attr<T>& operator*=(Attr<U>& v);

            /**
             * \brief div operator
             *
             * \param v value to div
             *
             * \return *this
             **/
            template<typename U> Attr<T>& operator/=(Attr<U>& v);

            /**
             * \brief mod operator
             *
             * \param v value to mod
             *
             * \return *this
             **/
            template<typename U> Attr<T>& operator%=(Attr<U>& v);

            /**
             * \brief print the stored value
             *
             * \param output print in this stream
             *
             * \return output
             **/
            virtual std::ostream& print_value(std::ostream& output)const override;

            const T& value()const;


        protected:
            inline T& getValue();
            bool prepared;

        private:
            virtual T prepare_to_db(const T& value);
            /**
             * \brief Set the value in the query (use for dispatch
             *
             * \param query Query to set in
             * \param column culum number to set
             *
             * \return false if fail
             */
            virtual bool set(Query& query,const unsigned int& column) override final;


            /**
             * \brief Extract the value from the query row
             *
             * \param query executed query
             * \param prefix column number to get
             * \param max_depth max depth of construction recurtion
             *
             * \return false if fail
             **/
            virtual bool get(const Query& query,int& prefix,int max_depth) override final;

            virtual T prepare_from_db(const T& value);

            inline void setValue(const T& v);
    };

    // define more common type
    using PositiveIntegerField = Attr<unsigned int>;
    using BigIntegerField = Attr<long long int>;
    using BigDoubleField = Attr<long double>;

    /*
      'CommaSeparatedIntegerField':   
      'DateField':                    
      'DateTimeField':                
      'DecimalField':                 
      'FileField':                    
      'FilePathField':                
      'IPAddressField':               
      'GenericIPAddressField':        
      'NullBooleanField':             
      'OneToOneField':                
      'PositiveSmallIntegerField':    
      'SlugField':                    
      'SmallIntegerField':            
      'TimeField'
        CompressedTextField : blob
      */

};
#include <ORM/fields/private/Attr.tpl>

#endif
