#include <iostream>
#include <random>
#include "../math_objects/m_vector.h"
#include <ctime>
#include <fstream>
#include <array>
#include <mpi.h>
#include <chrono>

#define N 3
#define size 32
#define repeats_struct 1
#define repeats_for_avarage 50
#define await_time 200
#define observation_time 200
#define T1 1.05
#define T2 1.65
#define T_steps 30

using matrix = std::array<std::array<std::array<mvector<double, N>, size>, size>, size>;
std::mt19937 gen(std::time(nullptr));
constexpr auto max_val = double(gen.max());
int quant = (gen.max())/(size) + 1;

struct system_data
{
    mvector<double, observation_time + 1> m;
    mvector<double, observation_time + 1> c;
    size_t repeats = 0, iter = 0;

    void add_values(const double& m1, const double& c1)
    {
        m[iter] = m1;
        c[iter] = c1;
        iter++;
    }

    system_data& operator+=(const system_data& exemp)
    {
        for(int i = 0;i < observation_time;i++)
            m[i] += exemp.m[i];
        c += exemp.c;
        repeats ++;
        return *this;
    }

    system_data avarege()
    {
        for(int i = 0;i < observation_time;i++)
            m[i] /= repeats;
        c /= repeats;
        return *this;
    }
};

double uniform_distribution(const double& a, const double& b)
{
    return (b - a)*gen()/max_val + a;
}

mvector<double, N> random_normal()
{
    double x = uniform_distribution(-1.0, 1.0);
    double y = uniform_distribution(-1.0, 1.0);
    double z = uniform_distribution(-1.0, 1.0);
    mvector<double, N> res = {x, y, z};
    return res.normalized();
}

void init_system(matrix& system, const double& p)
{
    double x, y, z;
    for(int i = 0;i < size;i++)
        for(int j = 0;j < size;j++)
            for(int k = 0;k < size;k++)
                if(uniform_distribution(0.0, 1.0) < p){
                    system[i][j][k] = {0, 0, 1};
                    system[i][j][k].not_zero = true;
                } else {
                    system[i][j][k] = {0, 0, 0};
                    system[i][j][k].not_zero = false;
                }
}

double get_m(matrix& system)
{
    mvector<double, N> res;
    for(int i = 0;i < size;i++)
        for(int j = 0;j < size;j++)
            for(int k = 0;k < size;k++)
                res += system[i][j][k];
    return res.magnitude()/(size*size*size);
}

double get_c(const matrix& system)
{
    return 0;
}

system_data metropolys_algorythm(matrix& system, const double& T,const size_t& await_t, const size_t& obser_t)
{
    system_data data;
    mvector<double, N> old_state;
    double dE, r;
    size_t x, y, z;
    for(int t = 0;t < await_t + obser_t;t++){
        for(int i = 0;i < size*size*size;i++){
            x = gen()/quant;
            y = gen()/quant;
            z = gen()/quant;
            if(true){
                old_state = system[x][y][z];
                system[x][y][z] = random_normal();
                dE = -1*(system[x][y][z] - old_state)*(system[(x + 1)%size][y][z]+
                    system[(x - 1)%size][y][z]+system[x][(y + 1)%size][z]+
                    system[x][(y - 1)%size][z]+system[x][y][(z + 1)%size]+
                    system[x][y][(z - 1)%size]);
                if(dE > 0){
                    r = uniform_distribution(0.0 ,1.0);
                    if(r > std::exp(-dE/T))
                        system[x][y][z] = old_state;
                }
            }
        }
        if(t >= await_t)
            data.add_values(get_m(system), get_c(system));
    }
    return data;
}

int main(int argc, char* argv[])
{
    int rank, size_syst;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size_syst);

    const double p = 1;
    matrix system, system_c;
    system_data data[T_steps + 1];
    auto start = std::chrono::system_clock::now();
    for(int i = 0;i < repeats_struct;i++)
        for(int j = 0;j < repeats_for_avarage;j++){
            std::cout<<j<<"@@@@@@@@@@@@@!\n";
            init_system(system, p);
            //metropolys_algorythm(system, T2, 20, 0);
            for(int T = T_steps;T >= 0;T--){
                std::cout<<T<<"\n";
                //std::cout<<double((T_steps - T) + j*(T_steps - T))/(T_steps*repeats_for_avarage)<<"\n";
                    data[T] += metropolys_algorythm(system, T1 + T*(T2 - T1)/T_steps, await_time, observation_time);
            }
        }
    for(int T = T_steps;T >= 0;T--){
        data[T].avarege();
        std::ofstream fout(std::to_string(size) + "n/gaiz_"+ std::to_string(T)+ std::to_string(rank) + ".dat");
        fout<<data[T].m<<endl;
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout<< elapsed_seconds.count() << "s\n";
    MPI_Finalize();
}
