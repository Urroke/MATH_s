#include "math_objects/matrix.h"
#include "math_objects/function_object.h"
#include "little_math/little_math.h"
#include <fstream>



int main()
{
    constexpr int L;
    constexpr int N;
    constexpr int polynom_degree;

    mvector<double, L> data[N];

    std::ifstream fin("data.dat");
    std::ofstream fout("value.dat");



    polynom<double, degree> func1(method_of_min_suare<double, length, degree>(x, y));
    polynom<double, degree2> func2(method_of_min_suare<double, length, degree2>(x, y));

    for(int i = 0;i < length;i++){
        err1 += std::pow(func1(x[i]) - y[i], 2);
        err2 += std::pow(func2(x[i]) - y[i], 2);
    }

    std::cout<<err1<<"\t"<<err2;
}
