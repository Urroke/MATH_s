#include "math_objects/matrix.h"
#include "little_math/little_math.h"
using real = double;


double f(double x)
{
    return std::exp(x);
}

double K(double x,double s)
{
    return std::exp(x - s);
}
template<size_t n>
mvector<real, n> solve(double a, double b,double l)
{
    real h = (b - a) / n;
    matrix<real,n,n> m;
    mvector<real,n> vect, res;
    for(int i = 0; i < n; i++)
    {
        vect[i] = f(a+i*h);
        for(int j = 0; j < n; j++)
        {
            m[i][j] = -K(a+i*h,a+j*h) * 2;
            if(j == 0 || j == n - 1)
            {
                m[i][j] =  -K(a+i*h,a+j*h);
            }
        }
    }
    m *= l * h / 2;
    m += matrix<real,n,n>('E');
    res = method_of_gauss(m, vect, false);
    return res;

}

template <size_t n>
void view(real a, real b,real init_l, real step_l, int steps)
{
    std::vector<mvector<real, n>> res(steps);

    std::ofstream fout("res_n=" + std::to_string(n) + ".dat");
    real h = (b - a)/n;
    for(int l = 0;l < steps;l++)
        res[l] = solve<n>(a, b, l*step_l + init_l);
    for(int i = 0;i < n;i++){
        fout<<i*h + a<<"\t";
        for(int l = 0;l < steps;l++)
            fout<<res[l][i]<<"\t";
        fout<<"\n";
    }
}

constexpr int step = 5;

int main()
{

    view<10>(0.0, 1.0, 0.9, 0.01, 11);
    view<20>(0.0, 1.0, 0.0, 0.1, 11);
    view<50>(0.0, 1.0, 0.0, 0.1, 11);
    view<100>(0.0, 1.0, 0.0, 0.1, 11);
    return 0;
}
