#include "math_objects/matrix.h"
#include "math_objects/function_object.h"
#include "math_objects/polynomial.h"
#include "little_math/little_math.h"

double func(double x)
{
    return x*x*std::log(x);
}

int main()
{
    math_function<double, double> a(func);
    std::cout<<newton_kotes<double,double>(a,3, 1 ,2.71812 ,10);
    return 0;
}
