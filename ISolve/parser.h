#include <string>
#include <vector>
#include <map>
#include <regex>

std::map<std::string, int> comands = {{"calc", 2}, {"int", 3}};

struct materials{
    std::string comand;
    int qunt_keys;
    std::vector<std::string> keys;
};

materials parser(std::string exemp){
    materials res;
    int key = -1;
    std::string comand;
    std::vector<std::string> keys;
    int pos;
    for(int i = 0;i < exemp.length();i++)
        if(exemp[i] == '-'){
            pos = i;
            key++;
            i++;
            keys.push_back("");
            while(exemp[i] != ';'){
                if(i == exemp.length())throw "expected symbol \";\"";
                if(key == 0)
                    comand += exemp[i];
                else
                    keys[key - 1] += exemp[i];
                i++;
            }
            if(key == 0&&comands.find(comand) == comands.end()) throw "Ty mne tut chto to gonish, takoy komandy net";
        }
    keys.resize(keys.size() - 1);
    if(comand == "")throw "ey, druzhok pirozhok, ty zabyl napisat' komandu";
    if(keys.size() < comands[comand]) throw "ey bratok, ty argumentov ne dosypal";
    res.comand = comand;
    res.keys = keys;
    res.qunt_keys = keys.size();
    return res;
}
