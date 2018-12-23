#include <fstream>

int main()
{
	double m;
	const int length = 3000;
	std::ifstream fin("e(T)_64.dat");
	std::ofstream fout("c(T)64.dat");
    double x[27], x2[27];
    for(int i = 0;i < 27;i++){
        x[i] = 0.0;
        x2[i] = 0.0;
    }
	double temp[27] = {
        0.5, 0.7, 0.9, 1.1, 1.3, 1.5, 1.7, 1.9, 2.1,
        2.15, 2.2, 2.25, 2.3, 2.35, 2.4, 2.45, 2.5,
        2.55, 2.6, 2.65, 2.7, 2.75, 2.8, 3, 3.2, 3.4, 3.6};
    for(int j = 0;j < length;j++){
        fin>>m;
		for(int i = 0;i < 27;i++){
			fin>>m;
			x[i] += m;	x2[i] += m*m;
		}
	}
    for(int i = 0;i < 27;i++){
        x[i] /= length;
		x2[i] /= length;
		fout<<temp[i]<<"\t"<<(x2[i] - x[i]*x[i])/(temp[i]*temp[i])<<"\n";
    }
	return 0;
}
