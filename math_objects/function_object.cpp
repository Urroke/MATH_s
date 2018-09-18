#include "function_object.h"

template <typename input,typename output>
class math_function<input, output>::solve_proxi{
private:
    output(*func)(input);
    output delta(input a, input b)
    {
        return (func(b) - func(a))/(b - a);
    }

public:
    solve_proxi(output(*exemp)(input))
    {
        this->func = exemp;
    }

    output operator()(input left_border, input right_border, output eps){

        input a = left_border;
        input b = right_border;
        input c = (a + b)/2;
        output err;
        output P0, P1, P2;
        output A, B, C;
        output res;
        do{
            P0 = func(a);
            P1 = delta(a, c);
            P2 = (delta(c , b) - P1)/(b - a);

            A = P2;
            B = (P1 - P2*(a + c))/2;
            C = P0 - P1*a + P2*a*c;

            res = (-B + std::pow((B*B - A*C), 0.5))/A;

            if(res < a || res > b)
                res = (-B - std::pow((B*B - A*C), 0.5))/A;

            if(func(res)*func(a) <= 0){
                err = std::abs(b - res);
                b = res;
            }else{
                err = std::abs(a - res);
                a = res;
            }
        }while(err > eps);
        return res;
    }
};

template <typename input,typename output>
int math_function<input,output>::C(int n,int k)
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

template <typename input,typename output>
math_function<input,output>::math_function(){;}

template <typename input,typename output>
math_function<input,output>::math_function(output(*exemp)(input))
{
    this->func = exemp;
}

template <typename input,typename output>
math_function<input,output>::~math_function(){;}

template <typename input, typename output>
template <typename type>
typename math_function<input, output>::solve_proxi math_function<input, output>::operator==(const type& exemp)
{
    return typename math_function<input, output>::solve_proxi(func);
}

template <typename input,typename output>
template <typename temp>
output math_function<input,output>::operator()(const input& argument)
{
    return this->func(argument);
}

template <typename input,typename output>
template <typename temp2>
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
template <typename temp2>
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
