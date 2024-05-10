#include "bits/stdc++.h"

#include "Ranges.h"

using namespace std;
using namespace Liner;

struct Test {
    static void vector_() {
        vector<int> vec(3, 3);

        Vector<3> v31{vec};
        Vector<3> v32{vec.begin(), vec.end()};

        try {
            Vector<4> v41{vec};
        } catch (exception &e) {
            cout << e.what() << endl;
        }

        try {
            Vector<4> v41{vec.begin(), vec.end()};
        } catch (exception &e) {
            cout << e.what() << endl;
        }

        Vector<3> v = {1, 2, 3};

        cout << (v == v31) << endl;
        cout << (v == Vector<3>{1, 2, 3}) << endl;
    }

    static void vector_op() {
        Vector<3> v1 = {1, 2, 3};
        Vector<3> v2 = {4, 5, 6};

        auto v3 = v1 + v2;
        auto v4 = 5 * v3;
        auto v5 = v4 * 5;

        v5 *= 7;

        v5 += v2;

        auto i{1};
    }

    static void matrix_() {
        Matrix<3, 4> m{
                {1,  2,  3},
                {4,  5,  6},
                {7,  8,  9},
                {10, 11, 12}
        };

        auto r = m.row(1);
        try {
            auto r1 = m.row(-1);
        } catch (exception &e){
            cout << e.what() << endl;
        }

        try {
            auto r1 = m.row(3);
        } catch (exception &e){
            cout << e.what() << endl;
        }

        auto c = m.column(1);
        try {
            auto c1 = m.column(-2);
            auto i{1};
        }
        catch (exception &e){
            cout << e.what() << endl;
        }

        try {
            auto c1 = m.column(5);
            auto i{1};
            cout << i;
        }
        catch (exception &e){
            cout << e.what() << endl;
        }

        m(2, 3) = 1488;
        auto elem = m(2, 3);
        cout << elem << endl;
        try {
            auto e1 = m(-1, 1);
            cout << e1 << endl;
        } catch (exception &e) {
            cout << e.what() << endl;
        }

        try {
            auto e1 = m(-1, 1);
            cout << e1 << endl;
        } catch (exception &e) {
            cout << e.what() << endl;
        }

        try {
            auto e1 = m(1, 3);
        } catch (exception &e) {
            cout << e.what() << endl;
        }

        try {
            auto e1 = m(4, 1);
        } catch (exception &e) {
            cout << e.what() << endl;
        }

        return;
    }
};

int main() {

    Matrix<3, 4, int> m {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}};

//    cout << m(0, 3) << endl;
//
//    for (int item : MatrixRange(m)) {
//        cout << item << endl;
//    }

    int x = 10;
    int &xref = x;

    xref = const_cast<const int &>(xref);

    xref = 11;

//    MatrixElemIterConst i(m, 0);
    MatrixElemIter i1(m, 0);

    for (int &item : MatrixRange(m)) {
        item = 88;
    }

    Matrix<2, 2> m1;
    vector<int> v{1, 4, 8, 8};
    copy(v.begin(), v.end(), MatrixRange(m).begin());
    copy(MatrixRange(m).begin(), MatrixRange(m).end(), back_inserter(v));
    transform(MatrixRange(m).begin(), MatrixRange(m).end(), v.begin(), [](int i) {
        return i * 88;
    });

    return 0;
}
