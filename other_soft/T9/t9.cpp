#include "T9.h"
#include <windows.h>
int main()
{
    setlocale(LC_CTYPE, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    T9& test = T9::instance();
    test.correct_stream();
}
