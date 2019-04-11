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
    constexpr size_t L = 512;
    size_t found = 0;
    constexpr double T1 = 2.26;
    constexpr double T2 = 2.28;
    double m_4, m_2, m, r;
    std::ofstream fout("1Aresults_" + std::to_string(L) + ".dat");
    fout<<"T\tKUM\tM\tHI\n";
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
                found ++;
            }
        }

        std::cout<<T<<"\n";
        m /= found;
        m_2 /= found;
        m_4 /= found;
        fout<<(T*(T2 - T1)/temps + T1)<<"\t"<<0.5*(3 - m_4/std::pow(m_2, 2))
        <<"\t"<<m/(L*L)<<"\t"<<(m_2 -
        std::pow(m, 2))/(T*(T2 - T1)/temps + T1)<<"\n";
    }
}
