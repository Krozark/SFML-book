#include <iostream>

extern "C"{
    int print(int i){
        std::cout<<i<<std::endl;
        return 42;
    }
}
