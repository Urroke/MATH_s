#include "math_objects/matrix.h"
#include "math_objects/function_object.h"
#include "math_objects/polynomial.h"
#include "little_math/little_math.h"

double func(double x)
{
    return 3*x*x;
}

int main()
{
    math_function<double, double> a(func);
    std::cout<<newton_kotes<double,double>(a,3,0,5,1);
    return 0;
}
