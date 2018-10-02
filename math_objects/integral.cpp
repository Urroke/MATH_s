#include "function_object.h"

template <typename input,typename output>
class math_function<input, output>::integral{
private:
    output(*func)(input);
public:
    integral(output(*exemp)(input))
    {
        this->func = exemp;
    }

    output newton_cotes(input a, input b, input h, size_t degry)
    {

    }
    output gauss_legendre(input a, input b,  size_t degry)
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

};
