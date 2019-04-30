#include "little_math/little_math.h"
#include "math_objects/function_object.h"

double f(double x)
{
    return std::sin(std::cos(x*x));
}

double control(double x)
{
    return std::sin(std::cos(x*x));
}

double func(double x, double a, double b)
{
    std::function<double(double)> integral = [=](double s)-> double{
        return std::cos(s*(x + 1));
    };
    //return gauss_legendre(integral, a, b) + f(x);
}

int main()
{
    constexpr int degree = 50, size = 100;
    std::ofstream fout("my.txt"), fout1("control.txt");
    mvector<double, size> x, y;

    for(int i = 0;i < size;i++){
        x[i] = 100 + double(i)/(500);
        y[i] = f(x[i]);
    }

    polynom<double, degree> result(method_of_min_suare<double, size, degree>(x, y));

    for(int i = 0;i < size;i++){
        fout1<<100 + double(i)/500<<"\t"<<control(100 + double(i)/500)<<"\n";
        fout<<100 + double(i)/500<<"\t"<<result(100 + double(i)/500)<<"\n";
    }
}
