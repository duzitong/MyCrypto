__author__ = 'Duzitong'


from MyAlgebra import ModInt, Matrix, gaussian_elimination

a = ModInt(1, 5)
b = ModInt(2, 3)

l = [[1, 2], [2, 3], [3, 4]]
s = [[1], [2], [3]]

ml = Matrix(l)
ms = Matrix(s)

for i in gaussian_elimination(ml, ms):
    print(i)