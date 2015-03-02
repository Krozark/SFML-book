#ifndef RANDOM__HPP
#define RANDOM__HPP

#include <cstdlib>
#include <ctime>
#include <random>

namespace book
{

    extern std::default_random_engine generator;

    inline void rand_init() {
        srand(time(NULL));

    };
    inline float random(float min,float max) { return (rand()/float(RAND_MAX))*(max-min) + min; }
    inline int random(int min,int max) { return rand()%(max-min+1) + min; }
}

#endif
