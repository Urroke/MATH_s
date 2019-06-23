#include "../little_math/little_math.h"
#include "../math_objects/m_vector.h"

int main()
{
    constexpr size_t N = 4;
    constexpr size_t temps = 20;
    constexpr size_t length = 1;
    constexpr size_t L = 64;
    size_t found = 0;
    constexpr double T1 = 1.8;
    constexpr double T2 = 2.8;
    size_t stat_n = 0;
    double m_4, m_2, m, r, m_, hi, kum, m_4_l = 0.0, m_2_l = 0.0, m_l = 0.0, m_err = 0.0, hi_err = 0.0, kum_err = 0.0;
    std::ofstream fout("1Aresults_" + std::to_string(L) + ".dat");
    fout<<"T\tKUM\tM\tHI\n";
    std::vector<double> m_p, hi_p, kum_p;
    std::string dir[2] = {"results_freshr", "results_0"};
    for(int T = 0;T < temps;T++)
    {
        m *= 0.0;
        m_2 *= 0.0;
        m_4 *= 0.0;
        m_4_l = 0.0;
        m_2_l = 0.0;
        m_ = 0.0;
        m_l = 0.0;
        m_err = 0.0;
        hi_err = 0.0;
        kum_err = 0.0;
        found = 0;
        for(int d = 0;d < 2;d++)
        for(int j = 0;j < N;j++){
            std::ifstream fin(dir[d] + "/" + std::to_string(L) + "_" + std::to_string((T*(T2 - T1)/temps + T1)) + "_" + std::to_string(j) + ".dat");
                if(fin.is_open())
                    while(fin>>r){
                        m += r;
                        m_l += r;
                        fin>>r;
                        m_2 += r;
                        m_2_l += r;
                        fin>>r;
                        m_4 += r;
                        m_4_l += r;
                        fin>>r;
                        found++;
                    }
        }
        if(found == 0) continue;
        std::cout<<found<<"\n";
        m /= found*length;
        m_2 /= found*length;
        m_4 /= found*length;
        kum = 0.5*(3 - m_4/std::pow(m_2, 2));
        m_ = m/(L*L*L);
        hi = (m_2 - std::pow(m, 2))/(T*(T2 - T1)/temps + T1);

        fout<<(T*(T2 - T1)/temps + T1)<<"\t"<<kum<<"\t"<<m_<<"\t"<<hi<<"\n";
    }
}
