#include <fstream>
#include <cmath>
int main()
{
    std::ifstream fin("m(t)8.dat");
    std::ofstream fout("8forfindeq.dat");
    double x,y;

    while(!fin.eof())
    {
        fin>>x;
        fout<<std::log(x)<<"\t";
        fin>>x;
        fout<<std::log(x*(1.71812) + 1)*5<<"\n";
    }
}
