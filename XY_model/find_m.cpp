#include "../little_math/little_math.h"
#include "../math_objects/m_vector.h"
#include <random>

mt19937 gen(0);

std::uniform_real_distribution<double> dist(-1.0, 1.0);

mvector<double, 3> random_normal()
{
    mvector<double, 3> res;
    do{
        res = {dist(gen), dist(gen), dist(gen)};
    }while(res.magnitude() > 1.0);
    return res.normalized();
}

int main()
{
    constexpr int N = 4;
    constexpr int conf = 300;
    constexpr int obser_t = 3000;
    constexpr double m = 1.0;
    int found = 0;
    std::string dir[] = {"all_results/m_from_low_temp_in_0.600000/", ""};
    mvector<double, obser_t> res_val, buf, res_err;
    std::vector<mvector<double, obser_t>> res;

    int iter1 = 0;

        found = 0;
        for(int d = 0;d < 2;d++)
        for(int i = 0;i < N;i ++)
        {
            double r;
            std::ifstream fin1(dir[d] + std::to_string(m) + "_" + std::to_string(i) + ".dat");
            if(fin1.is_open())
            for(int c = 0;c < conf;c++){
                if(fin1.eof()) break;
                fin1>>buf;
                res.push_back(buf);
                res_val += buf;
                found ++;

            }
        }
        res_val /= found;
        for(int j=0;j < obser_t;j++)
        {
             for(int i = 0;i < res.size();i++)
                res_err[j] += std::pow(res[i][j] - res_val[j], 2);
            res_err[j] /= res.size();
            res_err[j] = std::sqrt(res_err[j]);
        }
        std::ofstream fout("m_res_" + std::to_string(m) + ".dat");

        for(int i = 0;i < obser_t;i++)
            fout<<i + 1<<"\t"<<res_val[i]<<"\t"<<res_err[i]<<"\n";

        std::ofstream fout2("test.dat");

        for(int i = 0;i < 100000;i++)
            fout2<<random_normal();

}
