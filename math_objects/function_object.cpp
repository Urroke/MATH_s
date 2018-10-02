#include "function_object.h"

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
template <typename temp2>
output math_function<input,output>::derivative(input argument,int n,int degree,input delta)
{
    output res = 0;
    output part;
    int fact = 1;
    output oper = 1;
    if(n == 1)
        for(int i = 1;i <= degree;i++){
            part = 0;
            fact *= i;
            for(int j = 0;j <= i;j++)
                part += func(argument + delta*j)*C(i,j)*std::pow(-1, i - j);
            part /= i*pow(delta,i)*fact;
            res += part;
            std::cout<<part<<"\n";
        }
    else
        for(int i = 1;i <= degree;i++){
            part = 0;
            for(int j = 0;j <= i;j++)
                part += derivative(argument + delta*j,n - 1,degree,delta)*C(i,j)*std::pow(-1,i - j);
            part /= i*pow(delta,i);
            res += part;
        }
    return res;
}

