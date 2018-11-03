#include "math_objects/matrix.h"
#include "little_math/little_math.h"
#include <random>
#include <chrono>

template <size_t size>
double e(const matrix<int, size, size>& exemp)
{
    double res = 0;
    for(int i = 0;i < size;i++)
        for(int j = 0;j < size;j++)
            res += (exemp[(i + 1)%size][j] +
                   exemp[i][(j + 1)%size] +
                   exemp[(size + i - 1)%size][j] +
                   exemp[i][(size + j - 1)%size])*exemp[i][j];
    res /= 2*size*size;
    return res;
}

template <size_t size>
double m(const matrix<int, size, size>& exemp)
{
    double res = 0;
    for(int i = 0;i < size;i++)
        for(int j = 0;j < size;j++)
            res += exemp[i][j];
    res = std::fabs(res)/(size*size);
    return res;
}

int main()
{
    constexpr size_t size = 8;
    const size_t N = 10000;
    constexpr size_t time = 2000;

    std::mt19937 gen(std::time(0));
    int quant = (4294967295)/(size*size) + 1;
    size_t point, x, y;
    double exp[2], r;
    double temp[27] = {
        0.5, 0.7, 0.9, 1.1, 1.3, 1.5, 1.7, 1.9, 2.1,
        2.15, 2.2, 2.25, 2.3, 2.35, 2.4, 2.45, 2.5,
        2.55, 2.6, 2.65, 2.7, 2.75, 2.8, 3, 3.2, 3.4, 3.6};

    int dE;
    matrix<int, size, size> cell;
    std::ofstream fout("m(t)8.dat"), fout1("e(t)8.dat");

    for(int tmp = 0;tmp < 27;tmp++){
        exp[0] = std::exp(-4/temp[tmp]);
        exp[1] = std::exp(-8/temp[tmp]);
        mvector<double, N> magnetization, energy;

        for(int n = 0;n < N;n++){
            std::cout<<100*double(tmp*N + n)/(27*N)<<" %";

           for(int i = 0;i < size;i++)
                for(int j = 0;j < size;j++)
                    cell[i][j] = 1;

            for(int mcss = 1;mcss <= time;mcss++){
                magnetization[mcss - 1] += m(cell);
                energy[mcss - 1] += e(cell);
                for(int i = 0;i < size*size;i++){
                    point = gen()/quant;
                    x = point % size;
                    y = point / size;
                    dE = 2*cell[y][x]*(
                            cell[(y + 1)%size][x] +
                            cell[(y + size - 1)%size][x] +
                            cell[y][(x + 1)%size] +
                            cell[y][(x + size - 1)%size]);
                    cell[y][x] *= -1;
                    if(dE > 0){
                        r = std::generate_canonical<double, 32>(gen);
                        if(r > exp[dE/4 - 1]){
                            cell[y][x] *= -1;
                        }
                    }
                }
            }
            system("cls");
        }
        for(int mcss = 1;mcss <= time;mcss++){
            fout<<mcss<<"\t"<<magnetization[mcss - 1]/N + 1<<"\n";
            fout1<<mcss<<"\t"<<energy[mcss - 1]/N<<"\n";
        }
    }
}
