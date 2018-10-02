#include "math_objects/selection.h"
#include <vector>
#include <random>
#include <fstream>

int main()
{
    std::mt19937 gen;
    std::mt19937_64 gen_64;
    std::normal_distribution norm;
    std::lognormal_distribution lognorm;
    std::uniform_real_distribution<> real(0,1);
    std::uniform_real_distribution<> real2(-1,1);
    std::poisson_distribution poiss(10);

    std::ofstream fout("res.dat");
    double ex = 0, ass = 0;
    size_t n;
    std::vector<double> a;
    selection<double> b(a);
    std::cin>>n;

    for(int j = 0;j < n;j++){
        system("cls");
        std::cout<<"processing "<<(j*10)/n;
        for(int i = 0;i < 1000000;i++)
            a.push_back(norm(gen));
        ex += b.E();
        ass += b.A();
        a.resize(0);
    }
    fout<<"mt199937 Normal distribution:\n";
    fout<<"ex - "<<ex/n<<"\tas - "<<ass/n<<"\n\n";
    ex = 0, ass = 0;

    for(int j = 0;j < n;j++){
        system("cls");
        std::cout<<"processing "<<(j*10)/n + 10;
        for(int i = 0;i < 1000000;i++)
            a.push_back(lognorm(gen));
        ex += b.E();
        ass += b.A();
        a.resize(0);
    }
    fout<<"mt19937 Lognormal_distribution:\n";
    fout<<"ex - "<<ex/n<<"\tas - "<<ass/n<<"\n\n";
    ex = 0, ass = 0;

     for(int j = 0;j < n;j++){
        system("cls");
        std::cout<<"processing "<<(j*10)/n + 20;
        for(int i = 0;i < 1000000;i++)
            a.push_back(real(gen));
        ex += b.E();
        ass += b.A();
        a.resize(0);
    }
    fout<<"mt19937 real {0, 1} distribution:\n";
    fout<<"ex - "<<ex/n<<"\tas - "<<ass/n<<"\n\n";
    ex = 0, ass = 0;

     for(int j = 0;j < n;j++){
        system("cls");
        std::cout<<"processing "<<(j*10)/n + 30;
        for(int i = 0;i < 1000000;i++)
            a.push_back(real2(gen));
        ex += b.E();
        ass += b.A();
        a.resize(0);
    }
    fout<<"mt19937 real {-1, 1} distribution:\n";
    fout<<"ex - "<<ex/n<<"\tas - "<<ass/n<<"\n\n";
    ex = 0, ass = 0;

     for(int j = 0;j < n;j++){
        system("cls");
        std::cout<<"processing "<<(j*10)/n + 40;
        for(int i = 0;i < 1000000;i++)
            a.push_back(poiss(gen));
        ex += b.E();
        ass += b.A();
        a.resize(0);
    }
    fout<<"mt19937 Poisson distribution:\n";
    fout<<"ex - "<<ex/n<<"\tas - "<<ass/n<<"\n\n";
    ex = 0, ass = 0;

     for(int j = 0;j < n;j++){
        system("cls");
        std::cout<<"processing "<<(j*10)/n + 50;
        for(int i = 0;i < 1000000;i++)
            a.push_back(norm(gen_64));
        ex += b.E();
        ass += b.A();
        a.resize(0);
    }
    fout<<"mt199937_64 Normal distribution:\n";
    fout<<"ex - "<<ex/n<<"\tas - "<<ass/n<<"\n\n";
    ex = 0, ass = 0;

    for(int j = 0;j < n;j++){
        system("cls");
        std::cout<<"processing "<<(j*10)/n + 60;
        for(int i = 0;i < 1000000;i++)
            a.push_back(lognorm(gen_64));
        ex += b.E();
        ass += b.A();
        a.resize(0);
    }
    fout<<"mt19937_64 Lognormal_distribution:\n";
    fout<<"ex - "<<ex/n<<"\tas - "<<ass/n<<"\n\n";
    ex = 0, ass = 0;

     for(int j = 0;j < n;j++){
        system("cls");
        std::cout<<"processing "<<(j*10)/n + 70;
        for(int i = 0;i < 1000000;i++)
            a.push_back(real(gen_64));
        ex += b.E();
        ass += b.A();
        a.resize(0);
    }
    fout<<"mt19937_64 real {0, 1} distribution:\n";
    fout<<"ex - "<<ex/n<<"\tas - "<<ass/n<<"\n\n";
    ex = 0, ass = 0;

     for(int j = 0;j < n;j++){
        system("cls");
        std::cout<<"processing "<<(j*10)/n + 80;
        for(int i = 0;i < 1000000;i++)
            a.push_back(real2(gen_64));
        ex += b.E();
        ass += b.A();
        a.resize(0);
    }
    fout<<"mt19937_64 real {-1, 1} distribution:\n";
    fout<<"ex - "<<ex/n<<"\tas - "<<ass/n<<"\n\n";
    ex = 0, ass = 0;

     for(int j = 0;j < n;j++){
        system("cls");
        std::cout<<"processing "<<(j*10)/n + 90;
        for(int i = 0;i < 1000000;i++)
            a.push_back(poiss(gen_64));
        ex += b.E();
        ass += b.A();
        a.resize(0);
    }
    fout<<"mt19937_64 Poisson distribution:\n";
    fout<<"ex - "<<ex/n<<"\tas - "<<ass/n<<"\n\n";

    return 0;
}
