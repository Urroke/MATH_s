#include "math_objects/matrix.h"
#include "math_objects/function_object.h"
#include "little_math/little_math.h"
#include <string>
#include <fstream>
#include <typeinfo>
#include <chrono>
#include <ctime>


int main()
{
    mvector<double, 3> ad, bd;
    mvector<float, 3> af, bf;
    ad = {1, 2, 4};
    bd = {4, -6, 9};
    af = {1, 2, 4};
    bf = {4, -6, 9};
    ad -= bd;
    std::cout<<ad<<"\n";
    std::cout<<ad*bf<<"\n";
    std::cout<<ad*2<<"\n";
    std::cout<<af*2<<"\n";
    return 0;
}
