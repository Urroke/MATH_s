#include "math_objects/matrix.h"
#include "math_objects/function_object.h"
#include "math_objects/polynomial.h"
#include "little_math/little_math.h"

int main()
{
        matrix<double,3,3> mat;
        mvector<double,3> res,vec,app;
        double rees;
        std::ifstream fin("file.txt");
        fin>>mat>>vec>>app;
        res = BiCGStab(mat, vec, 0.0001, app);
        std::cout<<mat*res;
}
