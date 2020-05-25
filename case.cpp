#include <iostream>
#include <random>
#include <ctime>
#include <stdio.h>
#include <fstream>
#include "math_objects/m_vector.h"
#include <cstdlib>

int main()
{
    std::mt19937 gen(std::time(nullptr));
    std::uniform_int_distribution<int> dist(0, 9);
    std::uniform_real_distribution<double> real_dist(0.0, 1.0);
    mvector<int, 10> vec;

    std::ifstream fin("info.dat");
    if(fin.is_open())
        fin>>vec;
    fin.close();
    int r;
    while(true)
    {


        std::cout<<"click any simbol or 'e'\n";
        char syb;
        std::cin>>syb;
        if(syb == 'e') break;
        do{
            r = dist(gen);
        }while(double(1)/double(vec[r] + 1) < real_dist(gen));
        std::system("clear");
        std::cout<<r<<"\n";
    }
    vec[r] += 1;
    std::ofstream fout("info.dat");
    fout<<vec;
}
