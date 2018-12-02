#include <fstream>

int main()
{
	std::ifstream fin("m(t)64.dat");
	std::ofstream fout("m(t)_64.dat");
	double x, y;
	for(int i = 0;i < 54;i++)
		for(int j = 0;j < 5000;j++)
		{
			fin>>x>>y;
			if(i > 4)
				fout<<x<<"\t"<<y<<"\n";
		}
	return 0;
}