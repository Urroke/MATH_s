#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED

enum except:int{
    no_diagonal_dominance = 1,
    zeros_on_the_diagonal = 2,
    negative_index = 3,
    index_outside_of_array = 4
};

#endif // ERROR_H_INCLUDED
