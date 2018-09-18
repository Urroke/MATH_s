#include "math_objects/matrix.h"
#include "math_objects/function_object.h"
#include "little_math/little_math.h"
#include <string>
#include <fstream>
#include <typeinfo>
#include <chrono>
#include <ctime>

template <typename type,size_t size>
mvector<type, size> zeid(mvector<type, size> x, double eps)
{
    mvector<type, size> prev;
    double err;

    do{
        prev = x;

        x[0] = x[1] - 4;
        x[1] = x[0]*x[0] / 2;

        for(int i = 0;i < size - 1;i++)
            err = std::max(std::abs(prev[i] - x[i]), std::abs(prev[i + 1] - x[i + 1]));

    } while(err > eps);
    return x;
}

int main()
{
    mvector<double, 2> ex;
    std::cin>>ex;
    std::cout<<zeid(ex, 0.001);
    return 0;
}
