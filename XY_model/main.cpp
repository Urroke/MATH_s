#include <iostream>
#include <random>
#include "../math_objects/m_vector.h"
#include <ctime>
#include <fstream>
#include <array>
#include <mpi.h>
#include <chrono>
#include <iomanip>

#define N 3
#define size 36
constexpr int repeats_struct = 25;
constexpr int config = 10;
constexpr int await_time = 5000;
constexpr int observation_time = 10000;
constexpr double T1 = 0.6;
constexpr double T2 = 1.0;
constexpr int temps = 20;
constexpr double eps = 0.0001;
constexpr double density = 0.6;
std::mt19937 gen(std::time(nullptr));
constexpr auto max_val = double(gen.max());
int quant = (gen.max())/(size) + 1;

struct system_data
{
    double m[observation_time];
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

mvector<double, N> random_normal()
{
    double x = uniform_distribution(-1.0, 1.0);
    double y = uniform_distribution(-1.0, 1.0);
    double z = uniform_distribution(-1.0, 1.0);
    mvector<double, N> res = {x, y, z};
    return res.normalized();
}

void init_system(mvector<double, N> (&system)[size][size][size], double& p, bool (&not_zero)[size][size][size])
{
    double count;
    do{
        count = 0;
        for(int i = 0;i < size;i++)
            for(int j = 0;j < size;j++)
                for(int k = 0;k < size;k++)
                    if(uniform_distribution(0.0, 1.0) < density){
                        system[i][j][k] = {0, 0, 1};
                        not_zero[i][j][k] = true;
                        count++;
                    } else {
                        system[i][j][k] = {0, 0, 0};
                        not_zero[i][j][k] = false;
                    }
    }while(std::fabs(count/(size*size*size) - density) > eps);
    p = count/(size*size*size);
}

double get_m(mvector<double, N> (&system)[size][size][size], const double& p)
{
    mvector<double, N> res;
    for(int i = 0;i < size;i++)
        for(int j = 0;j < size;j++)
            for(int k = 0;k < size;k++)
                res += system[i][j][k];
    return res.magnitude()/p;
}

double get_c(mvector<double, N> (&system)[size][size][size])
{
    return 0;
}

system_data metropolys_algorythm(mvector<double, N> (&system)[size][size][size],
const double& T,const size_t& await_t, const size_t& obser_t, const double& p, bool (&not_zero)[size][size][size])
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
            if(not_zero[x][y][z]){
                old_state = system[x][y][z];
                system[x][y][z] = random_normal();
                dE = (old_state - system[x][y][z])*(system[(x + 1)%size][y][z]+
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
            data.add_values(get_m(system, p), get_c(system));
    }
    return data;
}

int main(int argc, char* argv[])
{
    int rank, size_syst;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size_syst);
    double p;
    bool not_zero[size][size][size];
    mvector<double, N> model[size][size][size], model_c[size][size][size];
    system_data result;
    for(int i = 0;i < repeats_struct;i++){
        init_system(model_c, p, not_zero);
        for(int j = 0;j < config;j++){
        auto start = std::chrono::system_clock::now();
            for(int a = 0;a < size;a++)
                for(int aa = 0;aa < size;aa++)
                    for(int aaa = 0;aaa < size;aaa++)
                        model[a][aa][aaa] = model_c[a][aa][aaa];
            std::cout<<"configur - "<<j<<"\n";
            for(int T = temps - 1;T >= 0;T--){
                std::cout<<T<<"\n";
                result = metropolys_algorythm(model, T1 + T*(T2 - T1)/temps, await_time, observation_time, p, not_zero);
                std::ofstream fout("result0.6/res_"+ std::to_string(size) + "_" + std::to_string(T1 + T*(T2 - T1)/temps) + "_" + std::to_string(rank) + ".dat", std::ios_base::app);
                double m = 0, m_2 = 0, m_4 = 0, val;
                for(int j = 0;j < observation_time;j++){
                    val = result.m[j];
                    m += val;
                    m_2 += val*val;
                    m_4 += val*val*val*val;
                }
                fout<<setprecision(15)<<m/observation_time<<"\t"<<m_2/observation_time<<"\t"<<m_4/observation_time<<"\n";
                fout.close();
            }
            auto end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end-start;
            std::cout<< elapsed_seconds.count() << "s\n";
        }
    }
    MPI_Finalize();
}
