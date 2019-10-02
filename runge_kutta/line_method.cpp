#include "line_method.h"

int main()
{
    const std::string load = "[....................]";
    const double M_PI = 3.14159265;
    constexpr size_t t_steps_graph = 17;
    constexpr size_t t_steps = std::pow(2, t_steps_graph);
    const double a = 0.0;
    const double b = 1.0;
    const double tao = 0.00001;
    const double lambda = 1.0;
    constexpr size_t order = 3;
    constexpr size_t number_lattice = 200;
    std::array<mvector<double,number_lattice>, t_steps_graph> results;
    std::function<double(double)> right = [=](double x) -> double{
        return 30.0;
    };
    std::function<double(double)> left = [=](double x) -> double{
        return 20.0;
    };
    std::function<double(double)> init = [=](double x) -> double{
        return 20.0 + 10.0*x
           + 5.0*sin(M_PI*x)
           + 4.0*sin(2*M_PI*x)
           - 3.0*sin(3*M_PI*x)
           + 5.0*sin(4*M_PI*x)
           - 2.0*sin(5*M_PI*x)
           - 3.0*sin(6*M_PI*x)
           + 4.0*sin(10*M_PI*x)
           + 8.0*sin(12*M_PI*x)
           - 10.0*sin(18*M_PI*x);
    };
    std::function<double(double, double)> part = [=](double x, double t) -> double{
        return 0;
    };

    butcher_table<order> tabe1;
    std::ifstream fin("table1.dat");
    fin>>tabe1.a>>tabe1.b>>tabe1.c;
    fin.close();

    runge_kutta<double, order, number_lattice> rung(tabe1);
    line_method<double, number_lattice> method(init, left, right, part, a, b, type_problem::first, lambda);

    std::array<int, t_steps_graph> points;
    for(int i = 0;i < t_steps_graph;i++)
        points[i] = std::pow(2, i);

    int iter = 0;
    for(int t = 1;t < t_steps;t++){
        if(t % (t_steps/20) == 0){
            system("cls");
            std::string load_c = load;
            for(int i = 0;i < 20*t/t_steps;i++)
                load_c[1 + i] = char(219);
            std::cout<<load_c;
        }
        if(t == points[iter]){
                results[iter] = method(rung, tao);
                iter ++;
        }else method(rung, tao);
    }
    std::ofstream res("res_line_method.dat");
    res<<"X\tU\n";
    double h = (b - a)/(number_lattice - 1);
    for(int j = 0;j < number_lattice;j++){
            res<<a + j*h;
            for(int t = 0;t < t_steps_graph;t++)
                res<<"\t"<<results[t][j];
            res<<"\n";
    }
}
