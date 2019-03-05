#include "runge_kutta.h"
#include "richardson_extropolate.h"

int main()
{
    constexpr size_t order = 4;
    constexpr size_t size_system = 2;
    constexpr size_t steps_for_extropolate = 3;
    const double step = 0.1;
    const double t_0 = 0.0;
    const double T = 10.0;

    mvector<double, size_system> init_data;
    butcher_table<order> table;

    std::ifstream fin("table.dat");
    fin>>table.a>>table.b>>table.c;
    fin.close();

    runge_kutta<double, order, size_system> rung_4(table);

    std::array<std::function<double(mvector<double, size_system>, double)> , size_system> F = {
    [=](mvector<double, size_system> u, double t)-> double{
        return u[1];
    },
    [=](mvector<double, size_system> u, double t)-> double{
        return -u[0];
    }};

    rung_4 = F;
    init_data = {0, 1};

    std::ofstream fout("res.dat");
    /*for(int i = 0;i < int((T - t_0)/step);i++){
        fout<<t_0 + i*step<<"\t"<<init_data[0]<<"\n";
        init_data = rung_4(init_data, t_0 + i*step, step);
    }*/
    mvector<size_t, steps_for_extropolate> dividers;
    dividers = {1, 2, 4};
    for(int i = 0;i < int((T - t_0)/step);i++){
        fout<<t_0 + i*step<<"\t"<<init_data[0]<<"\n";
        init_data = richardson_extropolate(rung_4, t_0 + i*step, step, dividers, init_data);
    }
}
