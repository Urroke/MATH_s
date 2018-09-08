#include "function_object.h"

template <typename input,typename output>
int math_function<input,output>::C(int n,int k)
{
    int* binomial = new int[n+1];

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

template <typename input,typename output>
math_function<input,output>::math_function(){;}

template <typename input,typename output>
math_function<input,output>::math_function(output(*exemp)(input))
{
    this->func = exemp;
}

template <typename input,typename output>
math_function<input,output>::~math_function(){;}

template <typename input,typename output>
template <typename temp>
output math_function<input,output>::operator()(const input& argument)
{
    return this->func(argument);
}

template <typename input,typename output>
template <typename temp1,typename temp2>
output math_function<input,output>::derivative(input argument,int n,int degree,double delta)
{
    output res = 0;
    output part;
    output oper = 1;
    if(n == 1)
        for(int i = 1;i <= degree;i++){
            part = 0;
            for(int j = 0;j <= i;j++)
                part += func(argument + delta*j)*C(i,j)*std::pow(-1,j-1);
            part /= i*pow(delta,i);
            res += part;
        }
    else
        for(int i = 1;i <= degree;i++){
            part = 0;
            for(int j = 0;j <= i;j++)
                part += derivative(argument + delta*j,n - 1,degree,delta)*C(i,j)*std::pow(-1,j-1);
            part /= i*pow(delta,i);
            res += part;
        }
    return res;
}

template <typename input,typename output>
template <typename temp1,typename temp2>
output math_function<input,output>::integral(double a,double b)
{
    std::ifstream fin("Gaussian quadratures - Legendre.txt");

    output res = 0;
    double weight[6];
    double points[6];

    for(int i = 0;i < 6;i++){
        fin>>weight[i];
        fin>>points[i];
    }

    for(int i = 0;i < 6;i++)
        res += weight[i]*func((a + b)/2 + points[i]*(b - a)/2);
    return res;
}
