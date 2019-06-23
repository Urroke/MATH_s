#ifndef LINE_METHOD_H_INCLUDED
#define LINE_METHOD_H_INCLUDED
#include "runge_kutta.h"
#include "../little_math/little_math.h"

enum class type_problem:int{
    first = 0,
    second = 1,
    first_mixed = 2,
    second_mixed = 3
};

template <typename type, size_t number_lattice>
class line_method
{
private:
    std::function<type(type)> init_condition;
    std::function<type(type)> left_boundary_condition;
    std::function<type(type)> right_boundary_condition;
    std::function<type(type, type)> left_part;
    mvector<type, number_lattice> U, f;
    type lyambda;
    type left_boundary;
    type right_boundary;
    type t = 0.0;
    type_problem task_type;
    type lambda;
    type h;
    bool initialize = false;

public:
    line_method() = default;

    line_method(std::function<type(type)> init_condition, std::function<type(type)> left_boundary_condition, std::function<type(type)> right_boundary_condition,
                std::function<type(type, type)> left_part, type left_boundary, type right_boundary, type_problem task_type, type lambda)
    {
        this->left_boundary_condition = left_boundary_condition;
        this->right_boundary_condition = right_boundary_condition;
        this->init_condition = init_condition;
        this->left_part = left_part;
        this->left_boundary = left_boundary;
        this->right_boundary = right_boundary;
        this->task_type = task_type;
        this->lambda = lambda;
        h = (right_boundary - left_boundary)/(number_lattice - 1);
        for(int i = 1;i < number_lattice - 1;i++)
            U[i] = init_condition(left_boundary + i*h);
        U[0] = left_boundary_condition(left_boundary);
        U[number_lattice - 1] = right_boundary_condition(right_boundary);
    }

    template<size_t order>
    mvector<type, number_lattice> operator()(runge_kutta<type, order, number_lattice> rung, type tao){
        std::array<std::function<double(mvector<double, number_lattice>, double)> , number_lattice> F;
        for(int i = 1;i < number_lattice - 1;i++){
            f[i] = left_part(left_boundary + i*h, t);
            F[i] = [=](mvector<double, number_lattice> u, double t)-> double{
                return lambda/(h*h)*(u[i + 1] - 2*u[i] + u[i - 1]) + f[i];      ///ื่ํ่ f
            };
        }
        switch(task_type){
            case type_problem::first:
                std::function<type(type)> der_left = derivative<double, 3, 2>(left_boundary_condition, 0.01);
                std::function<type(type)> der_right = derivative<double, 3, 2>(right_boundary_condition, 0.01);
                F[0] = [=](mvector<double, number_lattice> u, double t)-> double{
                    return der_left(t);
                };
                F[number_lattice - 1] = [=](mvector<double, number_lattice> u, double t)-> double{
                    return der_right(t);
                };
            break;
        }
        rung = F;
        U = rung(U, t, tao);
        t += tao;
        return U;
    }
    ~line_method() = default;
};

#endif // LINE_METHOD_H_INCLUDED
