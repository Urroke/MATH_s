#include "little_math.h"

template <typename type, size_t size>
mvector<type, size> method_of_gauss(matrix<type, size, size> A, mvector<type, size> b, bool somde)
{
    mvector<size_t, size> numbers;
    mvector<type, size> x, res;
    if(somde)
        try{
            numbers = sample_of_main_diagonal_elements(A ,b, numbers);
        }catch(except val)
        {
            if(val != except::no_diagonal_dominance)
                throw val;
        }
    else
        for(int i = 0;i < size;i++)
            numbers[i] = i;
    type coef;
    for(int i = 0;i < size - 1;i++)
        for(int j = i + 1;j < size;j++){
            coef = A[j][i]/A[i][i];
            for(int k = i;k < size;k++)
                A[j][k] -= coef*A[i][k];
            b[j] -= coef*b[i];
        }
    for(int i = size - 1;i >= 0;i--){
        x[i] = b[i];
        for(int j = i + 1; j < size;j++)
            x[i] -= x[j]*A[i][j];
        x[i] /= A[i][i];
        res[numbers[i]] = x[i];
    }
    return res;
}
