#include <fstream>

int main()
{
	double x, x2, m;
	const int length = 5000;
	std::ifstream fin("e(t)16.dat");
	std::ofstream fout("c(T)16.dat");
	
	double temp[27] = {
        0.5, 0.7, 0.9, 1.1, 1.3, 1.5, 1.7, 1.9, 2.1,
        2.15, 2.2, 2.25, 2.3, 2.35, 2.4, 2.45, 2.5,
        2.55, 2.6, 2.65, 2.7, 2.75, 2.8, 3, 3.2, 3.4, 3.6};
	
	for(int i = 0;i < 27;i++){
		x = 0;
		x2 = 0;
		for(int j = 0;j < length;j++){
			fin>>m>>m;
			x += m;	x2 += m*m;
		}
		x /= length;
		x2 /= length;
		fout<<temp[i]<<"\t"<<(x2 - x*x)/(temp[i]*temp[i])<<"\n";
	}
	return 0;
}