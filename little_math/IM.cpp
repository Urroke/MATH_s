#ifndef IM_H_INCLUDED
#define IM_H_INCLUDED
#include "little_math.h"

template <typename type, size_t size>
mvector<type,size> IM(matrix<type,size,size> mat, mvector<type,size>
                        vec, double eps, mvector<type,size> initial_approx, std::string options)
{
    int* numbers = new int[size];
    for(int i = 0;i < size;i++)
        numbers[i] = i;
    int maxX, maxY;

    for(int i = 0;i < size - 1;i++){
        maxX = i, maxY = i;
        for(int j = i;j < size;j++)
            for(int k = i;k < size;k++)
                if(mat[maxY][maxX] < mat[j][k]){
                    maxY = j; maxX = k;
                }
        swap(vec[i],vec[maxY]);
        swap(numbers[i],numbers[maxX]);
        mat.swap_elements(i,i,maxY,maxX);
    }
    double diag = 0,other = 0;
    for(int i = 0;i < size;i++){
        diag += mat[i][i];
        for(int j = 0;j < size;j++)
            if(i != j) other += mat[i][j];
    }

    if(diag < other) throw 1;
    diag = 1;

    for(int i = 0;i < size;i++)
        diag *= mat[i][i];

    if(diag == 0) throw 2;

    mvector<type,size> aprox = initial_approx, result;
    type err;

    do{
        for(int i = 0;i < size;i++){
            result[i] = vec[i];
            for(int j = 0;j < size;j++)
                if(i != j)
                    result[i] -= mat[i][j]*aprox[j];
            result[i] /= mat[i][i];
        }

        for(int i = 0;i < size - 1;i++)
            err = std::max(std::abs(result[i] - aprox[i]),std::abs(result[i + 1] - aprox[i + 1]));
        aprox = result;
    }
    while(err > eps);

    for(int i = 0;i < size;i++)
        result[i] = aprox[numbers[i]];

    delete[] numbers;
    return result;
}

template <typename type,size_t size>
matrix<type, size, size> converse_IM(matrix<type, size, size> exemp, double eps)
{
    matrix<type,size,size> ones('E');
    for(int i = 0;i < size;i++)
        ones.set_colum(IM(exemp,ones.get_colum(i),eps,ones.get_colum(i)),i);
    return ones;
}

#endif
