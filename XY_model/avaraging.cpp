#include "../little_math/little_math.h"
#include "../math_objects/m_vector.h"

int main()
{
    constexpr size_t N = 3;
    constexpr size_t temps = 1;
    constexpr size_t size = 200;
    constexpr size_t config = 33;
    constexpr size_t L = 48;
    constexpr double T1 = 2.0;
    constexpr double T2 = 2.0;
    mvector<double, 2000> m, mres;

        std::ifstream fin("blabla.dat");
        for(int i = 0;i < 50;i++){
            fin>>m;
            mres+=m;
            }
        mres/= 50;
         std::ofstream fout("blablabla.dat");
         fout<<mres;

}
