__author__ = 'Duzitong'


from MyAlgebra import ModInt, Matrix, gaussian_elimination

a = ModInt(1, 5)
b = ModInt(2, 3)

l = [[1, 2, 3], [2, 3, 4], [3, 4, 5]]

ml = Matrix(l)

print(ml)

for i in gaussian_elimination(a, b):
    print(i)