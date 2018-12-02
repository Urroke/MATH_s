#include <fstream>
#include "math_objects/matrix.h"
#include "little_math/little_math.h"


int main()
{
	double x, x2;
	const int length = 5000;
	std::ifstream fin("e(t)64.dat");
	std::ofstream fout("e(T)_64.dat");
	mvector<double, length> m[27];
	
	for(int i = 0;i < 27;i++)
		for(int j = 0;j < length;j++){
			fin>>x>>x2;
			m[i][j] = x2;
		}
	for(int j = 0;j < length;j++){
		fout<<j + 1<<"\t";
		for(int i = 0;i < 27;i++)
			fout<<m[i][j]<<"\t";
		fout<<"\n";
	}
	return 0;
}