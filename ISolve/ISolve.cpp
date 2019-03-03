#include <iostream>
#include <string>
#include <fstream>
#include "file_maker.h"

int main()
{
    std::ofstream calcer("calcer.cpp");
    std::string comand;
    std::getline(cin, comand);
    calcer<<file_maker(parser(comand));
}
