#include "bits/stdc++.h"

#include "Range.h"

using namespace std;
using namespace Linear;

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
        auto v5 = v3 * 5;

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
    }
};

int main() {
    Matrix<3, 4, int> m {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}};
    Matrix<3, 4, int> m1 {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}};


    for (auto column_ref : MatrixColRange(m)) {
        if (std::accumulate(column_ref.begin(), column_ref.end(), 0) == 6) {
            column_ref *= 10;
        } else {
            column_ref = Vector{1, 2, 3};
        }

        column_ref += m.column_ref(1);
        column_ref[1] = 88;
    }

//    ranges::copy(vector{1, 2, 3}, MatrixElmRange(m).begin());

//    ranges::transform(MatrixColRange(m), MatrixElmRange(m).begin(), [](ColumnRef<3, 4, int> column) -> Vector<3, int> {
//        if (column[0] % 2 == 0) {
//            return column;
//        } else {
//            return Vector{1, 2, 3};
//        }
//    });



//    vector<int> v{1, 4, 8, 8};
//    copy(v.begin(), v.end(), MatrixElmRange(m).begin());
//    copy(MatrixElmRange(m).begin(), MatrixElmRange(m).end(), back_inserter(v));
//    transform(MatrixElmRange(m).begin(), MatrixElmRange(m).end(), v.begin(), [](int i) {
//        return i * 88;
//    });

//    m.column_ref(1) *= 10;
//
//    for (auto & item : MatrixElmRange(m)) {
//        item = 99;
//    }
//
//    for (auto col : MatrixColRange(m)) {
//        col *= 2;
//    }
//
//    for (auto row : MatrixRowRange(m)) {
//        row *= 2;
//    }



    return 0;
}
