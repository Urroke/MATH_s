#ifndef T9_H_INCLUDED
#define T9_H_INCLUDED
#include "../support_libs.h"
class T9
{
private:
    T9(){;}
    ~T9(){;}
    T9(const T9&) = delete;
    T9& operator=(const T9&) = delete;

    std::vector<std::string> library;

    double get_weight(char one,char two)
    {

    }

    void learning(std::string word,std::string to)
    {
        double weight;
        int quant;
        char syb;
        int point;
        std::ifstream in;
        std::ofstream out;
        std::vector<double> weights;
        std::vector<char> sybs;

        for(int i = 0;i < word.length();i++){
            std::string temp(1,to[i]);
            in.open("weights\\" + temp + ".txt");

            in>>quant;

            for(int j = 0;j < 32;j++){
                in>>syb;
                in>>weight;
                weights.push_back(weight);
                sybs.push_back(syb);
            }
            in.close();
            out.open("weights\\" + temp + ".txt",std::ios_base::trunc);
            out<<quant + 1<<"\n";

            for(int j = 0;j < 32;j++){
                out<<sybs[j]<<"\t";
                if(sybs[j] == word[i]) out<<(weights[j]*quant + 1)/(quant + 1);
                else  out<<(weights[j]*quant)/(quant + 1);
                out<<"\n";
            }
            out.close();
            weights.resize(0);
            sybs.resize(0);
        }
    }

    std::vector<std::string> correct(std::string exemp)
    {
        std::ifstream in;

        std::string temp;
        std::vector<std::string> result;

        double weight;
        double max_weight = 0;
        in.open("library\\" + std::to_string(exemp.length()) + ".txt");

        while(in >> temp){
            weight = 0;
            for(int i = 0;i < exemp.length();i++)
                if(exemp[i] == temp[i])
                    weight += 1;
            if(weight > max_weight){
                max_weight = weight;
            }
            in.clear();

            while(in >> temp){
                weight = 0;
                for(int i = 0;i < exemp.length();i++)
                    if(exemp[i] == temp[i])
                        weight += 1;
                if(weight > double(exemp.length())*0.75)
                    result.push_back(temp);
            }
        }
        return result;
    }
public:
    static T9& instance()
    {
        static T9 s;
        return s;
    }

    std::string correct_stream()
    {
        int syb = 0;
        size_t ans;
        std::string cash = "";
        std::string temp;
        std::vector<std::string> options;

        while(char(syb) != '\r')
        {
            syb = getch();
            temp += char(syb);

            if(char(syb) == '\b'){
                if(!cash.empty()){
                    cash.erase(cash.end() - 1);
                }
            }else cash += char(syb);
            system("cls");
            std::cout<<cash;

            if(char(syb) == ' '){
                temp = "";
                size_t index = cash.length() - 2;

                while((cash[index] != ' ')&&(index > 0))
                    index --;

                if(index > 0) index++;

                for(int i = index ;i < cash.length() - 1;i++)
                    temp += cash[i];

                options = correct(temp);
                std::cout<<"\n";
                for(int i = 0;i < options.size();i++)
                    std::cout<<options[i]<<"\t";

                std::cin>>ans;
                if(options.size() > 0){
                    learning(temp,options[ans]);
                    temp = options[ans];
                }

                cash.erase(index,cash.length());

                cash += temp + " ";
                system("cls");
                std::cout<<cash;
            }
        }
    }
};


#endif // T9_H_INCLUDED
