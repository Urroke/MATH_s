#ifndef LITTLE_MATH_H_INCLUDED
#define LITTLE_MATH_H_INCLUDED
#include "../support_libs.h"
#include "../math_objects/matrix.h"

template <typename type, size_t size>
mvector<type,size> IM(matrix<type,size,size> mat, mvector<type,size>
                        vec, double eps, mvector<type,size> initial_approx, std::string options);

template <typename type,size_t size>
matrix<type, size, size> converse_IM(matrix<type, size, size> exemp, double eps);

#include "IM.cpp"
#endif
