#include "little_math.h"

template <typename input, typename output,typename temp =typename  enable_if<std::is_arithmetic<input>::value&&
                                                         std::is_arithmetic<output>::value, void>::type>
output method_of_parabola(output(*func)(input) ,input left_border, input right_border, output eps){

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
