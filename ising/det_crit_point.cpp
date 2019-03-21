#include "../little_math/little_math.h"
#include "../math_objects/m_vector.h"

int main()
{
    constexpr size_t N = 12;
    constexpr size_t temps = 50;
    constexpr size_t size = 500;
    constexpr size_t config = 500;
    constexpr size_t L = 128;
    size_t not_found = 0;
    constexpr double T1 = 1.8;
    constexpr double T2 = 2.8;
    constexpr size_t c = 3;
    constexpr size_t folders = 2;
    size_t codes[c] = {3, 5 ,55};
    double m_4, m_2, m, r;
    std::ofstream fout("0Aresults_" + std::to_string(L) + ".dat");
    fout<<"T\tKUM\tM\tHI\n";
    for(int T = 0;T < temps;T++)
    {
        m *= 0;
        m_2 *= 0;
        m_4 *= 0;
        not_found = 0;
        for(int dir = 0;dir < folders;dir++)
            for(int code = 0;code < c;code++){
                std::cout<<code<<"\n";
                for(int i = 0;i < config;i++)
                    for(int j = 0;j < N;j++){
                        std::ifstream fin(std::to_string(dir) + "res/" + std::to_string(codes[code]) + "res_"+ std::to_string(L) + "_" + std::to_string(T)+ "_" + std::to_string(i) + "_" + std::to_string(j) + ".dat");
                            if(fin.is_open()){
                                for(int k = 0;k < size;k++){
                                    fin>>r;
                                    m_4 += r*r*r*r;
                                    m_2 += r*r;
                                    m += r;
                                }
                            } else {not_found++;}
                    }
            }
        std::cout<<not_found<<"\n";
        m /= (N*config*c*folders - not_found)*size;
        m_2 /= (N*config*c*folders - not_found)*size;
        m_4 /= (N*config*c*folders - not_found)*size;
        fout<<(T*(T2 - T1)/temps + T1)<<"\t"<<0.5*(3 - m_4/std::pow(m_2, 2))
        <<"\t"<<m/(L*L)<<"\t"<<(m_2 -
        std::pow(m, 2))/(T*(T2 - T1)/temps + T1)<<"\n";
    }
}
