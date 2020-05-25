#include "../little_math/little_math.h"
#include "../math_objects/m_vector.h"

int main()
{
    constexpr size_t N = 4;
    constexpr size_t temps = 20;
    constexpr size_t size = 100;
    constexpr size_t config = 100;
    constexpr size_t L = 256;
    constexpr double T1 = 1.5;
    constexpr double T2 = 2.5;

    double m, m_2, e, e_2;

    for(int T = 0;T <= temps;T++)
    {
        std::ofstream fout(std::to_string(L) + ".dat");
        m *= 0;
        m_2 = 0;
        e = 0;
        e_2 = 0;
        double r;
        for(int j = 0;j < N;j++){
            std::ifstream fin("fresh/" + std::to_string(L) + "_" + std::to_string(T1 + T*(T2 - T1)/temps) + "_" + std::to_string(j) + ".dat");
            for(int i = 0;i < 25;++i)
            {
                fin>>r; m += r;
                fin>>r; m_2 += r;
                fin>>r; e += r;
                fin>>r; e_2 += r;
            }
        }
        m /= (N*25*L*L);
        fout<<"T\tM\n1\t1\n";
        for(int i = 0;i < size;i++)
            fout<<i + 2<<"\t"<<m[i]<<"\n";
    }
}
