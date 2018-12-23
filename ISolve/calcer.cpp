#include "../support_libs.h"
#include "../math_objects/matrix.h"
#include"../little_math/little_math.h"
double func(double x)
{
	return x/2;
}

int main()
{
	std::ofstream fout("store.dat");
	std::cout<<newton_kotes(func, 0.0, 5.0, 3.0, 100.0);
}