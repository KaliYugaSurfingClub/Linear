#include "bits/stdc++.h"

#include "Range.h"

using namespace std;
using namespace Linear;


int main() {
    Matrix<3, 5> m {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

    for (int i = 0; i < 3; ++i) {
        for (auto j : m.row_copy(i)) {
            cout << j << " ";
        }
        cout << endl;
    }

    Vector<3, int> v1 {1, 2, 3};
    Vector<3, int> v2 {2, 3, 4};

    auto v3 = v1 + v2;

    return 0;
}
