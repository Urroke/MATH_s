#include "function_object.h"

template <typename input,typename output>
math_function<input,output>::math_function(output(*exemp)(input))
{
    this->func= exemp;
}

template <typename input,typename output>
math_function<input,output>::math_function(std::function<output(input)> exemp)
{
    this->func = exemp;
}

template <typename input,typename output>
math_function<input,output>::~math_function(){;}

template <typename input,typename output>
output math_function<input,output>::operator()(input argument)
{
    return this->func(argument);
}

template <typename input,typename output>
math_function<input, output>& math_function<input, output>::operator=(math_function<input, output> exemp)
{
    this->func = exemp.func;
    return *this;
}


template <typename input,typename output>
math_function<input, output> math_function<input,output>::operator+=( math_function<input, output> exemp)
{
    std::function<output(input)> old_func = func;
    std::function<output(input)> old_exemp = exemp.func;
    std::function<output(input)> res = [=](input x)->output{return old_func(x) + old_exemp(x);};
    func = res;
    return *this;
}

template <typename input,typename output>
math_function<input, output> math_function<input,output>::operator-=( math_function<input, output> exemp)
{
    std::function<output(input)> old_func = func;
    std::function<output(input)> old_exemp = exemp.func;
    std::function<output(input)> res = [=](input x)->output{return old_func(x) - old_exemp(x);};
    func = res;
    return *this;
}

template <typename input,typename output>
math_function<input, output> math_function<input,output>::operator*=( math_function<input, output> exemp)
{
    std::function<output(input)> old_func = func;
    std::function<output(input)> old_exemp = exemp.func;
    std::function<output(input)> res = [=](input x)->output{return old_func(x) * old_exemp(x);};
    func = res;
    return *this;
}

template <typename input,typename output>
math_function<input, output> math_function<input,output>::operator/=( math_function<input, output> exemp)
{
    std::function<output(input)> old_func = func;
    std::function<output(input)> old_exemp = exemp.func;
    std::function<output(input)> res = [=](input x)->output{return old_func(x) / old_exemp(x);};
    func = res;
    return *this;
}

/*template <typename in, typename out>
math_function<in, out> operator+( math_function<in, out> lhs, math_function<in, out> rhs)
{
    std::function<out(in)> old_func = lhs.func;
    std::function<out(in)> old_exemp = rhs.func;
    std::function<out(in)> res = [=](in x)->out{return old_func(x) + old_exemp(x);};
    math_function<in, out> result = res;
    return result;
}*/

/*template <typename input,typename output>
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
}*/

