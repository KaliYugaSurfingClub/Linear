#include "bits/stdc++.h"

#include "Range.h"
#include "Operations.h"

using namespace std;
using namespace Linear;


void f(const Matrix<3, 3> &m) {
    *MatrixElmRange(m).begin() = 88;
}

int main() {
//    Matrix<3, 5> m {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
//
//    vector v{1, 2, 3, 4, 5};
//    copy(m.row_ref(0).begin(),  m.row_ref(0).end(), m.row_ref(1).begin());
//
//    Vector<5> vv = Vector<5>(v) + Vector<5>(m.row_ref(1));
//
//    for (RowRef r : MatrixRowRange(m)) {
//        for (int item : r) {
//            cout << item << " ";
//        }
//        cout << endl;
//    }
//
//    Vector<3, int> v1 {1, 2, 3};
//    Vector<3, int> v2 {2, 3, 4};
//
//    MatrixRowRange range(m);
//    RowRef r = m.row_ref(1);
//
//
//    Matrix<3, 3> m1{1, 0, 0, 0, 1, 0, 0, 0, 1};
//    Matrix<3, 3> m2;
//
//    for (RowRef r : MatrixRowRange(m1)) {
//        for (int item : r) {
//            cout << item << " ";
//        }
//        cout << endl;
//    }
//
//    m2 = m1 * m1 * m1;
//
//    for (RowRef r : MatrixRowRange(m2)) {
//        for (int item : r) {
//            cout << item << " ";
//        }
//        cout << endl;
//    }

    Matrix<3, 3> m1{-2, 1, 2, 1, 3, 4, 1, -5, 5};

    cout << m1.det() << endl;

    return 0;
}
