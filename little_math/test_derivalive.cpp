#include "little_math.h"
#include <iostream>

double func(double x)
{
    return x*x;
}

double dfunc(double x)
{
    return 2*x;
}

double func1(double x)
{
    return std::sin(x);
}

double func2(double x)
{
    return x*x - std::atan(x);
}

double func3(double x)
{
    return std::sin(std::cos(x));
}

double dfunc1(double x)
{
    return std::cos(x);
}

double dfunc2(double x)
{
    return 2.0*x - 1.0/(1.0 + x*x);
}

double dfunc3(double x)
{
    return -std::cos(std::cos(x))*std::sin(x);
}

int main()
{
    const double eps = 0.00001;
    std::function<double(double)> der = derivative<double, 3, 2>(func1, 0.01);
    std::cout<<"test1\n";
    for(int i = 0;i < 100;i++)
        if(std::fabs(der(i) - dfunc1(i)) > eps){
            std::cout<<"ERROR\n";
            break;
        }
        else if(i == 99) std::cout<<"OK\n";

    der = derivative<double, 3, 2>(func2, 0.01);
    std::cout<<"test2\n";
    for(int i = 0;i < 100;i++)
        if(std::fabs(der(i) - dfunc2(i)) > eps){
            std::cout<<"ERROR\n";
            break;
        }
        else if(i == 99) std::cout<<"OK\n";

    der = derivative<double, 3, 2>(func3, 0.01);
    std::cout<<"test3\n";
    for(int i = 0;i < 100;i++)
        if(std::fabs(der(i) - dfunc3(i)) > eps){
            std::cout<<"ERROR ";
            std::cout<<std::fabs(der(i) - dfunc3(i))<<"\n";
        }
        else if(i == 99) std::cout<<"OK\n";
}
