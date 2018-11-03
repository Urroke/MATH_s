#include "little_math/little_math.h"
#include "math_objects/function_object.h"

int main()
{
    constexpr size_t length_aprox = 5;
    const double eps = 0.001;
    mvector<double, 2> pol;
    mvector<double, 2000> m;
    mvector<double, length_aprox> x,y;
    std::ifstream fin("m(t)8.dat");
    std::ofstream fout("m(t)8eq.dat");
    double r;

    for(int i = 0;i < length_aprox;i++)
        x[i] = i;

    for(int i = 0;i < 27;i++){
        std::cout<<i<<"\n";
        for(int j = 0;j < 2000;j++){
            fin>>m[j];
            fin>>m[j];
        }
        for(int j = 0;j < 2000 - length_aprox;j++){
            for(int k = j;k < j + length_aprox;k++)
                y[k - j] = m[k];

            pol = method_of_min_suare<double, length_aprox, 1>(x, y);
            if(std::fabs(pol[0]) < eps){
                fout<<j + 1<<"\t"<<m[j]<<"\n";
                break;
            }
        }
    }
}
