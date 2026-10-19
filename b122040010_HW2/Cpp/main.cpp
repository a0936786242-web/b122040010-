/********************************************************************************
 * Author: 黃煜展
 * Date: 2026-10-17
 * Purpose: Public test cases for SparseMatrixLL implementation.
 ********************************************************************************/

#include <iostream>
#include <vector>
#include "SparseMatrixLL.h"

using namespace std;

int main() {
    SparseMatrixLL m1(3, 3);
    m1.set(0, 0, 1);
    m1.set(1, 1, 2);
    cout << m1 << endl;

    SparseMatrixLL m2(3, 3);
    m2.set(1, 1, 3);
    m2.set(2, 2, 4);
    cout << m2 << endl;

    SparseMatrixLL m3(3, 2);
    m3.set(0, 0, 1);
    m3.set(1, 1, 2);
    cout << m3 << endl;

    SparseMatrixLL m4(2, 3);
    m4.set(0, 0, 1);
    m4.set(1, 1, 3);
    cout << m4 << endl;

    SparseMatrixLL m5 = m1 + m2;
    cout << m5 << endl;

    SparseMatrixLL m6 = m1.transpose();
    cout << m6 << endl;

    SparseMatrixLL m7 = m3 * m4;
    cout << m7 << endl;

    SparseMatrixLL m8(3, 3);
    cout << m8 << endl;
    vector<vector<int>> dense_matrix = {
        {0, 2, 3},
        {0, 0, 0},
        {4, 0, 0}
    };
    m8.from_dense_matrix(dense_matrix);
    cout << m8 << endl;
    
    SparseMatrixLL mm1(3, 3);
    SparseMatrixLL m9 = m8 + mm1;
    cout << m9 << endl;

    SparseMatrixLL m10 = m8.transpose();
    cout << m10 << endl;

    SparseMatrixLL m11 = m10 * mm1;
    cout << m11 << endl;

    SparseMatrixLL m12 = m11 + m2;
    cout << m12 << endl;

    try {
        SparseMatrixLL m13 = m10 + SparseMatrixLL(4, 4);
    } catch (const std::exception& e) {
        cout << "An error occurred: " << e.what() << endl;
    }

    const vector<vector<int>> original_m3 = m3.to_dense();
    SparseMatrixLL m14 = m3.transpose();
    cout << "m14 = m3.transpose():\n" << m14;
    if (&m14 != &m3 && m3.to_dense() == original_m3) {
        cout << "m14: Passed (Original matrix unchanged)" << endl;
    } else {
        cout << "m14: Failed (Original matrix was modified)" << endl;
    }

    try {
        SparseMatrixLL m15 = m10 * SparseMatrixLL(2, 3);
    } catch (const std::exception& e) {
        cout << "An error occurred: " << e.what() << endl;
    }

    return 0;
}