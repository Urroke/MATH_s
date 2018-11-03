#include "little_math/little_math.h"
#include "math_objects/function_object.h"

double f(double x)
{
    return 5*std::sin(x);
}

double control(double x)
{
    return std::sin(2*x + 2)/(x + 1) + f(x);
}

double func(double x, double a, double b)
{
    std::function<double(double)> integral = [=](double s)-> double{
        return std::cos(s*(x + 1));
    };
    return gauss_legendre(integral, a, b) + f(x);
}

int main()
{
    constexpr int degree = 6, size = 10;
    std::ofstream fout("my.txt"), fout1("control.txt");
    mvector<double, 10> x, y;

    for(int i = 0;i < 10;i++){
        x[i] = double(i)/5;
        y[i] = func(double(i)/5, .0, 2.0);
    }

    polynom<double, degree> result(method_of_min_suare<double, size, degree>(x, y));

    for(int i = 0;i < 100;i++){
        fout1<<double(i)/50<<"\t"<<control(double(i)/50)<<"\n";
        fout<<double(i)/50<<"\t"<<result(double(i)/50)<<"\n";
    }
}
