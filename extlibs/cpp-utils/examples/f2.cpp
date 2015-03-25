#include <iostream>
#include <utils/icpp/test.hpp>

extern "C"{

    int print(int i){
        std::cout<<i<<std::endl;
        return 42;
    }

    void show(const Value& v){
        v.show(std::cout)<<std::endl;
    }
}
