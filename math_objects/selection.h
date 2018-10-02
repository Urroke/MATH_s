#ifndef SELECTION_H_INCLUDED
#define SELECTION_H_INCLUDED
#include "../little_math/little_math.h"

template <typename type>
class selection{
private:
   vector<type>* data;
public:
    selection();
    selection(vector<type> &exemp);
    ~selection();

    type moment(size_t degree);
    type A();
    type E();
};

#include "selection.cpp"
#endif // SELECTION_H_INCLUDED
