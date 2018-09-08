#ifndef FUNCTION_OBJECT_H_INCLUDED
#define FUNCTION_OBJECT_H_INCLUDED
#include "../support_libs.h"

template <typename input,typename output>
class math_function{
private:
    output(*func)(input);

    int C(int n,int k);

public:

    template <typename T>
    using enable_type_arithmetic = typename std::enable_if<std::is_arithmetic<T>::value,void>::type;

    math_function();

    math_function(output(*exemp)(input));

    ~math_function();

    template<typename temp = enable_type_arithmetic<output>>
    output operator()(const input& argument);

    template <typename temp1 = enable_type_arithmetic<input>,
            typename temp2 = enable_type_arithmetic<output>>
    output derivative(input argument,int n,int degree,double delta);

    template <typename temp1 = enable_type_arithmetic<input>,
            typename temp2 = enable_type_arithmetic<output>>
    output integral(double a,double b);
};

#include "function_object.cpp"
#endif 
