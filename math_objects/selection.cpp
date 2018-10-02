#include "selection.h"

template <typename type>
selection<type>::selection(){;}

template <typename type>
selection<type>::~selection()
{
    if(data != nullptr)
        delete data;
}

template <typename type>
selection<type>::selection(vector<type> &exemp)
{
    data = &exemp;
}

template <typename type>
type selection<type>::moment(size_t degree)
{
    type* averages_in_degrees = new type[degree];
    type res = 0;

    for(int i = 0;i < degree;i++){
        averages_in_degrees[i] = 0;
        for(int j = 0;j < (*data).size();j++)
            averages_in_degrees[i] += std::pow((*data)[j], i + 1);
        averages_in_degrees[i] /= (*data).size();
    }

    for(int i = 1;i < degree;i++)
        res += C(degree, i + 1)*std::pow(-1,degree - i + 1)*averages_in_degrees[i]*std::pow(averages_in_degrees[0],degree - i - 1);
    res -= (degree - 1)*std::pow(-averages_in_degrees[0],degree);

    delete[] averages_in_degrees;

    return res;
}

template <typename type>
type selection<type>::A()
{
    return moment(3)/std::pow(moment(2),double(3)/2);
}

template <typename type>
type selection<type>::E()
{
    return moment(4)/std::pow(moment(2),2) - 3;
}

