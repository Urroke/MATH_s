#ifndef POLYNOMIAL_H_INCLUDED
#define POLYNOMIAL_H_INCLUDED

template <typename type>
type legandre(type x,size_t n)
{
    type* P = new type[n + 1];
    type res;
    P[0] = 1; P[1] = x;
    for(int i = 2;i <= n;i++)
        P[i] = (2 - double(1)/i)*P[i - 1]*x - (1 - double(1)/n)*P[i - 2];
    res = P[n];
    delete[] P;
    return res;
}

#endif
