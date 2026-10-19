from SparseMatrixLL import SparseMatrixLL

# Example usage
m1 = SparseMatrixLL(3, 3)
m1[0, 0] = 1
m1[1, 1] = 2
print("m1:\n", m1, sep='')

m2 = SparseMatrixLL(3, 3)
m2[1, 1] = 3
m2[2, 2] = 4
print("m2:\n", m2, sep='')

m3 = SparseMatrixLL(3, 2)
m3[0, 0] = 1
m3[1, 1] = 2
print("m3:\n", m3, sep='')

m4 = SparseMatrixLL(2, 3)
m4[0, 0] = 1
m4[1, 1] = 3
print("m4:\n", m4, sep='')

m5 = m1 + m2
print("m5 = m1 + m2:\n", m5, sep='')

m6 = m1.transpose()
print("m6 = transpose(m1):\n", m6, sep='')

m7 = m3 * m4
print("m7 = m3 * m4:\n", m7, sep='')

m8 = SparseMatrixLL(3, 3)  # Create an instance with the desired dimensions
print(m8)
dense_matrix = [
    [0, 2, 3],
    [0, 0, 0],
    [4, 0, 0]
]
m8.from_dense_matrix(dense_matrix)
print("m8:\n", m8, sep='')  # Output will be the sparse representation of the dense matrix

m9 = m8 + SparseMatrixLL(3, 3)
print("m9 = m8 + 0:\n", m9, sep='')

m10 = m8.transpose()
print("m10 = transpose(m8):\n", m10, sep='')

m11 = m10 * SparseMatrixLL(3, 3)
print("m11 = m10 * 0:\n", m11, sep='')

m12 = m11 + m2
print("m12 = m11 + m2:\n", m12, sep='')

try:
    m13 = m10 + SparseMatrixLL(4, 4)
except Exception as e:
    print("An error occurred:", e)


original_m3 = m3.to_dense()
m14 = m3.transpose()
print("m14 = m3.transpose():\n", m14, sep='')
if (
    m14 is not m3
    and m3.to_dense() == original_m3
):
    print("m14: Passed (Original matrix unchanged)")
else:
    print("m14: Failed (Original matrix was modified)")

try:
    m15 = m10 * SparseMatrixLL(2, 3)
except Exception as e:
    print("An error occurred:", e)