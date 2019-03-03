#include<fstream>

int main()
{
    double num;
    std::ifstream fin("06/data_0.dat");
    std::ofstream fout("data.dat",std::ios_base::trunc);

    for(int i = 0;i < 1000;i++){
        fin>>num;
        fin>>num;
        fout<<num;
    }
}
