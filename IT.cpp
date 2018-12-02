#include "little_math/little_math.h"

double func(double x)
{
    return x*x*x - 7*x*x + 5*x + 4;
}

double method_of_newton(double(*func)(double), double x, double eps)
{
    double x1;
    do{
        x1 = x;
        x = x - 0.0002*func(x)/(-func(x + 0.0002) + 4*func(x + 0.0001) - 3*func(x));
    }while(std::fabs(x - x1) > eps);
    return x;
}

int main()
{
    std::ifstream fin("dat.dat");
    matrix<double, 4, 4> A;
    mvector<double, 4> b;
    double res;
    fin>>A>>b;
    //std::cout<<method_of_gauss(A, b, false);
    res = method_of_newton(func, 1, 0.0001);
    std::cout<<res<<"\n"<<func(res);
}
