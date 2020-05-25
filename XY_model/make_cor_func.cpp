#include "../little_math/little_math.h"
#include "../math_objects/m_vector.h"

int main()
{
    constexpr int N = 3;
    constexpr int t_w_count = 4;
    constexpr int conf = 2;
    constexpr int obser_t = 10000;
    constexpr int t_w[t_w_count] = {20, 40, 80, 160};
    double density = 0.6;
    int found = 0;
    std::string dir[] = {"", "all_results/chi0.600000/"};
    //dir[0] = "auto_cor_low_temp" + std::to_string(density) + "/";
    mvector<double, obser_t> left, right, buf;

    for(int j = 0;j < obser_t;j++)
    {
        left[j] = 0;
        right[j] = 0;
    }
    int iter1 = 0, iter2 = 0;
    for(int t = 0;t < t_w_count;t++){
        found = 0;
        left*=0;
        right*=0;
        for(int d = 0;d < 2;d++)
        for(int i = 0;i < N;i ++)
        {
            double r;
            std::ifstream fin1(dir[d] + "l" + std::to_string(t_w[t]) + "_" + std::to_string(i) + ".dat");
            std::ifstream fin2(dir[d] + "/r"+ std::to_string(t_w[t]) + "_" + std::to_string(i) + ".dat");
            if(fin1.is_open())
            for(int c = 0;c < conf;c++){
                if(fin1.eof()) break;
                fin1>>buf;
                left += buf;
                found ++;

            }
            if(fin2.is_open())
            for(int c = 0;c < conf;c++){
                if(fin2.eof()) break;
                fin2>>buf;
                right += buf;;
            }

        }

        std::ofstream fout("cor_res" + std::to_string(t_w[t]) + ".dat");
        std::ofstream foutm("cor_mm_res" + std::to_string(t_w[t]) + ".dat");
        std::ofstream foutc("cor_ss_res" + std::to_string(t_w[t]) + ".dat");
        //std::cout<<t<<"\n";
        std::cout<<found<<"\n";
        for(int j = t_w[t];j < obser_t;j++)
        {
            if(j == t_w[t]) std::cout<<left[j]/found<<"\n";
            left[j] /= found;
            right[j] /= found;
            fout<<j - t_w[t] + 1<<"\t"<<left[j] - right[j]<<"\n";
            foutm<<j - t_w[t] + 1<<"\t"<<right[j]<<"\n";
            foutc<<j - t_w[t] + 1<<"\t"<<left[j]<<"\n";
        }
    }
}
