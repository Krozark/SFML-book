#include <utils/json/Object.hpp>
//#include <utils/json/Value.hpp>

namespace utils
{
    namespace json
    {
        
        Object::Object()
        {
        }

        std::ostream& operator<<(std::ostream& stream, const Object& self)
        {
            self.print_ident(stream,0);
            return stream;
        }

        void Object::print_ident(std::ostream& stream, int i)const
        {
            /*if(i >0)
                stream<<"\n";
            ident(stream,i);*/
            stream<<"{\n";
            ++i;

            if(values.size()>0)
            {
                auto begin = values.begin();
                auto end = values.end();

                ident(stream,i);
                stream<<"\""<<begin->first<<"\" : ";
                begin->second.print_ident(stream,i);

                ++begin;
                while(begin!=end)
                {
                    stream<<",\n";
                    ident(stream,i);
                    stream<<"\""<<begin->first<<"\" : ";
                    begin->second.print_ident(stream,i);
                    ++begin;
                }
            }
            --i;
            stream<<"\n";
            ident(stream,i);
            stream<<"}";
        }

        Value& Object::operator[] (const std::string& key)
        {
            return values[key];
        }

        const Value& Object::operator[] (const std::string& key) const
        {
            return values.at(key);
        }

        /*std::pair<std::unordered_map<std::string, Value>::iterator, bool> Object::insert(const std::pair<std::string, Value>& v)
        {
            return values.insert(v);
        }*/

        std::unordered_map<std::string, Value>::const_iterator Object::begin() const
        {
            return values.begin();
        }

        std::unordered_map<std::string, Value>::const_iterator Object::end() const
        {
            return values.end();
        }

        std::unordered_map<std::string, Value>::iterator Object::begin()
        {
            return values.begin();
        }

        std::unordered_map<std::string, Value>::iterator Object::end()
        {
            return values.end();
        }

        size_t Object::size() const
        {
            return values.size();
        }


        void Object::ident(std::ostream& out,int max)
        {
            for(int i=0;i<max;++i)
                out<<"    ";
        }

    }
}
