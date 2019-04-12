#include "../little_math/little_math.h"
#include "../math_objects/m_vector.h"
#include <dirent.h>

int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

int main()
{
    constexpr size_t N = 5;
    constexpr size_t temps = 50;
    constexpr size_t size = 2000;
    constexpr size_t config = 100;
    constexpr size_t L = 128;
    size_t found = 0;
    constexpr double T1 = 2.26;
    constexpr double T2 = 2.28;
    double m_4, m_2, m, r;
    std::ofstream fout("1Aresults_" + std::to_string(L) + ".dat");
    fout<<"T\tKUM\tERR_KUM\tM\tERR_M\tHI\tERR_HI\n";
    std::string dir = "newres/";
    std::vector<std::string> files = std::vector<std::string>();

    getdir(dir,files);

    for(int T = 0;T < temps;T++) ///KEK
    {
        m *= 0;
        m_2 *= 0;
        m_4 *= 0;
        found = 0;
        for (unsigned int i = 0;i < files.size();i++)
        if(files[i].size() > 7)
        if(std::atoi(files[i].substr(27, 3).c_str()) == L)
        if(std::atoi(files[i].substr(31, 2).c_str()) == T){
            std::ifstream fin(dir + files[i]);
            for(int k = 0;k < size;k++){
                fin>>r;
                m_4 += r*r*r*r;
                m_2 += r*r;
                m += r;
            }
            found ++;
            fin.close();
        }

        std::cout<<T<<"\n";
        m /= found*size;
        m_2 /= found*size;
        m_4 /= found*size;

        double kum_g = 0.5*(3 - m_4/std::pow(m_2, 2));
        double hi_g = (m_2 - std::pow(m, 2))/(T*(T2 - T1)/temps + T1);
        double m_g = m/(L*L);
        double err_kum = 0;
        double err_hi = 0;
        double err_m = 0;

        m *= 0;
        m_2 *= 0;
        m_4 *= 0;

        for (unsigned int i = 0;i < files.size();i++)
        if(files[i].size() > 7)
        if(std::atoi(files[i].substr(27, 3).c_str()) == L)
        if(std::atoi(files[i].substr(31, 2).c_str()) == T){
            std::ifstream fin(dir + files[i]);
            for(int k = 0;k < size;k++){
                fin>>r;
                m_4 += r*r*r*r;
                m_2 += r*r;
                m += r;
            }
            m /= size;
            m_2 /= size;
            m_4 /= size;

            double kum = 0.5*(3 - m_4/std::pow(m_2, 2));
            double hi = (m_2 - std::pow(m, 2))/(T*(T2 - T1)/temps + T1);
            double m_ = m/(L*L);

            err_kum += std::pow(kum - kum_g, 2);
            err_m += std::pow(m_ - m_g, 2);
            err_hi += std::pow(hi - hi_g, 2);

            fin.close();
        }

        err_kum /= found;
        err_m /= found;
        err_hi /= found;

        err_kum = std::pow(err_kum, 0.5);
        err_m = std::pow(err_m, 0.5);
        err_hi = std::pow(err_hi, 0.5);

        fout<<(T*(T2 - T1)/temps + T1)<<"\t"<<kum_g<<"\t"<<err_kum<<"\t"<<m_g<<"\t"<<err_m<<"\t"<<hi_g<<"\t"<<err_hi<<"\n";
    }
}
