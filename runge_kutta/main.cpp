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

    mvector<double, size_system> cont1, extr1, cont2, extr2;
    butcher_table<order> tabe1, tabel2;

    std::ifstream fin("table.dat");
    fin>>tabe1.a>>tabe1.b>>tabel2.b>>tabe1.c;
    tabel2.a = tabe1.a;
    tabel2.c = tabe1.c;

    fin.close();

    runge_kutta<double, order, size_system> rung_4(tabe1);
    runge_kutta<double, order, size_system> rung_4_(tabel2);

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
    cont2 = cont1;
    extr1 = cont1;
    extr2 = cont1;
    std::ofstream fout("res.dat");
    /*for(int i = 0;i < int((T - t_0)/step);i++){
        fout<<t_0 + i*step<<"\t"<<init_data[0]<<"\n";
        init_data = rung_4(init_data, t_0 + i*step, step);
    }*/
    mvector<size_t, steps_for_extropolate> dividers;
    dividers = {1, 2, 4};
    for(int i = 0;i < int((T - t_0)/step);i++){
        fout<<t_0 + i*step<<"\t"<<cont1[0]<<"\t"<<cont1[1]
        <<"\t"<<cont2[0]<<"\t"<<cont2[1]<<"\t"<<std::fabs(cont1[0] - cont2[0])
        <<"\t"<<std::fabs(cont1[1] - cont2[1])<<"\t"<<extr1[0]<<"\t"<<extr1[1]
        <<"\t"<<extr2[0]<<"\t"<<extr2[1]<<"\t"<<std::fabs(extr1[0] - extr2[0])
        <<"\t"<<std::fabs(extr1[1] - extr2[1])<<"\n";
        extr1 = richardson_extropolate(rung_4, t_0 + i*step, step, dividers, extr1);
        extr2 = richardson_extropolate(rung_4_, t_0 + i*step, step, dividers, extr2);
        cont1 = rung_4(cont1, t_0 + i*step, step);
        cont2 = rung_4_(cont2, t_0 + i*step, step);
    }
}
