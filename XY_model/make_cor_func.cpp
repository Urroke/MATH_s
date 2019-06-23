#include "../little_math/little_math.h"
#include "../math_objects/m_vector.h"

int main()
{
    constexpr int N = 4;
    constexpr int t_w_count = 4;
    constexpr int obser_t = 10000;
    constexpr int t_w[t_w_count] = {20, 40, 80, 160};
    int found = 0;
    double left[obser_t], right[obser_t];

    for(int j = 0;j < obser_t;j++)
    {
        left[j] = 0;
        right[j] = 0;
    }
    for(int t = 0;t < t_w_count;t++){
        for(int i = 0;i < N;i ++)
        {
            double r;
            std::ifstream fin1("cor/l" + std::to_string(t_w[t]) + "_" + std::to_string(i) + ".dat");
            std::ifstream fin2("cor/r"+ std::to_string(t_w[t]) + "_" + std::to_string(i) + ".dat");
            if(fin1.is_open())
            while(!fin1.eof()){
                for(int j = 0;j < obser_t;j++){
                    fin1>>r;
                    left[j] += r;
                }
                found ++;
            }

            if(fin2.is_open())
            while(!fin2.eof())
                for(int j = 0;j < obser_t;j++){
                    fin2>>r;
                    right[j] += r;
                }

        }

        std::ofstream fout("cor_res" + std::to_string(t_w[t]) + ".dat");
        std::cout<<t<<"\n";
        for(int j = t_w[t];j < obser_t;j++)
        {
            left[j] /= found;
            right[j] /= found;
            fout<<j - t_w[t] + 1<<"\t"<<left[j] - right[j]<<"\n";
        }
    }
}
