#include "m_vector.h"

template <typename Type,size_t _size>
mvector<Type,_size>::mvector()
{
    for(int i = 0;i < _size;i++)
        values[i] = 0;
}

template <typename Type,size_t _size>
mvector<Type,_size>::~mvector(){}

template <typename Type,size_t _size>
template <typename other_type,typename temp>
    mvector<Type,_size>& mvector<Type,_size>::operator=(const mvector<other_type,_size>& exemp)
{
    for(size_t i = 0;i <_size ;i++)
        this->values[i] = static_cast<Type>(exemp[i]);
    return *this;
}

template <typename Type,size_t _size>
    mvector<Type,_size>& mvector<Type,_size>::operator=(const mvector<Type,_size>& exemp)
{
    for(size_t i = 0;i <_size ;i++)
        this->values[i] = exemp.values[i];
    return *this;
}

template <typename Type,size_t _size>
template <typename other_type,typename temp>
mvector<Type,_size>& mvector<Type,_size>::operator+=(const mvector<other_type,_size>& exemp)
{
    for(int i = 0;i < _size;i++)
        this->values[i] += static_cast<Type>(exemp[i]);
        return *this;
}

template <typename Type,size_t _size>
mvector<Type,_size>& mvector<Type,_size>::operator+=(const mvector<Type, _size>& exemp)
{
    for(int i = 0;i < _size;i++)
        this->values[i] += exemp.values[i];
    return *this;
}

template <typename Type,size_t _size>
template <typename other_type,typename temp>
mvector<Type,_size>& mvector<Type,_size>::operator-=(const mvector<other_type,_size>& exemp)
{
    for(int i = 0;i < _size;i++)
        this->values[i] -= static_cast<Type>(exemp[i]);
    return *this;
}

template <typename Type,size_t _size>
template <typename other_type,typename temp>
mvector<Type,_size>& mvector<Type,_size>::operator*=(const other_type& exemp)
{
    Type oper = static_cast<Type>(exemp);
    for(int i = 0;i < _size;i++)
        this->values[i] *= oper;
    return *this;
}

template <typename Type,size_t _size>
template <typename other_type,typename temp>
mvector<Type,_size>& mvector<Type,_size>::operator/=(const other_type& exemp)
{
    if(exemp == 0) throw invalid_argument("error: attempt to divide by 0");
    for(int i = 0;i < _size;i++)
        this->values[i] /= static_cast<Type>(exemp);
    return *this;
}

template <typename Type,size_t _size>
mvector<Type, _size> mvector<Type, _size>::operator+(const mvector<Type, _size>& rhs)
{
    mvector<Type, _size> result;
    for(int i = 0;i < _size;i++)
        result.values[i] = this->values[i] + rhs.values[i];
    return result;
}

template <typename Type,size_t _size>
mvector<Type, _size> mvector<Type, _size>::operator-(const mvector<Type, _size>& rhs)
{
    mvector<Type, _size> result;
    for(int i = 0;i < _size;i++)
        result.values[i] = this->values[i] - rhs.values[i];
    return result;
}

template <typename Type,size_t _size>
Type mvector<Type, _size>::operator*(const mvector<Type, _size>& rhs)
{
    Type result = 0;
    for(int i = 0;i < _size;i++)
        result += this->values[i] * rhs.values[i];
    return result;
}

template <typename Type,size_t _size>
Type& mvector<Type,_size>::operator[](const size_t& index)
{
    if(index >= values.size()) throw "Pisya tyt";
    else return  this->values[index];
}

template <typename Type,size_t _size>
const Type& mvector<Type,_size>::operator[](const size_t& index) const
{
    if(index >= values.size()) throw "Pisya tyt";
    else  return this->values[index];
}

template <typename Type, size_t _size>
template <size_t a, size_t b>
mvector<Type, b - a> mvector<Type,_size>::get_interval()
{
    if(a >= values.size()||b >= values.size()) throw invalid_argument("Index outside of array");
    mvector<Type, b - a> res;
    for(int i = 1;i < b - a;i++)
        res[i] = values[a + i];
    return res;
}

