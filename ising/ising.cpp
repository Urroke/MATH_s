#include <iostream>
#include <random>
#include <chrono>
#include <mpi/mpi.h>
#include <string>
#include <fstream>
#include <iomanip>
#include "../math_objects/m_vector.h"
#include <cstdlib>

#define L 64
#define config 50
#define await 9000
#define init_await 0
#define observation 150000
#define temps 20
#define T1 1.5
#define T2 3.5

using spin = int;

std::mt19937 gen(std::time(nullptr));
constexpr auto max_val = double(gen.max());
int quant = gen.max()/L + 1;
std::uniform_int_distribution<int> dist(0, 1);

struct system_data
{
    double m[observation];
    double e[observation];
    size_t repeats = 0, iter = 0;

    void add_values(const double& m1, const double& e1)
    {
        m[iter] = m1;
        e[iter] = e1;
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

double get_e(spin (&system)[L][L])
{
    double res = 0;
    for(int i = 0;i < L;i++)
        for(int j = 0;j < L;j++)
            res += system[i][j]*(system[i][(j + 1)%L] + system[i][(j - 1 + L)%L] + system[(i + 1)%L][j]+system[(i - 1 + L)%L][j]);
    return std::abs(res);
}

system_data wolff_algorythm(spin (&system)[L][L], const double& T,const size_t& await_t, const size_t& obser_t)
{
    system_data res;
    double chance = std::exp(-2.0/T) - 1;
    bool chosen[L][L];
    size_t x, y, x_, y_;
    int sign;
    std::vector<spin> klaster_x, klaster_y;
    static size_t turns = 8;

    for(int t = 0;t < await_t + obser_t;t++){
        for(int i = 0;i < turns;i++){
            x = gen()/quant;
            y = gen()/quant;
            klaster_x.resize(1);
            klaster_y.resize(1);
            klaster_x[0] = x;
            klaster_y[0] = y;
            for(int k = 0;k < L;k++)
                for(int j = 0;j < L;j++)
                    chosen[k][j] = false;
            chosen[x][y] = true;
            sign = dist(gen)*2 - 1;
            for(int j = 0;j < klaster_x.size();j++){
                if(!chosen[(klaster_x[j] + 1)%L][klaster_y[j]])
                if(uniform_distribution(0.0 ,1.0) < chance*system[(klaster_x[j] + 1)%L][klaster_y[j]]*system[klaster_x[j]][klaster_y[j]]){
                    x_ = (klaster_x[j] + 1)%L;
                    y_ = klaster_y[j];
                    chosen[x_][y_] = true;
                    system[x_][y_] = sign;
                    klaster_x.push_back(x_);
                    klaster_y.push_back(y_);
                }
               if(!chosen[(klaster_x[j] + L - 1)%L][klaster_y[j]])
                if(uniform_distribution(0.0 ,1.0) < chance*system[(klaster_x[j] + L - 1)%L][klaster_y[j]]*system[klaster_x[j]][klaster_y[j]]){
                    x_ = (klaster_x[j] + L - 1)%L;
                    y_ = klaster_y[j];
                    chosen[x_][y_] = true;
                    system[x_][y_] = sign;
                    klaster_x.push_back(x_);
                    klaster_y.push_back(y_);
                }
                if(!chosen[klaster_x[j]][(klaster_y[j] + 1)%L])
                if(uniform_distribution(0.0 ,1.0) < chance*system[klaster_x[j]][(klaster_y[j] + 1)%L]*system[klaster_x[j]][klaster_y[j]]){
                    x_ = klaster_x[j];
                    y_ = (klaster_y[j] + 1)%L;
                    chosen[x_][y_] = true;
                    system[x_][y_] = sign;
                    klaster_x.push_back(x_);
                    klaster_y.push_back(y_);
                }
                if(!chosen[klaster_x[j]][(klaster_y[j] + L - 1)%L])
                if(uniform_distribution(0.0 ,1.0) < chance*system[klaster_x[j]][(klaster_y[j] + L - 1)%L]*system[klaster_x[j]][klaster_y[j]]){
                    x_ = klaster_x[j];
                    y_ = (klaster_y[j] + L - 1)%L;
                    chosen[x_][y_] = true;
                    system[x_][y_] = sign;
                    klaster_x.push_back(x_);
                    klaster_y.push_back(y_);
                }
            }
        }
        if(t >= await_t)
            res.add_values(get_m(system), 0);
    }
    return res;
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
            res.add_values(get_m(system), get_e(system));
    }
    return res;
}

int main(int argc, char* argv[])
{
    string directory = "fresh";
    std::system(("mkdir " + directory).c_str());
    int rank, size;
    MPI_Init(&argc, &argv);

    system_data result;
    spin system[L][L];

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    for(int i = 0;i < config;i++){
        init_system(system);

        metropolys_algorythm(system, T1, 1, 0);

        std::cout<<"config - "<<i<<"\n";
        auto start_c= std::chrono::system_clock::now();
        for(int T = temps;T >= 0;T--){
            auto start = std::chrono::system_clock::now();

            result = metropolys_algorythm(system, T1 + T*(T2 - T1)/temps, await, observation);

            std::ofstream fout(directory + "/" + std::to_string(L) + "_" + std::to_string(T1 + T*(T2 - T1)/temps) + "_" + std::to_string(rank) + ".dat", std::ios_base::app);
            double m = 0, m_2 = 0,e = 0, e_2 = 0;
            for(int j = 0;j < observation;j++){
                m += result.m[i];
                e += result.e[i];
                m_2 += std::pow(result.m[i], 2);
                e_2 += std::pow(result.e[i], 2);
            }
            m /= observation;
            e /= observation;
            m_2 /= observation;
            e_2 /= observation;
            auto end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end-start;
            fout<<m<<"\t"<<m_2<<"\t"<<e<<"\t"<<e_2<<"\n";
        }
        auto end_c = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds_c = end_c-start_c;
        std::cout<<elapsed_seconds_c.count()<<"\n";
    }

    MPI_Finalize();
}
