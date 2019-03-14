#include <iostream>
#include <random>
#include <chrono>
#include <mpi/mpi.h>
#include <string>
#include <fstream>
#include <iomanip>
#include "../math_objects/m_vector.h"

#define calc_code ///свой номер в списке группы
#define L 512
#define config 10
#define await 10000
#define observation 3000
#define temps 100
#define T1 2.0
#define T2 2.5

using spin = int;

std::mt19937 gen(std::time(nullptr));
constexpr auto max_val = double(gen.max());
int quant = gen.max()/L + 1;

struct system_data
{
    double m[observation];
    size_t repeats = 0, iter = 0;

    void add_values(const double& m1, const double& c1)
    {
        m[iter] = m1;
        iter++;
    }
};

inline double uniform_distribution(const double& a, const double& b)
{
    return (b - a)*gen()/max_val + a;
}

inline void init_system(spin (&system)[L][L])
{
    for(int i = 0;i < L;i++)
        for(int j = 0;j < L;j++)
            system[i][j] = 1;
}

double get_m(spin (&system)[L][L])
{
    double res = 0;
    for(int i = 0;i < L;i++)
        for(int j = 0;j < L;j++)
            res += system[i][j];
    return std::abs(res);
}

system_data metropolys_algorythm(spin (&system)[L][L], const double& T,const size_t& await_t, const size_t& obser_t)
{
    system_data res;
    double _exp[2] = {std::exp(-4.0/T), std::exp(-8.0/T)}, r;
    size_t x, y;
    int dE;
    for(int t = 0;t < await_t + obser_t;t++){
        for(int i = 0;i < L*L;i++){
            x = gen()/quant;
            y = gen()/quant;
            system[x][y] *= -1;
            dE = -2*system[x][y]*(system[(x + 1)%L][y]+
                system[(x - 1 + L)%L][y]+system[x][(y + 1)%L]+
                system[x][(y - 1 + L)%L]);
            if(dE > 0){
                r = uniform_distribution(0.0 ,1.0);
                if(r > _exp[dE/4 - 1])
                    system[x][y] *= -1;
            }
        }
        if(t >= await_t)
            res.add_values(get_m(system), 0);
    }
    return res;
}

int main(int argc, char* argv[])
{
    int rank, size;
    MPI_Init(&argc, &argv);
    system_data result;
    spin system[L][L];
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    auto start = std::chrono::system_clock::now();
    for(int i = 0;i < config;i++){
        init_system(system);
        metropolys_algorythm(system, T1, 10000, 0);
        std::cout<<"config - "<<i<<"\n";
        for(int T = temps;T >= 0;T--){
            std::cout<<T1 + T*(T2 - T1)<<"\n";
            result = metropolys_algorythm(system, T1 + T*(T2 - T1)/temps, await, observation);
            std::ofstream fout(std::to_string(calc_code) + "res_"+ std::to_string(L) + "_" + std::to_string(T)+ "_" + std::to_string(i) + "_" + std::to_string(rank) + ".dat");
            for(int j = 0;j < observation;j++)
                fout<<setprecision(15)<<result.m[j]<<"\n";
            fout.close();
        }
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout<< elapsed_seconds.count() << "s\n";
    MPI_Finalize();
}
