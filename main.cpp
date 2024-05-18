#include "bits/stdc++.h"

#include "Matrix.h"

using namespace std;
using namespace Linear;

//todo swap

struct Test {

    static void vec_oper() {
        Matrix<3, 3, int> m {1, 2, 3, 4, 5, 6, 7, 8, 9};
        Vector<3, int> v3_1 {1, 2, 3};
        Vector<3, int> v3_2 {1, 2, 3};

        Matrix<3, 3, int>::RowRef ref = m.row(2);
        Matrix<3, 3, int>::RowRef ref1 = m.row(1);
        ref = ref1 = Vector{1, 2, 3};


        m.column(1) += Vector{1, 2, 3} + m.row(1);
        m.column(1) *= 10;

        for (auto row : m.columns()) {
            for (int elem : row) {
                cout << elem << " ";
            }
            cout << endl;
        }
        cout << endl;

        for (auto row : m.const_rows()) {
            for (int elem : row) {
                cout << elem << " ";
            }
            cout << endl;
        }
        cout << endl;

        auto v3_3 = v3_1 + v3_2;
        auto v3_4 = v3_1 + m.column(0);
        auto v3_5 = m.column(0) + v3_1;
        auto v3_6 = m.column(0) + m.row(1);

        if (v3_1 == m.column(0)) {}
        if (m.row(0) == m.column(0)) {}

        v3_1 += m.row(0);

        auto s = scalar_product(m.row(1), m.row(2));

        m.row(0) = Vector{1, 2, 3};
        m.row(0) = m.column(1);
        m.row(0) = m.row(1) = m.row(2);

        for (auto row : m.rows()) {
            for (int elem : row) {
                cout << elem << " ";
            }
            cout << endl;
        }
        cout << endl;

        std::for_each(m.rows().begin(), m.rows().end(), [](auto ref) {
            if (ref == Vector<3, int>{3, 170, 9}) {
                ref = Vector<3, int>{0, 0, 0};
            }
        });

        std::for_each(reverse_iterator(m.rows().begin()), m.rows().end(), [](auto r) {
            cout << 123;
        });

        for (auto row : m.rows()) {
            for (int elem : row) {
                cout << elem << " ";
            }
            cout << endl;
        }
        cout << endl;

    }

};


int main() {

    vector<int> v;

    Test::vec_oper();

    const Matrix<3, 3, int> m {1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (auto row : m.rows()) {
        for (int elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }
    cout << endl;

//
//    for (auto row : mat.rows()) {
//        row -= mat.row(0) * row[0];
//    }
//
//    auto ref = *mat.rows().begin();
//    ref = Vector<3, int>{};
//
//    std::for_each(mat.rows().begin(), mat.rows().end(), [&](auto ref) {
//        ref -= mat.row(0);
//    });
//
//
//    Matrix<3, 5, int> m {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
//
//    Vector<3, int> sdda{1, 2, 3};
//    Vector<3, int> asdasds{1, 2, 3};
////    sdda += asdasds;
//
////    auto assd = m * 8;
////    auto sad = o *8;
//
//    array<int, 3> a{0};
//    auto i = next(a.begin(), 10);
//
//    vector v{1, 2, 3, 4, 5};
//    copy(m.row(0).begin(), m.row(0).end(), m.row(1).begin());
//    Vector<5, int>(m.row(1));
//
////    Vector<5, int> vv = Vector<5, int>(v) + Vector<5, int>(m.row(1));
//
//    for (RowRef r : m.rows()) {
//        for (int item : r) {
//            cout << item << " ";
//        }
//        cout << endl;
//    }
//
//    Vector<3, int> v1 {1, 2, 3};
//    Vector<3, int> v2 {2, 3, 4};
//
//    RowRef r = m.row(1);
//
//
//    Matrix<3, 3, int> m1{1, 0, 0, 0, 1, 0, 0, 0, 1};
//    Matrix<3, 3, int> m2;
//
//    for (RowRef r : m.rows()) {
//        for (int item : r) {
//            cout << item << " ";
//        }
//        cout << endl;
//    }
//
//    for (RowRef r : m2.rows()) {
//        for (int item : r) {
//            cout << item << " ";
//        }
//        cout << endl;
//    }
//
//    Matrix<3, 3, int> m12{-2, 1, 2, 1, 3, 4, 1, -5, 5};
//
//    cout << m12.det() << endl;
//
//    auto E = Matrix<3, 3, int>::identity() * Matrix<3, 3, int>::identity();
//
//    auto mmm = Matrix<3, 3, int>::identity();

    return 0;
}
