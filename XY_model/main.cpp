#include <iostream>
#include <random>
#include "../math_objects/m_vector.h"
#include <ctime>
#include <fstream>
#include <array>

#define N 3
#define size 8
#define repeats_struct 1
#define repeats_for_avarage 40
#define await_time 0
#define observation_time 500

using matrix = std::array<std::array<std::array<mvector<double, N>, size>, size>, size>;

struct system_data
{
    mvector<double, observation_time> m;
    mvector<double, observation_time> c;
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

double uniform_distribution(std::mt19937& gen,const double& a, const double& b)
{
    return (b - a)*gen()/double(4294967295) + a;
}

mvector<double, N> random_normal(std::mt19937& gen)
{
    double x, y, z;
    x = uniform_distribution(gen, -1.0, 1.0);
    y = uniform_distribution(gen, -1.0, 1.0);
    z = uniform_distribution(gen, -1.0, 1.0);
    mvector<double, N> res;
    res = {x, y, z};
    return res.normalized();
}

void init_system(matrix& system, const double& p)
{
    std::mt19937 gen(std::time(0));
    double x, y, z;
    for(int i = 0;i < size;i++)
        for(int j = 0;j < size;j++)
            for(int k = 0;k < size;k++)
                if(uniform_distribution(gen, 0.0, 1.0) < p)
                    system[i][j][k] = {0, 0, 1};
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

system_data metropolys_algorythm(matrix system, const double& T)
{
    system_data data;
    std::mt19937 gen(std::time(0));
    mvector<double, N> old_state;
    double dE, r;
    size_t x, y, z;
    int quant = (4294967295)/(size) + 1;
    for(int t = 0;t < await_time + observation_time;t++){
        for(int i = 0;i < size*size*size;i++){
            x = gen()/quant;
            y = gen()/quant;
            z = gen()/quant;
            if(system[x][y][z].magnitude() > 0){
                old_state = system[x][y][z];
                system[x][y][z] = random_normal(gen);
                dE = -1*(system[x][y][z] - old_state)*(system[(x + 1)%size][y][z]+
                    system[(x - 1)%size][y][z]+system[x][(y + 1)%size][z]+
                    system[x][(y - 1)%size][z]+system[x][y][(z + 1)%size]+
                    system[x][y][(z - 1)%size]);
                if(dE > 0){
                    r = uniform_distribution(gen, 0.0 ,1.0);
                    if(r > std::exp(-dE/T))
                        system[x][y][z] = old_state;
                }
            }
        }
        if(t >= await_time)
            data.add_values(get_m(system), get_c(system));
    }
    return data;
}

int main()
{
    const double p = 1;
    system_data result;
    matrix system;

    for(int i = 0;i < repeats_struct;i++){
        std::cout<<i<<"\n";
        init_system(system, p);
        for(int j = 0;j < repeats_for_avarage;j++){
            result += metropolys_algorythm(system, 1.1);
        }
    }

    result.avarege();
    std::ofstream fout("gaiz.dat");
    fout<<result.m<<endl;
}
