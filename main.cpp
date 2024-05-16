#include "bits/stdc++.h"

#include "Matrix.h"
#include "Ref.h"
#include "Operator.h"

using namespace std;
using namespace Linear;


void f( Matrix<3, 3, int> &m) {
    *m.elems().begin() = 88;
}

template<typename T>
void g(T ptr) {
    cout << ptr << endl;
}

int main() {
    Matrix<3, 5, int> m {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

    array<int, 3> a{0};
    auto i = next(a.begin(), 10);
    g(i);

    vector v{1, 2, 3, 4, 5};
    copy(m.row(0).begin(), m.row(0).end(), m.row(1).begin());
    Vector<5, int>(m.row(1));

//    Vector<5, int> vv = Vector<5, int>(v) + Vector<5, int>(m.row(1));

    for (RowRef r : m.rows()) {
        for (int item : r) {
            cout << item << " ";
        }
        cout << endl;
    }

    Vector<3, int> v1 {1, 2, 3};
    Vector<3, int> v2 {2, 3, 4};

    RowRef r = m.row(1);


    Matrix<3, 3, int> m1{1, 0, 0, 0, 1, 0, 0, 0, 1};
    Matrix<3, 3, int> m2;

    for (RowRef r : m.rows()) {
        for (int item : r) {
            cout << item << " ";
        }
        cout << endl;
    }

    for (RowRef r : m2.rows()) {
        for (int item : r) {
            cout << item << " ";
        }
        cout << endl;
    }

    Matrix<3, 3, int> m12{-2, 1, 2, 1, 3, 4, 1, -5, 5};

    cout << m12.det() << endl;

    auto mmm = Matrix<3, 3, int>::identity();

    return 0;
}
