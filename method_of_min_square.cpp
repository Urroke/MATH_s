#include "math_objects/matrix.h"
#include "math_objects/function_object.h"
#include "little_math/little_math.h"
#include <fstream>

template <typename type, size_t size>
void convertor(mvector<type, size>& data, type(*func)(type))
{
    for(int i = 0;i < size;i++)
        data[i] = func(data[i]);
}

int main()
{
    constexpr int left = 100;
    constexpr int right = 200;
    constexpr int L = 1000;
    constexpr int N = 5;
    constexpr int polynom_degree = 1;
    mvector<double, L> data[N], MCS_s;
    mvector<double, polynom_degree + 1> coefs;
    mvector<double, N> a, b;
    mvector<double, right - left> aprox;
    double delta, beta;
    std::ifstream fin("data.dat");
    std::ofstream result("value1.dat");
    std::ofstream aprox_("aprox1.txt");
    std::ofstream beta_("beta2.dat");

    for(int i = 0;i < N;i++){
        fin>>data[i];
        convertor(data[i], std::log);
    }

    for(int i = 0;i < L;i++)
        MCS_s[i] = i + 1;
    convertor(MCS_s, std::log);

    for(int i = 0;i < N;i++){
        coefs = method_of_min_suare<double, right - left, polynom_degree>(MCS_s.get_interval<left, right>(),
                                                                data[i].get_interval<left, right>());
        a[i] = coefs[0];
        b[i] = coefs[1];
        beta_<<a[i]<<"\n";
    }

    delta = std::sqrt((summ_power(a,2) - summ_power(a,1)*summ_power(a,1))/(N*(N-1)));
    beta = summ_power(a, 1);

    coefs[0] = summ_power(a, 1);
    coefs[1] = summ_power(b, 1);

    polynom<double, polynom_degree> res(coefs);

    for(int i = 0; i < right - left;i++)
        aprox[i] = res(MCS_s[i + left]);
    convertor(aprox, std::exp);

    result<<"beta = "<<beta<<" +- "<<delta<<std::endl;
    aprox_<<aprox;

}
