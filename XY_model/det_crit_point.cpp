#include "../little_math/little_math.h"
#include "../math_objects/m_vector.h"

int main()
{
    constexpr size_t N = 4;
    constexpr size_t temps = 31;
    constexpr size_t size = 200;

    mvector<double, size> m, ex;
    double m_4, m_2;
    std::ofstream fout("kum_32.dat");
    for(int i = 0;i < temps;i++)
    {
        m *= 0;
        for(int j = 0;j < N;j++){
            std::ifstream fin("32n/gaiz_" + std::to_string(i) + std::to_string(j) + ".dat");
            fin>>ex; m += ex;
            std::cout<<m;
        }
        m /= N;
        //fout<<0.5*(3 - summ_power(m, 4)/std::pow(summ_power(m, 2), 2))<<"\n";
        fout<<summ_power(m, 1)<<"\n";
    }
}
