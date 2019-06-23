#ifndef LINE_METHOD_H_INCLUDED
#define LINE_METHOD_H_INCLUDED
#include "runge_kutta.h"
#include "../little_math/little_math.h"

template <typename type, size_t number_lattice>
class line_method
{
private:
    std::function<type(type)> initial_condition;
    std::function<type(type)> left_boundary_condition;
    std::function<type(type)> right_boundary_condition;
    std::function<type(type)> left_part;
    mvector<type, number_lattice> U, f;
    type lyambda;
    type left_boundary;
    type right_boundary;
public:
    line_method() = delete;

    line_method(std::function<type(type)> initial_condition, std::function<type(type)> left_boundary_condition,
                std::function<type(type)> right_boundary_condition, std::function<type(type)> left_part);

    template<size_t order>
    mvector<type, number_lattice> operator()(runge_kutta<type, order, number_lattice> rung,
                                             type left_boundary, type right_boundary, type lambda,
                                             type t, type tao, std::string type_problem){

        std::array<std::function<double(mvector<double, number_lattice>, double)> , number_lattice> F;
        type h = (right_boundary - left_boundary)/(number_lattice - 1);
        for(int i = 1;i < number_lattice - 1;i++){
            U[i] = initial_condition(left_boundary + i*h);
            f[i] = left_part(left_boundary + i*h);
            F[i] = [=](mvector<double, number_lattice> u, double t)-> double{
                return lambda/(h*h)*(u[i + 1] - 2*u[i] + u[i - 1]) + f[i];
            };
        }
        if(type_problem == "f"){
            U[0] = left_boundary_condition(left_boundary);
            U[number_lattice - 1] = right_boundary_condition(right_boundary);
            F[0] = derivative<double, 3, 2>(left_boundary_condition, 0.01);
            F[number_lattice - 1] = derivative<double, 3, 2>(right_boundary_condition, 0.01);
        }
        if(type_problem == "s"){

        }
        if(type_problem == "fm"){

        }
        if(type_problem == "sm"){

        }

        rung = F;

        return rung_4(U, t, tao);
    }

    ~line_method() = default;
};

#endif // LINE_METHOD_H_INCLUDED
