#ifndef RUNGE_KUTTA_H_INCLUDED
#define RUNGE_KUTTA_H_INCLUDED
#include "../math_objects/matrix.h"
#include <functional>

template <size_t size>
struct butcher_table
{
    mvector<double, size> b, c;
    matrix<double, size, size> a;
};

template <typename type, size_t size>
using func = std::function<type(mvector<type, size>, type)>;

template <typename type, size_t order, size_t size>
class runge_kutta{
private:
    butcher_table<order> table;
    std::array<func<type, size>, size> F;
public:
    runge_kutta() = delete;
    runge_kutta(const butcher_table<order>& exemp):table(exemp){;}
    ~runge_kutta() = default;

    mvector<type, size> operator()(const mvector<type, size>& init_value, const type& t, const type& tao);
    runge_kutta<type, order, size>& operator=(std::array<func<type, size>, size> exemp);
    func<type, size>& operator[](const size_t& index);
};

#include "runge_kutta.cpp"
#endif
