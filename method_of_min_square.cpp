#include "math_objects/matrix.h"
#include "math_objects/function_object.h"
#include "little_math/little_math.h"
#include <fstream>

double log(double x){;}

double exp(double x){;}

template <typename type, size_t size>
void convertor(const mvector<type, size>& data, type(*func)(type))
{
    for(int i = 0;i < size;i++)
        data[i] = func(data[i]);
}

int main()
{
    constexpr int L = 1000;
    constexpr int N = 5;
    constexpr int polynom_degree = 1;
    mvector<double, L> data[N], MCS_s;
    mvector<double, polynom_degree + 1> coefs;
    mvector<double, N> a, b;
    double delta;
    std::ifstream fin("data.dat");
    std::ofstream result("value.dat");
    std::ofstream polynoms("polynoms.dat");

    fin>>MCS_s;
    for(int i = 0;i < N;i++){
        fin>>data[i];
        convertor(data[i], log);
    }

    for(int i = 0;i < N;i++){
        coefs = method_of_min_suare<double, 100, polynom_degree>(MCS_s.get_interval<100,200>(),
                                                                data[i].get_interval<100,200>());
        a[i] = coefs[0];
        b[i] = coefs[1];
    }

    delta = std::sqrt((summ_power(a,2) - summ_power(a,1))/(n*(n-1)));
}
