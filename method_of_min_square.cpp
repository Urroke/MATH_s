#include "math_objects/matrix.h"
#include "math_objects/function_object.h"
#include "little_math/little_math.h"
#include <fstream>

int main()
{
    constexpr size_t degree = 1;
    constexpr size_t degree2 = 7;
    constexpr size_t length = 8;

    mvector<double, length> x, y;
    double err1 = 0, err2 = 0;

    std::ifstream fin("data.txt");
    std::ofstream fout("polynom1.txt");

    fin>>x>>y;

    polynom<double, degree> func1(method_of_min_suare<double, length, degree>(x, y));
    polynom<double, degree2> func2(method_of_min_suare<double, length, degree2>(x, y));

    for(int i = 0;i < length;i++){
        err1 += std::pow(func1(x[i]) - y[i], 2);
        err2 += std::pow(func2(x[i]) - y[i], 2);
    }

    std::cout<<err1<<"\t"<<err2;
}
