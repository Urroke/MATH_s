#include <iostream>
#include <string>
#include <fstream>
#include "file_maker.h"

int main()
{
    materials test;
    std::ofstream calcer("calcer.cpp");
    std::string comand, a;
    //std::getline(std::cin, comand);
    comand = "-int; -=x/2:s x:s; -nc; -0.0; -5.0; -3.0; -100.0;";
    try{
        calcer<<file_maker(parser(comand));
    }catch(const char* error){
        std::cout<<error;
    }
    catch(std::string error){
        std::cout<<error;
    }
    //system("g++ calcer.cpp -o make -std=c++17");
    return 0;
}
