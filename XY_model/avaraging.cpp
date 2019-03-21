#include "../little_math/little_math.h"
#include "../math_objects/m_vector.h"

int main()
{
    constexpr size_t N = 3;
    constexpr size_t temps = 1;
    constexpr size_t size = 200;
    constexpr size_t config = 33;
    constexpr size_t L = 48;
    constexpr double T1 = 2.0;
    constexpr double T2 = 2.0;

    mvector<double, size> m, ex;

    for(int T = 0;T < temps;T++)
    {
        std::ofstream fout("0m_T = " + std::to_string(T*(T2 - T1)/temps + T1) + "_" + std::to_string(L) + ".dat");
        m *= 0;
        for(int i = 0;i < config;i++){
            for(int j = 0;j < N;j++){
                std::ifstream fin("m/res_"+ std::to_string(L) + "_" + std::to_string(T)+ "_" + std::to_string(i) + "_" + std::to_string(j) + ".dat");
                    if(fin.is_open()){
                        fin>>ex;
                        m += ex;
                    } else std::cout<<"kek";
            }
        }
        m /= (N*config);
        fout<<"T\tM\n1\t1\n";
        for(int i = 0;i < size;i++)
            fout<<i + 2<<"\t"<<m[i]<<"\n";
    }
}
