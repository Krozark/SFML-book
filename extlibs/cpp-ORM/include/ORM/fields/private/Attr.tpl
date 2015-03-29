#include <ORM/backends/Query.hpp>

namespace orm 
{
    template<typename T>
    Attr<T>::Attr(const T& val,const std::string& col) : VAttr(col), _value(val), prepared(false)
    {
    };

    template<typename T>
    Attr<T>::Attr(const std::string& col) : VAttr(col) , _value(), prepared(false)
    {
    };

    template<typename T>
    bool Attr<T>::get(const Query& query,int& prefix,int max_depth)
    {
        prepared = false;
        return query.get(_value,prefix);
    };

    template<typename T>
    T Attr<T>::prepare_to_db(const T& value)
    {
        return value;
    }

    template<typename T>
    bool Attr<T>::set(Query& query,const unsigned int& column)
    {
        bool res;

        if(prepared)//_value is for local
        {
            T tmp = prepare_to_db(_value);
            res = query.set(tmp,column);
        }
        else
            res = query.set(_value,column);
        return res;
    };

    template<typename T>
    T Attr<T>::prepare_from_db(const T& value)
    {
        return value;
    }


    template<typename T>
    std::ostream& Attr<T>::print_value(std::ostream& output)const
    {
        return (output<<'"'<<_value<<'"');
    }

    template<typename T>
    const T& Attr<T>::value()const
    {
        return _value;
    }


    template<typename T>
    T& Attr<T>::getValue()
    {
        if(not prepared)
        {
            _value = prepare_from_db(_value);
            prepared = true;
        }
        return _value;
    }

    template<typename T>
    void Attr<T>::setValue(const T& v)
    {
        prepared = true;
        modify = true;
        _value = v;
    }
    
    template<typename T>
    template<typename U>
    T& Attr<T>::operator=(const U& v)
    {
        setValue(v);
        return _value;
    };

    template<typename T>
    Attr<T>& Attr<T>::operator=(const Attr<T>& v)
    {
        setValue(v._value);
        prepared = v.prepared;
        _value=v._value;
        return*this;
    };

    template<typename T>
    template<typename U>
    auto Attr<T>::operator+(const U& v) -> decltype(_value+v)
    {
        return getValue()+v;
    };

    template<typename T>
    template<typename U>
    auto Attr<T>::operator-(const U& v) -> decltype(_value-v)
    {
        return getValue()-v;
    };

    template<typename T>
    template<typename U>
    auto Attr<T>::operator*(const U& v) -> decltype(_value*v)
    {
        return getValue()*v;
    };

    template<typename T>
    template<typename U>
    auto Attr<T>::operator/(const U& v) -> decltype(_value/v)
    {
        return getValue()/v;
    };

    template<typename T>
    template<typename U>
    auto Attr<T>::operator%(const U& v) -> decltype(_value%v)
    {
       return getValue()%v;
    };

    template<typename T>
    Attr<T>& Attr<T>::operator++()
    {
        getValue();
        ++_value;
        modify=true;
        return *this;
    };

    template<typename T>
    Attr<T>& Attr<T>::operator++(int)
    {
        getValue();
        ++_value;
        modify=true;
        return *this;
    };

    template<typename T>
    Attr<T>& Attr<T>::operator--()
    {
        getValue();
        --_value;
        modify=true;
        return *this;
    };

    template<typename T>
    Attr<T>& Attr<T>::operator--(int)
    {
        getValue();
        --_value;
        modify=true;
        return *this;
    };

    template<typename T>
    template<typename U>
    bool Attr<T>::operator==(const U& v)
    {
        return getValue() == v;
    };

    template<typename T>
    template<typename U>
    bool Attr<T>::operator!=(const U& v)
    {
        return getValue()!=v;
    }

    template<typename T>
    template<typename U>
    bool Attr<T>::operator>(const U& v)
    {
        return getValue()>v;
    };

    template<typename T>
    template<typename U>
    bool Attr<T>::operator<(const U& v)
    {
        return getValue()<v;
    };

