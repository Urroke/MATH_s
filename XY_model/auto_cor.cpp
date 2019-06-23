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
#define size 100
constexpr int repeats_struct = 20;
constexpr int config = 15;
constexpr int observation_time = 10000;
constexpr double TC = 1.0813;
constexpr double eps = 0.0001;
constexpr double density = 0.8;
constexpr int t_w_count = 4;
constexpr int t_w[t_w_count] = {20, 40, 80, 160};
std::mt19937 gen(std::time(nullptr));
constexpr auto max_val = double(gen.max());
int quant = (gen.max())/(size) + 1;
mvector<double, N> model_c[size][size][size], model[size][size][size], model_w[t_w_count][size][size][size];;
bool not_zero[size][size][size];

struct system_data
{
    double m[t_w_count][observation_time];
    double c[t_w_count][observation_time];

    system_data()
    {
        for(int j = 0;j < t_w_count;j++)
            for(int i = 0;i < observation_time;i++){
                m[j][i] = 0;
                c[j][i] = 0;
            }
    }

    system_data operator+=(system_data exemp)
    {
        for(int j = 0;j < t_w_count;j++)
            for(int i = 0;i < observation_time;i++){
                m[j][i] += exemp.m[j][i];
                c[j][i] += exemp.c[j][i];
            }
        return *this;
    }

    system_data operator/=(double exemp)
    {
        for(int j = 0;j < t_w_count;j++)
            for(int i = 0;i < observation_time;i++){
                m[j][i] /= exemp;
                c[j][i] /= exemp;
            }
        return *this;
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

void init_system(double& p)
{
    double count;
    do{
        count = 0;
        for(int i = 0;i < size;i++)
            for(int j = 0;j < size;j++)
                for(int k = 0;k < size;k++)
                    if(uniform_distribution(0.0, 1.0) < density){
                        model_c[i][j][k] = {0, 0, 1};
                        not_zero[i][j][k] = true;
                        count++;
                    } else {
                        model_c[i][j][k] = {0, 0, 0};
                        not_zero[i][j][k] = false;
                    }
    }while(std::fabs(count/(size*size*size) - density) > eps);
    p = count/(size*size*size);
}

mvector<double, N> get_m(const double& p)
{
    mvector<double, N> res;
    for(int i = 0;i < size;i++)
        for(int j = 0;j < size;j++)
            for(int k = 0;k < size;k++)
                res += model[i][j][k];
    return res/(p*size*size*size);
}

double get_cor(int index, const double& p)
{
    double res = 0;
    for(int i = 0;i < size;i++)
        for(int j = 0;j < size;j++)
            for(int k = 0;k < size;k++)
                res += model[i][j][k]*model_w[index][i][j][k];
    return res/(p*size*size*size);
}

system_data metropolys_algorythm(const double T, const size_t obser_t, const double p)
{
    system_data data;
    mvector<double, N> old_state, m_w[t_w_count];
    double dE, r;
    size_t x, y, z;
    for(int t = 1;t <= obser_t;t++){
        for(int i = 0;i < size*size*size;i++){
            x = gen()/quant;
            y = gen()/quant;
            z = gen()/quant;
            if(not_zero[x][y][z]){
                old_state = model[x][y][z];
                model[x][y][z] = random_normal();
                dE = (old_state - model[x][y][z])*(model[(x + 1)%size][y][z]+
                    model[(x - 1)%size][y][z]+model[x][(y + 1)%size][z]+
                    model[x][(y - 1)%size][z]+model[x][y][(z + 1)%size]+
                    model[x][y][(z - 1)%size]);
                if(dE > 0){
                    r = uniform_distribution(0.0 ,1.0);
                    if(r > std::exp(-dE/T))
                        model[x][y][z] = old_state;
                }
            }
        }


        for(int i = 0;i < t_w_count;i++){
            if(t == t_w[i]){
                for(int a = 0;a < size;a++)
                    for(int aa = 0;aa < size;aa++)
                        for(int aaa = 0;aaa < size;aaa++)
                            model_w[i][a][aa][aaa] = model[a][aa][aaa];
                m_w[i] = get_m(p);
            }
            if(t > t_w[i]){
                data.m[i][t - 1] = get_m(p)*m_w[i];
                data.c[i][t - 1] = get_cor(i, p);
            }
        }
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

    system_data result;
    for(int i = 0;i < repeats_struct;i++){

        init_system(p);

        for(int j = 0;j < config;j++){
            auto start = std::chrono::system_clock::now();
            for(int a = 0;a < size;a++)
                for(int aa = 0;aa < size;aa++)
                    for(int aaa = 0;aaa < size;aaa++)
                        model[a][aa][aaa] = model_c[a][aa][aaa];
            std::cout<<"configur - "<<j<<"\n";
            result += metropolys_algorythm(TC, observation_time, p);

            auto end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end-start;
            std::cout<< elapsed_seconds.count() << "s\n";
        }

        result /= config;
        for(int j = 0;j < t_w_count;j++)
        {
            std::ofstream fout1("cor/l"+ std::to_string(t_w[j]) + "_" + std::to_string(rank) + ".dat", std::ios_base::app);
            for(int k = 0;k < observation_time;k++)
                fout1<<result.c[j][k]<<"\t";
            fout1<<"\n";

            std::ofstream fout2("cor/r"+ std::to_string(t_w[j]) + "_" + std::to_string(rank) + ".dat", std::ios_base::app);
            for(int k = 0;k < observation_time;k++)
                fout2<<result.m[j][k]<<"\t";
            fout2<<"\n";
        }
    }
    MPI_Finalize();
}
