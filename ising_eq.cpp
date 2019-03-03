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
    std::chrono::time_point<std::chrono::system_clock> start, end;
    constexpr size_t size = 8;
    const size_t N = 300;
    constexpr size_t time = 3000;
    std::uniform_int_distribution<int> dist(0, 45);
    std::mt19937 gen(std::time(0));
    int quant = (4294967295)/(size*size) + 1;
    size_t point, x, y;
    double exp[2], r, atime = 0.0;
    double temp[27] = {
        0.5, 0.7, 0.9, 1.1, 1.3, 1.5, 1.7, 1.9, 2.1,
        2.15, 2.2, 2.25, 2.3, 2.35, 2.4, 2.45, 2.5,
        2.55, 2.6, 2.65, 2.7, 2.75, 2.8, 3, 3.2, 3.4, 3.6};
    int dE, saveT;
    matrix<int, size, size> cell;
    double meq[27] ,eeq[27];

    for(int i = 0;i< 27;i++){
        meq[i] = 0;
        eeq[i] = 0;
    }

    std::ofstream fout("mequ8.dat", std::ios::app), fout1("eequ8.dat", std::ios::app);
    std::ifstream fouts("save.dat");

    for(int n = 1;n <= N;n++){
        std::cout<<100*double(n)/N<<" % Времени осталось  -  "<<atime*(N - n)/3600000000<<"  ч  "<<
        atime*(N - n)/60000000<<"  м  "<<atime*(N - n)/1000000<<"  c\n";
        start = std::chrono::system_clock::now();
        exp[0] = std::exp(-4/temp[26]);
        exp[1] = std::exp(-8/temp[26]);

        for(int i = 0;i < size;i++)
            for(int j = 0;j < size;j++)
                cell[i][j] = 1;

        for(int mcss = 1;mcss <= time*4;mcss++)
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
        for(int tmp = 26;tmp >= 0;tmp--){
            exp[0] = std::exp(-4/temp[tmp]);
            exp[1] = std::exp(-8/temp[tmp]);
            for(int mcss = 1;mcss <= time;mcss++){
                meq[tmp] += m(cell);
                eeq[tmp] += e(cell);
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
        }
        end = std::chrono::system_clock::now();
        atime *= (n - 1);
        atime += std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
        atime /= n;
        system("clear");
    }
    for(int i = 0;i < 27;i++){
        fout<<temp[i]<<"\t"<<meq[i]/(N*time)<<"\n";
        fout1<<temp[i]<<"\t"<<eeq[i]/(N*time)<<"\n";
    }
}
