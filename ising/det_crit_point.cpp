#include "../little_math/little_math.h"
#include "../math_objects/m_vector.h"

int main()
{
    constexpr size_t count_thread = 4;
    constexpr size_t count_temperatures_on_interval = 20;
    constexpr size_t system_size = 64;
    constexpr double T1 = 1.8;
    constexpr double T2 = 2.8;
    constexpr int config_count  = 100;
    constexpr int count_group_for_error = 5;
    constexpr int count_directory = 5;
    constexpr int count_config_in_group = config_count/count_group_for_error;
    size_t found = 0;
    double m_4, m_2, m, r, m_, hi, kum, m_group , m_2_group, m_4_group;

    std::ofstream fout("results_for_L=" + std::to_string(system_size) + ".dat");
    fout<<"T\tU(L,T)\tU(L,T)_ERROR\tM\tM_ERROR\tHI\tHI_ERROR\n";

    std::array<double, count_config_in_group> m__group, hi_group, kum_group;
    for(int i = 0;i < count_group_for_error;i++){
        m__group[i] = 0;
        hi_group[i] = 0;
        kum_group[i] = 0;
    }

    std::string names_directtory[count_directory] = {"res1", "res2", "res3", "res4", "res5"};

    for(int T = 0;T < count_temperatures_on_interval;T++)
    {
        m = m_2 = m_4 = found = m_ = m_group = m_2_group = m_4_group = 0.0;

        for(int d = 0;d < count_directory;d++)
        for(int j = 0;j < count_thread;j++){

            std::ifstream fin("data/" + names_directtory[d] + "/" + std::to_string(system_size) + "_" +
            std::to_string((T*(T2 - T1)/count_temperatures_on_interval + T1)) + "_" + std::to_string(j) + ".dat");

                if(fin.is_open())
                    while(fin>>r){
                        if(found == config_count) break;
                        m += r; m_group += r; fin>>r;
                        m_2 += r; m_2_group += r; fin>>r;
                        m_4 += r; m_4_group += r; fin>>r;
                        found++;
                        if(found % count_config_in_group == 0){
                            m_group /= count_config_in_group;
                            m_2_group /= count_config_in_group;
                            m_4_group /= count_config_in_group;
                            m__group[found / count_config_in_group - 1] = m_group/std::pow(system_size, 2);
                            hi_group[found / count_config_in_group - 1] = (m_2_group - std::pow(m_group, 2))/(T*(T2 - T1)/count_temperatures_on_interval + T1);
                            kum_group[found / count_config_in_group - 1] = 0.5*(3.0 - m_4_group/std::pow(m_2_group, 2));
                            m_group = m_2_group = m_4_group = 0.0;
                        }
                    }
        }
        if(found == 0) throw "it looks like you were wrong range\n";
        if(found > config_count) std::cout<<"Yo-BRO, you Took Too Many ConFiGuRaTioN$,THeRe aRe Not so Many of THeM.Maximum configuration is "<<found<<"\n";

        m /= found;
        m_2 /= found;
        m_4 /= found;
        kum = 0.5*(3.0 - m_4/std::pow(m_2, 2));
        m_ = m/std::pow(system_size, 2);
        hi = (m_2 - std::pow(m, 2))/(T*(T2 - T1)/count_temperatures_on_interval + T1);

        double kum_error = 0.0, hi_error = 0.0, m_error = 0.0;
        for(int i = 0;i < count_group_for_error;i++){
            kum_error += std::pow(kum - kum_group[i], 2);
            kum_group[i] = 0.0;
            hi_error += std::pow(hi - hi_group[i], 2);
            hi_group[i] = 0.0;
            m_error += std::pow(m_ - m__group[i], 2);
            m__group[i] = 0.0;
        }
        kum_error /= count_group_for_error;
        hi_error /= count_group_for_error;
        m_error /= count_group_for_error;
        kum_error = std::sqrt(kum_error);
        hi_error = std::sqrt(hi_error);
        m_error = std::sqrt(m_error);

        fout<<(T*(T2 - T1)/count_temperatures_on_interval + T1)<<"\t"<<kum<<
        "\t"<<kum_error<<"\t"<<m_<<"\t"<<m_error<<"\t"<<hi<<"\t"<<hi_error<<"\n";
    }
}
