#include "math_objects/matrix.h"
#include "math_objects/function_object.h"
#include "little_math/little_math.h"
#include <fstream>

double func(double x)
{
    return 4*x*x*x*x - x*x*x + 2*x*x -7*x - 10;
}

int main()
{
    std::cout<<"OK";

    mvector<double, 10> x, y;
    for(int i = 0;i < 10;i++){
        x[i] = i;
        y[i] = func(i);
    }
    std::cout<<method_of_min_suare<double, 10, 4>(x, y);*/
}
