#include "../little_math/little_math.h"
#include "../math_objects/m_vector.h"

int main()
{
    constexpr size_t N = 3;
    constexpr size_t temps = 20;
    constexpr size_t length = 1;
    constexpr size_t L = 24;
    size_t found = 0;
    constexpr double T1 = 0.6;
    constexpr double T2 = 1.0;
    size_t stat_n = 0;
    double m_4, m_2, m, r, m_, hi, kum, m_4_l = 0.0, m_2_l = 0.0, m_l = 0.0, m_err = 0.0, hi_err = 0.0, kum_err = 0.0;
    std::ofstream fout("1Aresults_" + std::to_string(L) + ".dat");
    fout<<"T\tKUM\tKUM_ERR\tM\tM_ERR\tHI\tHI_ERR\n";
    std::vector<double> m_p, hi_p, kum_p;
    std::string dir[2] = {"result0.6", ""};
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
            std::ifstream fin(dir[d] + "/res_"+ std::to_string(L) + "_" + std::to_string((T*(T2 - T1)/temps + T1)) + "_" + std::to_string(j) + ".dat");
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
                        found++;
                        if(found % 10 == 0)
                        {
                            m_l /= 10*length;
                            m_2_l /= 10*length;
                            m_4_l /= 10*length;
                            m_p.push_back(m_l/(L*L*L));
                            hi_p.push_back((m_2_l - std::pow(m_l, 2))/(T*(T2 - T1)/temps + T1));
                            kum_p.push_back(0.5*(3 - m_4_l/std::pow(m_2_l, 2)));
                            m_l = 0.0;
                            m_2_l = 0.0;
                            m_4_l = 0.0;
                            stat_n ++;
                        }

                    }
        }
        if(found == 0) continue;
        std::cout<<m<<"\n";
        m /= found*length;
        m_2 /= found*length;
        m_4 /= found*length;
        kum = 0.5*(3 - m_4/std::pow(m_2, 2));
        m_ = m/(L*L*L);
        hi = (m_2 - std::pow(m, 2))/(T*(T2 - T1)/temps + T1);

        for(int i = 0;i < m_p.size();i++){
            m_err += std::pow(m_p[i] - m_, 2);
            hi_err += std::pow(hi_p[i] - hi, 2);
            kum_err += std::pow(kum_p[i] - kum, 2);
        }

        m_err /= m_p.size()*(m_p.size() - 1);
        hi_err /= m_p.size()*(m_p.size() - 1);
        kum_err /= m_p.size()*(m_p.size() - 1);

        m_err = std::sqrt(m_err);
        hi_err = std::sqrt(hi_err);
        kum_err = std::sqrt(kum_err);

        fout<<(T*(T2 - T1)/temps + T1)<<"\t"<<kum<<"\t"<<kum_err<<"\t"<<m_<<"\t"<<m_err<<"\t"<<hi<<"\t"<<hi_err<<"\n";
    }
}
