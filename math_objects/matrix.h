#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED
#include "m_vector.h"
template <typename Type, size_t sizeY, size_t sizeX>
class matrix
{
private:
    class proxy_variable;
    class proxy_const;
    template<typename lhs,typename rhs>
    static constexpr bool combined = is_same<lhs,rhs>::value||
                                        is_convertible<lhs,rhs>::value;

    const size_t _size = sizeY*sizeX;
    array<Type,sizeX*sizeY> values;

public:
    template<typename lhs,typename rhs>
    using enable_type_combined = typename enable_if<combined<lhs,rhs>,void>::type;

    using eneble_type_square = typename enable_if<sizeX == sizeY,void>::type;

    matrix();
    matrix(char type_name);
    ~matrix();

    proxy_variable operator[](const size_t& index);
    proxy_const operator[](const size_t& index)const;

    matrix<Type,sizeY,sizeX>& operator=(const matrix<Type,sizeY,sizeX>& exemp);

    template<typename other_type,typename temp = enable_type_combined<Type,other_type>>
    matrix<Type,sizeY,sizeX>& operator=(const matrix<other_type,sizeY,sizeX>& exemp);

    template<typename other_type,typename temp = enable_type_combined<Type,other_type>>
    matrix<Type,sizeY,sizeX>& operator+=(const matrix<other_type,sizeY,sizeX>& exemp);

    template<typename other_type,typename temp = enable_type_combined<Type,other_type>>
    matrix<Type,sizeY,sizeX>& operator-=(const matrix<other_type,sizeY,sizeX>& exemp);

    template<typename other_type,typename temp = enable_type_combined<Type,other_type>>
    matrix<Type,sizeY,sizeX>& operator/=(const other_type& exemp);

    template<typename other_type,typename temp = enable_type_combined<Type,other_type>>
    matrix<Type,sizeY,sizeX>& operator*=(const other_type& exemp);

    template<typename T,size_t Y,size_t X>
    friend istream& operator>>(istream& in,matrix<T,Y,X>& exemp);

    template<typename T,size_t Y,size_t X>
    friend ostream& operator<<(ostream& out,matrix<T,Y,X>& exemp);

    template<typename lhs,typename rhs,size_t Y,size_t X, typename temp>
    friend matrix<typename common_type<lhs,rhs>::type,Y,X>
    operator+(const matrix<lhs,Y,X>& lhs_value,const matrix<rhs,Y,X>& rhs_value);

    template<typename lhs,typename rhs,size_t Y,size_t X, typename temp>
    friend matrix<typename common_type<lhs,rhs>::type,Y,X>
    operator-(const matrix<lhs,Y,X>& lhs_value,const matrix<rhs,Y,X>& rhs_value);

    template<typename lhs,typename rhs,size_t lhs_Y,size_t lhs_X,size_t rhs_Y,size_t rhs_X,typename temp>
    friend matrix<typename common_type<lhs,rhs>::type,lhs_Y,rhs_X>
    operator*(const matrix<lhs,lhs_Y,lhs_X>& lhs_value,const matrix<rhs,rhs_Y,rhs_X>& rhs_value);

    template<typename lhs,typename rhs,size_t Y,size_t X,typename temp>
    friend mvector<typename common_type<lhs,rhs>::type,Y>
    operator*(const matrix<lhs,Y,X>& lhs_value,const mvector<rhs,X>& rhs_value);

    template<typename lhs,typename rhs,size_t Y,size_t X,typename temp>
    friend mvector<typename common_type<lhs,rhs>::type,Y>
    operator*(const mvector<lhs,X>& lhs_value, const matrix<rhs,Y,X>& rhs_value);

    template<typename lhs,typename rhs,size_t Y,size_t X,typename temp>
    friend matrix<typename common_type<lhs,rhs>::type,Y,X>
    operator*(const matrix<lhs,Y,X>& lhs_value,const rhs& rhs_value);

    template<typename lhs,typename rhs,size_t Y,size_t X,typename temp>
    friend matrix<typename common_type<lhs,rhs>::type,Y,X>
    operator*(const lhs& lhs_value, const matrix<rhs,Y,X>& rhs_value);

    template<typename lhs,typename rhs,size_t Y,size_t X,typename temp>
    friend matrix<typename common_type<lhs,rhs>::type,Y,X>
    operator/(const matrix<lhs,Y,X>& lhs_value,const rhs& rhs_value);

    template<typename temp = eneble_type_square>
    void sample_of_main_diagonal_elements();

    template<typename temp = eneble_type_square>
    matrix<Type,sizeY,sizeX> get_sample_of_main_diagonal_elements();

    void trangle_view();

    matrix<Type,sizeY,sizeX> get_trangle_view();

    void transposed();

    matrix<Type,sizeY,sizeX> get_transposed();

    template<typename temp = eneble_type_square>
    void conversed();

    template<typename temp = eneble_type_square>
    matrix<Type,sizeY - 1,sizeX - 1> get_conversed();

    mvector<Type,sizeY> get_colum(size_t index);

    mvector<Type,sizeX> get_line(size_t index);

    void set_colum(mvector<Type,sizeY> exemp, size_t index);

    void set_line(mvector<Type,sizeX> exemp, size_t index);

    void swap_elements(size_t x1,size_t y1,size_t x2,size_t y2);
};

#include "matrix.cpp"
#endif
