#include "../little_math/little_math.h"
#include "../math_objects/m_vector.h"

int main()
{
    constexpr size_t N = 3;
    constexpr size_t temps = 8;
    constexpr size_t length = 10000;
    constexpr size_t L = 48;
    size_t found = 0;
    constexpr double T1 = 1.06;
    constexpr double T2 = 1.1;
    size_t stat_n = 0;
    double m_4, m_2, m, r, m_, hi, kum, m_4_l = 0.0, m_2_l = 0.0, m_l = 0.0, m_err = 0.0, hi_err = 0.0, kum_err = 0.0;
    std::ofstream fout("1Aresults_" + std::to_string(L) + ".dat");
    fout<<"T\tKUM\tKUM_ERR\tM\tM_ERR\tHI\tHI_ERR\n";
    std::vector<double> m_p, hi_p, kum_p;
    for(int T = 0;T < temps;T++)
    {
        for(int d = 0;d < 2;d++)
        for(int j = 0;j < N;j++){
            std::ifstream fin("results2/res_"+ std::to_string(L) + "_" + std::to_string((T*(T2 - T1)/temps + T1)) + "_" + std::to_string(j) + ".dat");
            std::ofstream fout("results_2/res_"+ std::to_string(L) + "_" + std::to_string((T*(T2 - T1)/temps + T1)) + "_" + std::to_string(j) + ".dat");
             while(fin>>r){
                fout<<r/length<<"\t";
                fin>>r;
                fout<<r/length<<"\t";
                fin>>r;
                fout<<r/length<<"\n";
             }
        }
    }
}
