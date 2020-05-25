#include "../little_math/little_math.h"
#include "../math_objects/m_vector.h"

int main()
{
    constexpr size_t count_thread = 4;
    constexpr size_t count_temperatures_on_interval = 20;
    constexpr size_t system_size = 8;
    constexpr double T1 = 1.5;
    constexpr double T2 = 3.5;
    constexpr int config_count  = 25;
    constexpr int count_group_for_error = 5;
    constexpr int count_directory = 5;
    constexpr int count_config_in_group = config_count/count_group_for_error;
    size_t found = 0;
    double e_2, m_2, m, e, r, m_, e_, hi, c, m_group , m_2_group, e_group, e_2_group;

    std::ofstream fout("results_for_L=" + std::to_string(system_size) + ".dat");
    fout<<"T\tC\tC_ERROR\tM\tM_ERROR\tHI\tHI_ERROR\tE\tE_ERROR\n";

    std::array<double, count_config_in_group> m__group, e__group, hi_group, c_group;
    for(int i = 0;i < count_group_for_error;i++){
        m__group[i] = 0;
        hi_group[i] = 0;
        c_group[i] = 0;
    }

    std::string names_directtory[count_directory] = {"", "", "", "", ""};

    for(int T = 0;T < count_temperatures_on_interval;T++)
    {
        m = m_2 = e_2 = e = found = m_ = e_ = m_group = m_2_group = e_2_group = e_group = 0.0;
        for(int j = 0;j < count_thread;j++){


            std::string name = ("fresh/" + std::to_string(system_size) + "_" +
            std::to_string((T*(T2 - T1)/count_temperatures_on_interval + T1)) + "_" + std::to_string(j) + ".dat");
            std::ifstream fin(name);
            std::cout<<name<<"\n";
                for(int i = 0;i < 25;i++){
                        if(found == config_count) break;

                        fin>>r; m += r; m_group += r;
                        std::cout<<r<<"\n";
                        fin>>r; m_2 += r; m_2_group += r;
                        fin>>r; e+= r; e_group += r;
                        fin>>r; e_2 += r; e_2_group += r;
                        found++;
                        if(found % count_config_in_group == 0){
                            m_group /= count_config_in_group;
                            m_2_group /= count_config_in_group;
                            e_group /= count_config_in_group;
                            e_2_group /= count_config_in_group;
                            m__group[found / count_config_in_group - 1] = m_group;
                            e__group[found / count_config_in_group - 1] = e_group;
                            hi_group[found / count_config_in_group - 1] = (m_2_group - std::pow(m_group, 2))/(T*(T2 - T1)/count_temperatures_on_interval + T1);
                            c_group[found / count_config_in_group - 1] = (e_2_group - std::pow(e_group, 2))/std::pow(T*(T2 - T1)/count_temperatures_on_interval + T1, 2);
                            m_group = m_2_group = e_group = e_2_group = 0.0;
                        }
                    }
        }
        if(found == 0) throw "it looks like you were wrong range\n";
        if(found > config_count) std::cout<<"Yo-BRO, you Took Too Many ConFiGuRaTioN$,THeRe aRe Not so Many of THeM.Maximum configuration is "<<found<<"\n";

        std::cout<<m<<"\n";
        m /= found;
        m_2 /= found;
        e /= found;
        e_2 /= found;
        e_ = e;
        m_ = m;
        hi = (m_2 - std::pow(m, 2))/(T*(T2 - T1)/count_temperatures_on_interval + T1);
        c = (e_2 - std::pow(e, 2))/pow(T*(T2 - T1)/count_temperatures_on_interval + T1, 2);

        double c_error = 0.0, hi_error = 0.0, m_error = 0.0, e_error = 0;
        for(int i = 0;i < count_group_for_error;i++){
            c_error += std::pow(c - c_group[i], 2);
            c_group[i] = 0.0;
            hi_error += std::pow(hi - hi_group[i], 2);
            hi_group[i] = 0.0;
            m_error += std::pow(m_ - m__group[i], 2);
            m__group[i] = 0.0;
            e_error += std::pow(e_ - e__group[i], 2);
            e__group[i] = 0.0;
        }
        c_error /= count_group_for_error;
        hi_error /= count_group_for_error;
        m_error /= count_group_for_error;
        e_error /= count_group_for_error;
        c_error = std::sqrt(c_error);
        hi_error = std::sqrt(hi_error);
        m_error = std::sqrt(m_error);
        e_error = std::sqrt(e_error);

        fout<<(T*(T2 - T1)/count_temperatures_on_interval + T1)<<"\t"<<c<<
        "\t"<<c_error<<"\t"<<m_/std::pow(system_size, 2)<<"\t"<<m_error<<"\t"<<hi<<"\t"<<hi_error<<"\t"<<e_/std::pow(system_size, 2)<<"\t"<<e_error<<"\n";
    }
}
