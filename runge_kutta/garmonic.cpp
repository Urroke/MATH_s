#include "runge_kutta.h"
#include "richardson_extropolate.h"

int main()
{
    constexpr size_t order = 3;
    constexpr size_t size_system = 2;
    constexpr size_t steps_for_extropolate = 3;
    const double step = 0.001;
    const double t_0 = 0.0;
    const double T = 10.0;
    const double l = 0.5;
    const double g = 10;
    const double k = 150;
    const double m = 1;
    const double init_phi = 0.3;
    const double init_phi_v = 0;

    mvector<double, size_system> cont1, extr1, cont2, extr2;
    butcher_table<order> tabe1, tabel2;

    std::ifstream fin("table1.dat");
    fin>>tabe1.a>>tabe1.b>>tabe1.c;

    fin.close();

    runge_kutta<double, order, size_system> rung_4(tabe1);

    std::array<std::function<double(mvector<double, size_system>, double)> , size_system> F = {
    [=](mvector<double, size_system> u, double t)-> double{
        return u[1];
    },
    [=](mvector<double, size_system> u, double t)-> double{
        return -g*u[0]/l;
    }};


    std::function<double(double)>control = [=](double x)->double{
        return init_phi*std::cos(std::sqrt(g/l)*x) + init_phi_v*std::sin(std::sqrt(g/l)*x)/std::sqrt(g/l);
    };

    rung_4 = F;
    cont1 = {init_phi, init_phi_v};
    extr1 = cont1;
    std::ofstream fout("res.dat");
    /*for(int i = 0;i < int((T - t_0)/step);i++){
        fout<<t_0 + i*step<<"\t"<<init_data[0]<<"\n";
        init_data = rung_4(init_data, t_0 + i*step, step);
    }*/
    mvector<size_t, steps_for_extropolate> dividers;
    dividers = {1, 2, 4};
    for(int i = 0;i < int((T - t_0)/step);i++){
        fout<<t_0 + i*step<<"\t"<<control(t_0 + i*step)<<"\t"<<cont1;
        extr1 = richardson_extropolate(rung_4, t_0 + i*step, step, dividers, extr1);
        cont1 = rung_4(cont1, t_0 + i*step, step);
    }
}
