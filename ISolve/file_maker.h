#include "parser.h"
std::string type_maker(std::string exemp)
{
    std::string args;
    for(int i = 0;i < exemp.size();i++){
        if(exemp[i] == 'm'){
            i++;
            while(exemp[i] == ' '&&i < exemp.size()) i++;
            args += "matrix<double, ";
            while(exemp[i] != ' '&&i < exemp.size()){
                args += exemp[i];
                i++;
            }
            args += ",";
            while(exemp[i] == ' '&&i < exemp.size()) i++;
            while(exemp[i] != ' '&&i < exemp.size()){
                args += exemp[i];
                i++;
            }
            while(exemp[i] == ' '&&i < exemp.size()) i++;
            args += "> ";
            exemp.erase(0, i);
            args += exemp;
            break;
        }
        if(exemp[i] == 'v'){
            i++;
            while(exemp[i] == ' '&&i < exemp.size()) i++;
            args += "mvector<double, ";
            while(exemp[i] != ' '&&i < exemp.size()){
                args += exemp[i];
                i++;
            }
            args += "> ";
            exemp.erase(0, i);
            args += exemp;
            break;
        }
        if(exemp[i] == 's'){
            i++;
            while(exemp[i] == ' '&&i < exemp.size()) i++;
            args += "double ";
            exemp.erase(0, i);
            args += exemp;
            break;
        }
    }
    if(args == "") throw "incorrect type";
    return args;
}

std::string values_maker(std::string exemp, int name)
{
    std::string res;
    exemp.erase(std::remove(exemp.begin(),exemp.end(),' '),exemp.end());
    std::ifstream fin(exemp);
    if(!fin.is_open()) throw "can't open " + exemp;
    fin.close();
    res += "arg" + std::to_string(name) + ";\n\t";
    res += "std::ifstream fin" + std::to_string(name) + "(\"" + exemp + "\");\n\t";
    res += "fin" + std::to_string(name) + ">>arg" + std::to_string(name) + ";\n\n";
    return res;
}

std::string argument_maker(std::string exemp, int name)
{
    std::string args;
    for(int i = 0;i < exemp.size();i++){
        if(exemp[i] == 'm'){
            i++;
            while(exemp[i] == ' '&&i < exemp.size()) i++;
            args += "matrix<double, ";
            while(exemp[i] != ' '&&i < exemp.size()){
                args += exemp[i];
                i++;
            }
            args += ",";
            while(exemp[i] == ' '&&i < exemp.size()) i++;
            while(exemp[i] != ' '&&i < exemp.size()){
                args += exemp[i];
                i++;
            }
            while(exemp[i] == ' '&&i < exemp.size()) i++;
            args += "> ";
            exemp.erase(0, i);
            args += values_maker(exemp, name);
            break;
        }
        if(exemp[i] == 'v'){
            i++;
            while(exemp[i] == ' '&&i < exemp.size()) i++;
            args += "mvector<double, ";
            while(exemp[i] != ' '&&i < exemp.size()){
                args += exemp[i];
                i++;
            }
            args += "> ";
            exemp.erase(0, i);
            args += values_maker(exemp, name);
            break;
        }
        if(exemp[i] == 's'){
            i++;
            while(exemp[i] == ' '&&i < exemp.size()) i++;
            args += "\tdouble ";
            exemp.erase(0, i);
            exemp.erase(std::remove(exemp.begin(),exemp.end(),' '),exemp.end());
            bool is_number = true;
            for(int j = 0;j < exemp.size();j++)
            if(exemp[j] < '1'&&exemp[i] > '9')
                is_number = false;
            if(is_number)
                args += "arg" + std::to_string(name) + " = " +exemp + ";\n\n";
            else{
                args += values_maker(exemp, name);
            }
            break;
        }
    }
    if(args == ""){
        std::string str = "undefined type - ";
        str += exemp[0];
        throw str;
    }
    return args;
}
std::string arguments_maker(std::string exemp, int &quant_args)
{
    std::string res;
    std::string arg;
    int names = 0;
    for(int i = 0;i < exemp.size();i++){
        if(exemp[i] != ' '&&i < exemp.size()){
            arg = "";names++;
            while(exemp[i] != ':'&&exemp[i] != ','&&i < exemp.size()){
                arg += exemp[i];
                i++;
            }i++;
            res += argument_maker(arg, names);
        }
    }
    quant_args = names;
    return res;
}
void func_make(std::string exemp, std::string &argumets, std::string &functional, std::string &out, int &qunt_args)
{
    std::string func;
    std::string file_name;
    std::string type;
    std::string args;
    int qunt_args_ = 0;
    int i;
    if(exemp[0] == '=')
    for(i = 1;i < exemp.size();i++){
        if(exemp[i] == ':') break;
        else func += exemp[i];
    }

    if(exemp[0] == '<'){
        for(i = 1;i < exemp.size();i++)
            if(exemp[i] == ':') break;
            else file_name += exemp[i];
        std::ifstream fin(file_name);
        if(!fin.is_open()) throw "ne mogu otkrit file";
        fin>>func;
    }

    if(func == "") throw "function not found";

    for(i = i + 1;i < exemp.size();i++){
        if(exemp[i] == ':') break;
        if(exemp[i] != ' '){
            type = ""; qunt_args_++;
            while(exemp[i] != ':'&&exemp[i] != ','&&i < exemp.size()){
                type += exemp[i];
                i++;
            }i++;
            args += type_maker(type) + ", ";
        }
    }
    args.erase(args.size() - 2, 2);
    while(exemp[i] == ' ') i++;

    exemp.erase(0,i - 1);
    qunt_args = qunt_args_;
    out = type_maker(exemp);
    functional = func;
    argumets = args;
}

std::string file_maker(materials exemp)
{
    std::string file;
    std::string func;
    std::string args;
    std::string type;
    int quant_args;
    int true_qunt_args;
    file += "#include \"../support_libs.h\"\n#include \"../math_objects/matrix.h\"\n#include\"../little_math/little_math.h\"\n";
    if(exemp.comand == "calc"){
        func_make(exemp.keys[0], args, func, type, true_qunt_args);
        file += type + "func(" + args + ")\n{\n\treturn " + func + ";\n}\n\n";
        file += "int main()\n{\n\t";
        file += "std::ofstream fout(\"store.dat\");\n\t";
        file += arguments_maker(exemp.keys[1], quant_args);
        file += "\tfout<<func(";
        if(quant_args < true_qunt_args) throw "few arguments";
        for(int i = 0;i < quant_args;i++)
            file += "arg" + std::to_string(i + 1) + ", ";
        file.erase(file.size() - 2, 2);
        file += ");\nreturn 0;}";
    }
    if(exemp.comand == "int"){
        func_make(exemp.keys[0], args, func, type, true_qunt_args);
        if(true_qunt_args > 1) throw "sorry while integrating the single variable function";
        file += type + "func(" + args + ")\n{\n\treturn " + func + ";\n}\n\n";
        file += "int main()\n{\n\t";
        file += "std::ofstream fout(\"store.dat\");\n\t";
        file += "std::cout<<";
        if(exemp.keys[1] == "nc") file += "newton_kotes(";
        if(exemp.keys[1] == "gl") file += "gauss_legendre(";
        file += "func, ";
        file += exemp.keys[2] + ", " + exemp.keys[3];
        if(exemp.keys[1] == "nc"){
            if(exemp.qunt_keys > 4)
                file += ", " + exemp.keys[4];
            else file += ", 2";
            if(exemp.qunt_keys > 5)
                file += ", " + exemp.keys[5];
            else file += ", 10";
        }
       file += ");\n}";
    }
    return file;
}
