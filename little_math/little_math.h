#ifndef LITTLE_MATH_H_INCLUDED
#define LITTLE_MATH_H_INCLUDED
#include "../support_libs.h"
#include "constant.h"
#include "../math_objects/matrix.h"
#include "../math_objects/function_object.h"

template <typename type, size_t size>
mvector<type,size> simple_iteration(matrix<type,size,size> mat, mvector<type,size>
                        vec, double eps, mvector<type,size> initial_approx, std::string options);

template <typename type, size_t size>
mvector<type,size> BiCGStab(const matrix<type,size,size>& A, const mvector<type,size>&
                        b, const double& eps, mvector<type,size> x);

template <typename type,size_t size>
matrix<type, size, size> converse_IM(matrix<type, size, size> exemp, double eps);

int C(size_t n,size_t k);

template <typename input, typename output>
output newton_kotes(math_function<input, output> func, size_t degree, input lhs, input rhs, size_t n);

template <typename type, size_t n, size_t degree>
mvector<type, degree + 1> method_of_min_suare(mvector<type, n> x, mvector<type, n> y);

template <typename type, size_t size>
mvector<type, size> method_of_gauss(matrix<type, size, size> x, mvector<type, size> b);

template <typename type, size_t size>
mvector<size_t, size> sample_of_main_diagonal_elements(matrix<type, size, size> &mat, mvector<type, size> &vec);

template <typename type, size_t size>
class polynom;

#include "IM.cpp"
#include "AM.cpp"
#include "solve_equations.cpp"
#include "newton_binom.cpp"
#include "integral.cpp"
#include "aprox.cpp"
#include "derivative.cpp"


#endif
