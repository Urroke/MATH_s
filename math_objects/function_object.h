#ifndef FUNCTION_OBJECT_H_INCLUDED
#define FUNCTION_OBJECT_H_INCLUDED
#include "../support_libs.h"

template <typename input,typename output>
class math_function{
private:
    std::function<output(input)> func;
    //std::vector<std::function<output(input)>> function_stack;
    template <typename lhs, typename rhs>
    static constexpr bool is_converte = std::is_convertible<lhs, rhs>::type;

public:
    template <typename lhs, typename rhs>
    using enable_is_converte = typename std::enable_if<is_converte<lhs, rhs>,void>::type;


    template <typename T>
    using enable_type_arithmetic = typename std::enable_if<std::is_arithmetic<T>::value,void>::type;

    math_function();

    math_function<input, output>& operator=(math_function<input, output> exemp);

    math_function<input, output> operator+=(math_function<input, output> exemp);
    math_function<input, output> operator-=(math_function<input, output> exemp);
    math_function<input, output> operator*=(math_function<input, output> exemp);
    math_function<input, output> operator/=(math_function<input, output> exemp);
    //template <typename in, typename out>
    //friend math_function<in, out> operator+(math_function<in, out> lhs, math_function<in, out> rhs);

    math_function(std::function<output(input)> exemp);

    math_function(output(*exemp)(input));

    ~math_function();

    output operator()(input argument);
};

#include "function_object.cpp"
#endif
