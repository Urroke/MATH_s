#include "../little_math/little_math.h"
#include "../math_objects/m_vector.h"

int main()
{
    constexpr size_t N = 3;
    constexpr size_t temps = 20;
    constexpr size_t config = 250;
    constexpr size_t L = 24;
    size_t not_found = 0;
    constexpr double T1 = 1.0;
    constexpr double T2 = 1.4;
    double m_4, m_2, m, r;
    std::ofstream fout("0Aresults_" + std::to_string(L) + ".dat");
    fout<<"T\tKUM\tM\tHI\n";
    for(int T = 0;T < temps;T++)
    {
        m *= 0;
        m_2 *= 0;
        m_4 *= 0;
        not_found = 0;
        for(int j = 0;j < N;j++){
            std::ifstream fin("results0/res_"+ std::to_string(L) + "_" + std::to_string((T*(T2 - T1)/temps + T1)) + "_" + std::to_string(j) + ".dat");
                if(fin.is_open()){
                    for(int k = 0;k < config;k++){
                        fin>>r;
                        m += r;
                        fin>>r;
                        m_2 += r;
                        fin>>r;
                        m_4 += r;
                    }
                } else {not_found++;}
        }
        std::cout<<m<<"\n";
        m /= (N - not_found)*4000*config;
        m_2 /= (N - not_found)*4000*config;
        m_4 /= (N- not_found)*4000*config;
        fout<<(T*(T2 - T1)/temps + T1)<<"\t"<<0.5*(3 - m_4/std::pow(m_2, 2))
        <<"\t"<<m/(L*L*L)<<"\t"<<(m_2 -
        std::pow(m, 2))/(T*(T2 - T1)/temps + T1)<<"\n";
    }
}
