#include "bits/stdc++.h"

#include "Range.h"

using namespace std;
using namespace Linear;


int main() {
    Matrix<3, 5> m {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

    vector v{1, 2, 3, 4, 5};
    copy(m.row_ref(0).begin(),  m.row_ref(0).end(), m.row_ref(1).begin());

    Vector<5> vv = Vector<5>(v) + Vector<5>(m.row_ref(1));

    for (RowRef r : MatrixRowRange(m)) {
        for (int item : r) {
            cout << item << " ";
        }
        cout << endl;
    }

    Vector<3, int> v1 {1, 2, 3};
    Vector<3, int> v2 {2, 3, 4};

    MatrixRowRange range(m);
    RowRef r = m.row_ref(1);

    Matrix m1 {
            {1, 2},
            {1, 2}
    };

    auto v3 = v1 + v2;

    return 0;
}
