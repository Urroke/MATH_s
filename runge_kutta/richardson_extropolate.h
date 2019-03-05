#ifndef RICHARDSON_EXTROPOLATE_H_INCLUDED
#define RICHARDSON_EXTROPOLATE_H_INCLUDED
#include "runge_kutta.h"
#include "../little_math/little_math.h"

template <typename type, size_t order, size_t size, size_t N>
mvector<type, size> richardson_extropolate(runge_kutta<type, order, size>& method,const type& t_0,
const type& tao,const mvector<size_t, N>& dividers,const mvector<type, size>& init_value)
{
    matrix<type, N, N> A;
    std::array<mvector<type, size>, N> b;
    mvector<type, N> b_for_system, init_aprox;
    mvector<type, size> res, init_data;
    type divider;

    for(int i = 0;i < N;i++){
        divider = tao/dividers[i];
        init_data = init_value;
        for(int j = 0;j < dividers[i];j++)
            init_data = method(init_data, t_0 + divider*j, divider);
        b[i] = init_data;
        A[i][0] = 1;
        for(int j = 1;j < N;j++)
            A[i][j] = std::pow(divider, j + order);
    }

    for(int i = 0;i < size;i++){
        for(int j = 0;j < N;j++)
            b_for_system[j] = b[j][i];
        res[i] = method_of_gauss(A, b_for_system, true)[0];
    }
    return res;
}

#endif // RICHARDSON_EXTROPOLATE_H_INCLUDED
