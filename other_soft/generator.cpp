#include <fstream>
#include <random>
#include <iostream>
using namespace std;

int main()
{
    random_device rd;
    mt19937_64 gen(rd());
    uniform_real_distribution<> dist(-100,100);
    ofstream out1("file1.txt",ios_base::trunc);
    ofstream out2("file2.txt",ios_base::trunc);
    int a;
    cin>>a;
    for(int i = 0;i < a;i++){
        for(int i = 0;i < a;i++){
            out1<<dist(gen)<<"   ";
            out2<<dist(gen)<<"   ";
        }
        out1<<endl;
        out2<<endl;
    }
    return 0;
}
