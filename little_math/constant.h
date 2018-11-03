#ifndef CONSTANT_H_INCLUDED
#define CONSTANT_H_INCLUDED

int newton_kotes_table[7][9] = {
{2, 1 , 1},
{6, 1, 4, 1},
{8, 1, 3, 3, 1},
{90, 7, 32, 12, 32, 7},
{288, 19, 75, 50, 50, 75, 19},
{840, 41, 216, 27, 272, 27, 216, 41},
{17280, 751, 3577, 1223, 2989, 2989, 1223, 3577, 751}
};

double GLQ_weight[6] = {
   0.171324492,
   0.360761573,
   0.467913935,
   0.467913935,
   0.360761573,
   0.171324492
};

double GLQ_points[6] = {
    -0.932469514,
    -0.661209386,
    -0.238619186,
    0.238619186,
    0.661209386,
    0.932469514
};


#endif // CONSTANT_H_INCLUDED