    template<typename T>
    template<typename U>
    bool Attr<T>::operator>=(const U& v)
    {
        return getValue()>=v;
    };

    template<typename T>
    template<typename U>
    bool Attr<T>::operator<=(const U& v) 
    {
        return getValue()<=v;
    };

    template<typename T>
    bool Attr<T>::operator!()
    {
        return !getValue();
    };

    template<typename T>
    template<typename U>
    Attr<T>& Attr<T>::operator+=(const U& v)
    {
        getValue()+=v;
        modify=true;
        return*this;
    };

    template<typename T>
    template<typename U>
    Attr<T>& Attr<T>::operator-=(const U& v)
    {
        getValue()-=v;
        modify=true;
        return*this;
    };

    template<typename T>
    template<typename U>
    Attr<T>& Attr<T>::operator*=(const U& v)
    {
        getValue()*=v;
        modify=true;
        return*this;
    };

    template<typename T>
    template<typename U>
    Attr<T>& Attr<T>::operator/=(const U& v)
    {
        getValue()/=v;
        modify=true;
        return*this;
    };

    template<typename T>
    template<typename U>
    Attr<T>& Attr<T>::operator%=(const U& v)
    {
        getValue()%=v;
        modify=true;
        return*this;
    };

    template<typename T>
    Attr<T>::operator T()
    {
        return getValue();
    };

    template<typename T>
    T Attr<T>::operator+(Attr<T>& v)
    {
        return getValue()+v.getValue();
    };

    template<typename T>
    T Attr<T>::operator-(Attr<T>& v)
    {
        return getValue()-v.getValue();
    };

    template<typename T>
    T Attr<T>::operator*(Attr<T>& v)
    {
        return getValue()*v.getValue();
    };

    template<typename T>
    T Attr<T>::operator/(Attr<T>& v)
    {
        return getValue()/v.getValue();
    };

    template<typename T>
    T Attr<T>::operator%(Attr<T>& v)
    {
        return getValue()%v.getValue();
    };

    template<typename T>
    template<typename U>
    bool Attr<T>::operator==(Attr<U>& v)
    {
        return getValue()==v.getValue();
    };

    template<typename T>
    template<typename U>
    bool Attr<T>::operator!=(Attr<U>& v)
    {
        return getValue()!=v.getValue();
    };

    template<typename T>
    template<typename U>
    bool Attr<T>::operator>(Attr<U>& v)
    {
        return getValue()>v.getValue();
    };

    template<typename T>
    template<typename U>
    bool Attr<T>::operator<(Attr<U>& v)
    {
        return getValue()<v.getValue();
    };

    template<typename T>
    template<typename U>
    bool Attr<T>::operator>=(Attr<U>& v)
    {
        return getValue()>=v.getValue();
    };

    template<typename T>
    template<typename U>
    bool Attr<T>::operator<=(Attr<U>& v)
    {
        return getValue()<=v.getValue();
    };

    template<typename T>
    template<typename U>
    Attr<T>& Attr<T>::operator+=(Attr<U>& v)
    {
        getValue()+=v.getValue();
        modify=true;
        return*this;
    };

    template<typename T>
    template<typename U>
    Attr<T>& Attr<T>::operator-=(Attr<U>& v)
    {
        getValue()-=v.getValue();
        modify=true;
        return*this;
    };

    template<typename T>
    template<typename U>
    Attr<T>& Attr<T>::operator*=(Attr<U>& v)
    {
        getValue()*=v.getValue();
        modify=true;
        return*this;
    };

    template<typename T>
    template<typename U>
    Attr<T>& Attr<T>::operator/=(Attr<U>& v)
    {
        getValue()/=v.getValue();
        modify=true;
        return*this;
    };

    template<typename T>
    template<typename U>
    Attr<T>& Attr<T>::operator%=(Attr<U>& v)
    {
        getValue()%=v.getValue();
        modify=true;
        return*this;
    };
};
