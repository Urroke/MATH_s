#include "little_math/little_math.h"
#include "math_objects/function_object.h"

int main()
{
    constexpr size_t length_aprox = 100;
	constexpr size_t time = 5000;
    const double eps = 0.00005;
    mvector<double, 2> pol;
    mvector<double, time> m;
    mvector<double, length_aprox> x,y;
    std::ifstream fin("8forfindeq.dat");
    std::ofstream fout("meq(t)8.dat");
    double r, meq;

    for(int i = 0;i < length_aprox;i++)
        x[i] = i;

    for(int i = 0;i < 27;i++){
        std::cout<<i<<"\n";
        for(int j = 0;j < time;j++){
            fin>>m[j];
            fin>>m[j];
        }
		
        for(int j = 0;j < time - length_aprox;j++){
            for(int k = j;k < j + length_aprox;k++)
                y[k - j] = m[k];

            pol = method_of_min_suare<double, length_aprox, 1>(x, y);
            if(std::fabs(pol[0]) < eps){
					meq = 0;
					for(int  k = j;k < time;k++)
						meq += m[k];
					meq /= time - j;
					fout<<j + 1<<"\t"<<(std::exp(meq/5) - 1)/1.71812<<"\n";
                break;
            }
        }
    }
}
