#include "math_objects/matrix.h"
#include "little_math/little_math.h"
#include <string>
#include <fstream>
#include <typeinfo>
#include <chrono>
#include <ctime>

int main()
{
    try{
        matrix<double,3,3> mat;
        mvector<double,3> res,vec,app;
        std::ifstream fin("file.txt");
        fin>>mat>>vec>>app;
        res = IM(mat, vec, 0.001, app, "");
        std::cout<<vec<<mat*res;
    }
    catch(int err){
        if(err == 1)
            std::cout<<"The sum of diagonal elements is greater than the sum of the remaining";
        if(err == 2)
            std::cout<<"Zero on main diagonal";
    }
    return 0;
}
