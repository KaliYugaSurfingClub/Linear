#include "bits/stdc++.h"

#include "Matrix.h"

using namespace std;
using namespace Linear;

//todo swap
//todo поддержка адаптеров, и алгоритмов, проблемы с jump_iterator


int main() {
    Matrix<2, 2, int> m = {1, 3, 2, 4};
    Matrix<2, 4, int> m1 = invert(m);


    return 0;
}
