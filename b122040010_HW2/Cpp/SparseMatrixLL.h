/********************************************************************************
 * Author: 黃煜展
 * Date: 2026-10-17
 * Purpose: Header file for MatrixEntry structure and SparseMatrixLL class.
 ********************************************************************************/

#ifndef SPARSE_MATRIX_LL_H
#define SPARSE_MATRIX_LL_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <unordered_map>
#include "linked_list.cpp"

using namespace std;

// --- MatrixEntry Structure ---
struct MatrixEntry {
    int col;
    int val;

    MatrixEntry(int column_number = 0, int value = 0) : col(column_number), val(value) {}
    bool operator==(const MatrixEntry &other) const { return col == other.col; }
};

// --- SparseMatrixLL Class Definition ---
class SparseMatrixLL {
private:
    int _nrows;
    int _ncols;
    vector<UnorderedList<MatrixEntry>> _row_list;

public:
    SparseMatrixLL(int nrows, int ncols);

    void set(int row, int col, int value);
    int get(int row, int col) const;

    SparseMatrixLL operator+(const SparseMatrixLL& other) const;
    SparseMatrixLL transpose() const;
    SparseMatrixLL operator*(const SparseMatrixLL& other) const;

    void check_row(int row) const;
    void check_col(int col) const;
    int len() const;

    void from_dense_matrix(const std::vector<std::vector<int>>& dense_matrix);
    std::vector<std::vector<int>> to_dense() const;
    void printout() const;

    int getRows() const { return _nrows; }
    int getCols() const { return _ncols; }

    friend std::ostream& operator<<(std::ostream& os, const SparseMatrixLL& matrix);
};

#endif