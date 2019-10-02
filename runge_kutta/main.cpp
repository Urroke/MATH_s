#include "runge_kutta.h"
#include "richardson_extropolate.h"

int main()
{
    constexpr size_t order = 3;
    constexpr size_t size_system = 4;
    constexpr size_t steps_for_extropolate = 3;
    const double step = 0.01;
    const double t_0 = 0.0;
    const double T = 10.0;
    const double l = 0.5;
    const double g = 10;
    const double k = 150;
    const double m = 1;

    mvector<double, size_system> cont1, extr1, cont2, extr2, cont0, extr0;
    butcher_table<order> tabe1, tabel2;

    std::ifstream fin("table1.dat");
    fin>>tabe1.a>>tabe1.b>>tabel2.b>>tabe1.c;
    tabel2.a = tabe1.a;
    tabel2.c = tabe1.c;

    fin.close();

    runge_kutta<double, order, size_system> rung_4(tabe1), rung_4_(tabel2);

    std::array<std::function<double(mvector<double, size_system>, double)> , size_system> F = {
    [=](mvector<double, size_system> u, double t)-> double{
        return u[2];
    },
    [=](mvector<double, size_system> u, double t)-> double{
        return u[3];
    },
    [=](mvector<double, size_system> u, double t)-> double{
        return -g*std::sin(u[0])/u[1];
    },
    [=](mvector<double, size_system> u, double t)-> double{
        return u[1]*u[2]*u[2] + g*std::cos(u[0]) + k*(l - u[1])/m;
    }};

    rung_4 = F;
    rung_4_ = F;
    cont1 = {1.5705, l, 0.0, 0.0};
    extr1 = cont1;
    cont0 = cont1;
    extr0 = cont1;
    std::ofstream fout("solve.dat");
    std::ofstream fout1("solve_extr.dat");
    /*for(int i = 0;i < int((T - t_0)/step);i++){
        fout<<t_0 + i*step<<"\t"<<init_data[0]<<"\n";
        init_data = rung_4(init_data, t_0 + i*step, step);
    }*/
    mvector<size_t, steps_for_extropolate> dividers;
    dividers = {1, 2, 4};
    for(int i = 0;i < int((T - t_0)/step);i++){
        fout<<t_0 + i*step<<"\t"<<(cont1 - rung_4_(cont0, t_0 + i*step, step)).max_abs()<<"\t"<<cont1;
        fout1<<t_0 + i*step<<"\t"<<(extr1 - richardson_extropolate(rung_4_, t_0 + i*step, step, dividers, extr0)).max_abs()<<"\t"<<extr1;
        extr0 = extr1;
        cont0 = cont1;
        extr1 = richardson_extropolate(rung_4, t_0 + i*step, step, dividers, extr0);
        cont1 = rung_4(cont0, t_0 + i*step, step);
    }
}
