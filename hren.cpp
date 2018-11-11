#include <fstream>
#include <cmath>
int main()
{
    std::ifstream fin("m(t)32eq.dat");
    std::ofstream fout("test32eq.dat");
    double x,y;

    while(!fin.eof())
    {
        fin>>x;
        fout<<std::log(x)<<"\t";
        fin>>x;
        fout<<std::log(x)*5<<"\n";
    }
}
