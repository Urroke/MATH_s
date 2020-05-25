#include "../little_math/little_math.h"
#include "../math_objects/m_vector.h"

int main()
{
    constexpr int count_size = 4;
    constexpr int t_w[count_size] = {20, 40 , 80, 160};
    constexpr double mu = 1.0;


    for(int i = 0;i < count_size;i++){
            std::ofstream fout(std::to_string(t_w[i]) + "_" + std::to_string(mu) + "+scale_ch.dat");
            std::ifstream fin("cor_res" + std::to_string(t_w[i]) + ".dat");
        for(int j = 0;j < 10000;j++){
            double r;
            fin>>r;
            fin>>r;
            fout<<double(j + 1)/std::pow(t_w[i], mu)<<"\t"<<r*std::pow(t_w[i], 0.25599 * 2.0)<<"\n";
        }
    }

}
