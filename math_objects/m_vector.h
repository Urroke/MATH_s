#ifndef M_VECTOR_H_INCLUDED
#define M_VECTOR_H_INCLUDED
#include "../support_libs.h"
using namespace std;

template <typename Type,size_t _size>
class mvector{
private:

    template<typename lhs, typename rhs>
    static constexpr bool combined = is_same<lhs, rhs>::value ||
                                          is_convertible<lhs, rhs>::value;

    array<Type,_size> values;
public:
    template <typename lhs,typename rhs>
    using enable_type_combined = typename enable_if<combined<lhs,rhs>,void>::type;
    mvector();
    mvector(std::initializer_list<Type> exemp){
        std::copy(exemp.begin(), exemp.end(), values.begin());
    }
    ~mvector();
    mvector<Type, _size>& operator=(const std::initializer_list<Type>& exemp){
        std::copy(exemp.begin(), exemp.end(), values.begin());
        return *this;
    }
    template <typename other_type,typename temp = enable_type_combined<Type,other_type>>
    mvector<Type,_size>& operator+=(const mvector<other_type,_size>& exemp);

    template <typename other_type,typename temp = enable_type_combined<Type,other_type>>
    mvector<Type,_size>& operator-=(const mvector<other_type,_size>& exemp);

    template <typename other_type,typename temp = enable_type_combined<Type,other_type>>
    mvector<Type,_size>& operator=(const mvector<other_type,_size>& exemp);

    template <typename other_type,typename temp = enable_type_combined<Type,other_type>>
    mvector<Type,_size>& operator*=(const other_type& exemp);

    template <typename other_type,typename temp = enable_type_combined<Type,other_type>>
    mvector<Type,_size>& operator/=(const other_type& exemp);

    //mvector<Type, _size>& operator{}(const std::initializer_list<Type>& exemp);

    Type& operator[](const size_t& index);

    const Type& operator[](const size_t& index) const;

    template <size_t a, size_t b>
    mvector<Type, b - a> get_interval();

    template <typename T,size_t size>
    friend istream& operator>>(istream& in,mvector<T,size>& exemp);

    template <typename T,size_t size>
    friend ostream& operator<<(ostream& out,const mvector<T,size>& exemp);

    mvector<Type,_size> normalized();
    Type magnitude();
    void normalize();
    Type max();
    Type min();
    size_t size();
};

template<typename lhs,typename rhs,size_t _size,typename temp = typename
        mvector<typename common_type<lhs,rhs>::type,_size>::template enable_type_combined<lhs,rhs>>
typename common_type<lhs,rhs>::type operator*(const mvector<lhs,_size>& lhs_value,const mvector<rhs,_size>& rhs_value);

template<typename lhs,typename rhs,size_t _size,typename temp = typename
        mvector<typename common_type<lhs,rhs>::type,_size>::template enable_type_combined<lhs,rhs>>
mvector<typename common_type<lhs,rhs>::type,_size>
operator*(const mvector<lhs,_size>& lhs_value,const rhs& rhs_value);

template<typename lhs,typename rhs,size_t _size,typename temp = typename
        mvector<typename common_type<lhs,rhs>::type,_size>::template enable_type_combined<lhs,rhs>>
mvector<typename common_type<lhs,rhs>::type,_size>
operator*(const lhs& lhs_value, const mvector<rhs,_size>& rhs_value);

template<typename lhs,typename rhs,size_t _size,typename temp = typename
        mvector<typename common_type<lhs,rhs>::type,_size>::template enable_type_combined<lhs,rhs>>
mvector<typename common_type<lhs,rhs>::type,_size>
operator/(const mvector<lhs,_size>& lhs_value,const rhs& rhs_value);

template<typename lhs,typename rhs,size_t _size,typename temp = typename
        mvector<typename common_type<lhs,rhs>::type,_size>::template enable_type_combined<lhs,rhs>>
mvector<typename common_type<lhs,rhs>::type,_size>
operator+(const mvector<lhs,_size>& lhs_value,const mvector<rhs,_size>& rhs_value);

template<typename lhs,typename rhs,size_t _size,typename temp = typename
        mvector<typename common_type<lhs,rhs>::type,_size>::template enable_type_combined<lhs,rhs>>
mvector<typename common_type<lhs,rhs>::type,_size>
operator-(const mvector<lhs,_size>& lhs_value,const mvector<rhs,_size>& rhs_value);


#include "m_vector.cpp"

#endif
