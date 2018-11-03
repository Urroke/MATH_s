#ifndef FUNCTION_OBJECT_H_INCLUDED
#define FUNCTION_OBJECT_H_INCLUDED
#include "../support_libs.h"

template <typename input,typename output>
class math_function{
private:
    output(*func)(input);
    class integral;
    int C(int n,int k);

    template <typename lhs, typename rhs>
    static constexpr bool is_converte = std::is_convertible<lhs, rhs>::type;

public:
    template <typename lhs, typename rhs>
    using enable_is_converte = typename std::enable_if<is_converte<lhs, rhs>,void>::type;


    template <typename T>
    using enable_type_arithmetic = typename std::enable_if<std::is_arithmetic<T>::value,void>::type;

    math_function();

    math_function(output(*exemp)(input));

    ~math_function();

    template <typename temp = enable_type_arithmetic<output>>
    output operator()(const input& argument);

    template <typename temp2 = enable_type_arithmetic<output>>
    output derivative(input argument, int n, int degree, input delta);

};

#include "function_object.cpp"
#endif
