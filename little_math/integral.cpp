#include "little_math.h"

template <typename input, typename output>
output newton_kotes(math_function<input, output> func, size_t degree, input lhs, input rhs, size_t n)
{
    input h = (rhs - lhs)/n;
    output res = 0;

    for(int i = 0;i < n;i++)
        for(int j = 1;j <= degree + 1;j++)
            res += newton_kotes_table[degree - 1][j]*func(lhs + i*h + (j-1)*h/degree);
    res *= h;
    res /= newton_kotes_table[degree - 1][0];
    return res;
}

/*template <typename input,typename output>
output gauss_legendre(output(*func)(input), input a, input b)
{
    output res = 0;

    for(int i = 0;i < 6;i++)
        res += GLQ_weight[i]*func((a + b)/2 + GLQ_points[i]*(b - a)/2);
    return (b - a)*res/2;
}*/

template <typename input,typename output>
output gauss_legendre(std::function<output(input)> func, input a, input b)
{
   output res = 0;

    for(int i = 0;i < 6;i++)
        res += GLQ_weight[i]*func((a + b)/2 + GLQ_points[i]*(b - a)/2);
    return (b - a)*res/2;
}

