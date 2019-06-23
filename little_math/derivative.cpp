#include "little_math.h"

template <typename type, size_t number_lattice, size_t degree>
std::function<type(type)> derivative(std::function<type(type)> func, type aprox_interval)
{
    std::function<type(type)> result = [=](type value)->type{
        type h = aprox_interval/(number_lattice - 1);
        mvector<type, number_lattice> x, y;
        for(int i = 0;i < number_lattice;i++){
            x[i] = value - aprox_interval/2 + h*i;
            y[i] = func(x[i]);
        }
        polynom<type, degree> res(method_of_min_suare<type, number_lattice, degree>(x, y));
        res.derivative();
        return res(value);
    };
    return result;
}
