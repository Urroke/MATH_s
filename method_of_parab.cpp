#include "math_objects/matrix.h"
#include "math_objects/function_object.h"
#include "little_math/little_math.h"
#include <string>
#include <fstream>
#include <typeinfo>
#include <chrono>
#include <ctime>

double func(double x)
{
    return x*x - 2*x;
}

int main()
{
    double res;
    math_function<double, double> a(func);
    res = (a==0)(-5,5,0.001);
    std::cout<<res;
    return 0;
}
