#include "little_math.h"

template <typename type, size_t size>
class polynom
{
private:
    mvector<type, size + 1> coefs;
public:
    polynom(const mvector<type, size + 1>& exemp)
    {
        coefs = exemp;
    }

    type operator()(const type& x)
    {
        type result = 0;
        for(int i = 0;i <= size;i++)
            result += std::pow(x, size - i)*coefs[i];
        return result;
    }

    ~polynom(){;}
};

template <typename type, size_t n>
type summ_power(mvector<type, n> exemp, size_t degree)
{
    type result = 0;
    for(int i = 0;i < n;i++)
        result += std::pow(exemp[i], degree);
    result /= n;
    return result;
}

template <typename type, size_t n, size_t degree>
mvector<type, degree + 1> method_of_min_suare(mvector<type, n> x, mvector<type, n> y)
{
    matrix<type, degree + 1, degree + 1> A;
    mvector<type, n> xy;
    mvector<type, degree + 1> res, b;

    for(int i = 0; i <= degree;i++)
        for(int j = 0;j <= degree ;j++)
            A[i][j] = summ_power(x, degree - j + i);

    for(int i = 0;i < degree + 1;i++){
        for(int j = 0;j < n;j++)
            xy[j] = y[j]*std::pow(x[j], i);
        b[i] = summ_power(xy, 1);
    }

    res = method_of_gauss(A, b);

    return res;
}
