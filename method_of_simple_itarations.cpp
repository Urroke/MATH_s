#include "math_objects/matrix.h"
#include "little_math/little_math.h"
#include <string>
#include <fstream>
#include <typeinfo>
#include <chrono>
#include <ctime>

int main()
{
        matrix<double,3,3> mat;
        mvector<double,3> res,vec,app;
        std::ifstream fin("file1.txt");
        fin>>mat>>vec>>app;
        res = method_of_gauss(mat, vec);
        std::cout<<vec<<mat*res;

    return 0;
}
