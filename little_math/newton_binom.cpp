#include "little_math.h"

int C(size_t n,size_t k)
{
    int* binomial = new int[n+1];
    int res;
    binomial[0] = 1;
    for (int i = 1;i <= n;i++)
        binomial[i] = 0;

    for (int i = 0;i < n;i++)
        for(int j = i + 1;j > 0;j--)
            binomial[j] += binomial[j - 1];

    res = binomial[k];
    delete[] binomial;

    return res;
}
