#include <utils/json/Driver.hpp>

int main(int argc,char* argv[])
{
    if(argc <2)
    {
        std::cerr<<"A json file is required as parameter"<<std::endl;
        return 0;
    }
        
    utils::json::Value* v = utils::json::Driver::parse_file(argv[1]);
    std::cout<<*v<<std::endl;

    return 0;
}
