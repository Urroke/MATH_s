#include "../little_math/little_math.h"
#include "../math_objects/m_vector.h"

int main()
{
    constexpr size_t N = 3;
    constexpr size_t temps = 40;
    constexpr size_t size = 2000;
    constexpr size_t config = 50;
    constexpr size_t L = 32;
    constexpr double T1 = 2.1;
    constexpr double T2 = 2.5;

    double m_4, m_2, m, r;
    std::ofstream fout("Aresults_" + std::to_string(L) + ".dat");
    for(int T = 0;T < temps;T++)
    {
        m *= 0;
        m_2 *= 0;
        m_4 *= 0;
        for(int i = 0;i < config;i++){
            for(int j = 0;j < N;j++){
                std::ifstream fin("res_"+ std::to_string(L) + "_" + std::to_string(T)+ "_" + std::to_string(i) + "_" + std::to_string(j) + ".dat");
                    if(fin.is_open()){
                        for(int k = 0;k < size;k++){
                            fin>>r;
                            m_4 += r*r*r*r;
                            m_2 += r*r;
                            m += r;
                        }
                    } else std::cout<<"kek";
            }

        }
        m /= N*config*size;
        m_2 /= N*config*size;
        m_4 /= N*config*size;
        fout<<(T*(T2 - T1)/temps + T1)<<"\t"<<0.5*(3 - m_4/std::pow(m_2, 2))
        <<"\t"<<m/(L*L)<<"\t"<<m_2 -
        std::pow(m, 2)/(T*(T2 - T1)/temps + T1)<<"\n";
    }
}
