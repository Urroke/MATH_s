#include "runge_kutta.h"

template <typename type, size_t order, size_t size>
runge_kutta<type, order, size>& runge_kutta<type, order, size>::operator=(std::array<func<type, size>, size> exemp)
{
    F = exemp;
}

template <typename type, size_t order, size_t size>
func<type, size>& runge_kutta<type, order, size>::operator[](const size_t& index)
{
    if(index >= size) throw "index outside of array";
    return F[index];
}

template <typename type, size_t order, size_t size>
mvector<type, size> runge_kutta<type, order, size>::operator()(const mvector<type, size>& init_value,const type& t, const type& tao)
{
    std::array<mvector<type, size>, order> k;
    mvector<type, size> k_p, sum, res;

    const double eps = 0.00001;

    res = init_value;

    for(int i = 0;i < order;i++){
        do
        {
            k_p = k[i];
            sum *= 0;

            for(int j = 0;j < order;j++)
                sum += table.a[i][j]*k[j];

            sum *= tao;
            sum += init_value;

            for(int j = 0;j < size;j++)
                k[i][j] = F[j](sum, t + tao*table.c[j]);

         } while((k_p - k[i]).magnitude() > eps);

            res += tao*table.b[i]*k[i];
        }
        return res;
}