template <typename lhs,typename rhs,size_t _size,typename temp>
typename common_type<lhs,rhs>::type operator*(const mvector<lhs,_size>& lhs_value,const mvector<rhs,_size>& rhs_value)
{
    typename common_type<lhs,rhs>::type result;
    for(int i = 0;i < _size;i++)
        result += rhs_value[i]*lhs_value[i];
    return result;
}

template <typename lhs,typename rhs,size_t _size,typename temp>
mvector<typename common_type<lhs,rhs>::type,_size>
operator*(const mvector<lhs,_size>& lhs_value,const rhs& rhs_value)
{
    mvector<typename common_type<lhs,rhs>::type,_size> result;
    for(int i = 0;i < _size;i++)
        result[i] = lhs_value[i]*rhs_value;
    return result;
}

template <typename lhs,typename rhs,size_t _size,typename temp>
mvector<typename common_type<lhs,rhs>::type,_size>
operator/(const mvector<lhs,_size>& lhs_value,const rhs& rhs_value)
{
    mvector<typename common_type<lhs,rhs>::type,_size> result;
    for(int i = 0;i < _size;i++)
        result[i] = lhs_value[i]/rhs_value;
    return result;
}

template <typename lhs,typename rhs,size_t _size,typename temp>
mvector<typename common_type<lhs,rhs>::type,_size>
operator*(const lhs& lhs_value, const mvector<rhs,_size>& rhs_value)
{
    mvector<typename common_type<lhs,rhs>::type,_size> result;
    for(int i = 0;i < _size;i++)
        result[i] = rhs_value[i]*lhs_value;
    return result;
}

template<typename lhs,typename rhs,size_t _size,typename temp>
mvector<typename common_type<lhs,rhs>::type,_size>
operator+(const mvector<lhs,_size>& lhs_value,const mvector<rhs,_size>& rhs_value)
{
    mvector<typename common_type<lhs,rhs>::type,_size> exemp;
    for(int i = 0;i < _size;i++)
        exemp[i] = rhs_value[i] + lhs_value[i];
    return exemp;
}

template <typename lhs,typename rhs,size_t _size,typename temp>
mvector<typename common_type<lhs,rhs>::type,_size>
operator-(const mvector<lhs,_size>& lhs_value,const mvector<rhs,_size>& rhs_value)
{
    mvector<typename common_type<lhs,rhs>::type,_size> exemp;
    for(int i = 0;i < _size;i++)
        exemp[i] = lhs_value[i] - rhs_value[i];
    return exemp;
}

template <typename T,size_t size>
istream& operator>>(istream& in,mvector<T,size>& exemp)
{
    for(int i = 0;i < size;i++)
        in>>exemp.values[i];
    return in;
}

template <typename T,size_t size>
ostream& operator<<(ostream& out,const mvector<T,size>& exemp)
{
    for(int i = 0;i < size;i++)
        out<<exemp.values[i]<<"\n";
    out<<"\n";
    return out;
}

template<typename Type,size_t _size>
mvector<Type,_size> mvector<Type,_size>::normalized()
{
    return *this /= magnitude();
}

template<typename Type,size_t _size>
Type mvector<Type,_size>::magnitude()
{
    Type result = 0;
    for(int i = 0;i < _size;i++)
        result += values[i]*values[i];
    return std::sqrt(result);
}

template<typename Type,size_t _size>
void mvector<Type,_size>::normalize()
{
     mvector<Type,_size> exemp = *this;
    for(int i = 0;i < _size;i++)
        exemp.values[i] /= magnitude();
        *this = exemp;
}

template<typename Type,size_t _size>
Type mvector<Type,_size>::max()
{
    Type result = values[0];
    for(int i = 1;i < _size;i++)
        if(values[i] > result)
            result = values[i];
    return result;
}

template<typename Type,size_t _size>
Type mvector<Type,_size>::min()
{
    Type result = values[0];
    for(int i = 1;i < _size;i++)
        if(values[i] < result)
            result = values[i];
    return result;
}

template<typename Type,size_t _size>
size_t mvector<Type,_size>::size()
{
    return _size;
}
