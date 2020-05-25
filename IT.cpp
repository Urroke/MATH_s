#include "math_objects/function_object.h"

double f1(double x)
{
    return x*x;
}

double f2(double x)
{
    return x;
}

double f3(double x)
{
    return x*x*x;
}


int main()
{
    math_function<double,double> f, one = f1, two = f2;
    //std::cout<<f(5)<<"\t"<<f_(5)<<"\n";;
    std::cout<<f1(10)<<"\n";
    std::cout<<f3(10)<<"\n";
    f1+=f3;
    std::cout<<f1(5);
}
