/********************************************************************************
 * Author: 黃煜展
 * Date: 2026-10-17
 * Purpose: Implementation of SparseMatrixLL class operations.
 ********************************************************************************/

#include "SparseMatrixLL.h"

SparseMatrixLL::SparseMatrixLL(int nrows, int ncols) : _nrows(nrows), _ncols(ncols), _row_list(nrows) {
    if (nrows <= 0 || ncols <= 0) {
        throw invalid_argument("Matrix dimensions must be positive.");
    }
}

void SparseMatrixLL::set(int row, int col, int value) {
    check_row(row);
    check_col(col);

    Node<MatrixEntry>* current = _row_list[row].getHead();
    while (current != nullptr) {
        if (current->getData().col == col) {
            if (value == 0) {
                _row_list[row].remove(MatrixEntry(col, 0));
            } else {
                current->setData(MatrixEntry(col, value));
            }
            return;
        }
        current = current->getNext();
    }

    if (value != 0) {
        _row_list[row].add(MatrixEntry(col, value));
    }
}

int SparseMatrixLL::get(int row, int col) const {
    check_row(row);
    check_col(col);

    Node<MatrixEntry>* current = _row_list[row].getHead();
    while (current != nullptr) {
        if (current->getData().col == col) {
            return current->getData().val;
        }
        current = current->getNext();
    }
    return 0;
}

SparseMatrixLL SparseMatrixLL::operator+(const SparseMatrixLL& other) const {
    if (_nrows != other._nrows || _ncols != other._ncols) {
        throw invalid_argument("Matrix dimensions do not match for addition.");
    }

    SparseMatrixLL result(_nrows, _ncols);
    for (int i = 0; i < _nrows; ++i) {
        unordered_map<int, int> row_sums;

        Node<MatrixEntry>* curr1 = _row_list[i].getHead();
        while (curr1 != nullptr) {
            row_sums[curr1->getData().col] += curr1->getData().val;
            curr1 = curr1->getNext();
        }

        Node<MatrixEntry>* curr2 = other._row_list[i].getHead();
        while (curr2 != nullptr) {
            row_sums[curr2->getData().col] += curr2->getData().val;
            curr2 = curr2->getNext();
        }

        for (const auto& pair : row_sums) {
            if (pair.second != 0) {
                result.set(i, pair.first, pair.second);
            }
        }
    }
    return result;
}

SparseMatrixLL SparseMatrixLL::transpose() const {
    SparseMatrixLL result(_ncols, _nrows);
    for (int i = 0; i < _nrows; ++i) {
        Node<MatrixEntry>* curr = _row_list[i].getHead();
        while (curr != nullptr) {
            int col = curr->getData().col;
            int val = curr->getData().val;
            result.set(col, i, val);
            curr = curr->getNext();
        }
    }
    return result;
}

SparseMatrixLL SparseMatrixLL::operator*(const SparseMatrixLL& other) const {
    if (_ncols != other._nrows) {
        throw invalid_argument("Matrix dimensions incompatible for multiplication.");
    }

    SparseMatrixLL result(_nrows, other._ncols);
    SparseMatrixLL otherT = other.transpose();

    for (int i = 0; i < _nrows; ++i) {
        for (int j = 0; j < other._ncols; ++j) {
            unordered_map<int, int> mapA;
            Node<MatrixEntry>* currA = _row_list[i].getHead();
            while (currA != nullptr) {
                mapA[currA->getData().col] = currA->getData().val;
                currA = currA->getNext();
            }

            int sum = 0;
            Node<MatrixEntry>* currB = otherT._row_list[j].getHead();
            while (currB != nullptr) {
                int col = currB->getData().col;
                if (mapA.find(col) != mapA.end()) {
                    sum += mapA[col] * currB->getData().val;
                }
                currB = currB->getNext();
            }

            if (sum != 0) {
                result.set(i, j, sum);
            }
        }
    }
    return result;
}

void SparseMatrixLL::check_row(int row) const {
    if (row < 0 || row >= _nrows) {
        throw out_of_range("Row number is out of range");
    }
}

void SparseMatrixLL::check_col(int col) const {
    if (col < 0 || col >= _ncols) {
        throw out_of_range("Column number is out of range");
    }
}

int SparseMatrixLL::len() const {
    int total_entries = 0;
    for (const auto& row_list : _row_list) {
        Node<MatrixEntry>* current = row_list.getHead();
        while (current) {
            total_entries++;
            current = current->getNext();
        }
    }
    return total_entries;
}

void SparseMatrixLL::from_dense_matrix(const std::vector<std::vector<int>>& dense_matrix) {
    if (dense_matrix.empty() || dense_matrix[0].empty()) {
        throw std::invalid_argument("Dense matrix must be non-empty");
    }
    int nrows = dense_matrix.size();
    int ncols = dense_matrix[0].size();
    if (nrows != _nrows || ncols != _ncols) {
        throw std::invalid_argument("Dense matrix dimensions must match the sparse matrix dimensions");
    }
    for (int i = 0; i < _nrows; ++i) {
        for (int j = 0; j < _ncols; ++j) {
            if (dense_matrix[i][j] != 0) {
                this->set(i, j, dense_matrix[i][j]);
            }
        }
    }
}

std::vector<std::vector<int>> SparseMatrixLL::to_dense() const {
    std::vector<std::vector<int>> dense_matrix(_nrows, std::vector<int>(_ncols, 0));
    for (int i = 0; i < _nrows; ++i) {
        for (int j = 0; j < _ncols; ++j) {
            dense_matrix[i][j] = this->get(i, j);
        }
    }
    return dense_matrix;
}

void SparseMatrixLL::printout() const {
    for (int i = 0; i < _nrows; ++i) {
        bool rowHasNonZero = false;
        std::stringstream ss;
        ss << "[" << i << "]:";
        for (int j = 0; j < _ncols; ++j) {
            int value = this->get(i, j);
            if (value != 0) {
                ss << " " << j << ": " << value;
                rowHasNonZero = true;
            }
        }
        if (rowHasNonZero) {
            std::cout << ss.str() << std::endl;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const SparseMatrixLL& matrix) {
    for (int i = 0; i < matrix._nrows; ++i) {
        for (int j = 0; j < matrix._ncols; ++j) {
            os << matrix.get(i, j) << " ";
        }
        os << "\n";
    }
    return os;
}