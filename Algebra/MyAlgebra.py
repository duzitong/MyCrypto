__author__ = 'Duzitong'


class ModInt:
    def __init__(self, n, p):
        self.n = n % p
        self.p = p
        self.q = 0
        self.x = 0
        self.y = 0

    def __add__(self, other):
        return ModInt((self.n + other.n) % self.p, self.p)
    
    def __sub__(self, other):
        return ModInt((self.n - other.n) % self.p, self.p)

    def __mul__(self, other):
        return ModInt((self.n * other.n) % self.p, self.p)

    def __truediv__(self, other):
        other.extendEuclid(other.n, other.p)
        return ModInt((self.n * other.x) % self.p, self.p)

    def __str__(self):
        return str(self.n)

    def extend_euclid(self, a, b):
        if b == 0:
            self.x = 1
            self.y = 0
            self.q = a
        else:
            self.extend_euclid(b, a % b)
            self.x, self.y = self.y, self.x - a // b * self.y


class Matrix:
    def __init__(self, l):
        self.l = l
        try:
            self.validate()
        except Exception as e:
            raise e

    def __str__(self):
        s = ''
        for i in self.l:
            for j in i:
                s += '{:>10}'.format(j)
            s += '\n'
        return s

    def row_dim(self):
        return len(self.l)

    def col_dim(self):
        return len(self.l[0])

    def validate(self):
        """
        check whether the matrix is valid
        """
        try:
            assert len(self.l) > 0
            assert len(self.l[0]) > 0
        except Exception as e:
            print('Length of two dimension of matrix cannot be 0')
            raise e
        t = type(self.l[0][0])
        try:
            assert t == ModInt or t == int or t == float
        except Exception as e:
            print('Type can only be ModInt or int')
            raise e
        dim = len(self.l[0])
        for i in self.l:
            if len(i) != dim:
                raise ShapeException
            for j in i:
                if type(j) != t:
                    raise TypeException


class ShapeException(Exception):
    def __str__(self):
        print('Matrix shape is not valid')


class TypeException(Exception):
    def __str__(self):
        print('Type of elements are not same')


def gaussian_elimination(a, b):
    """ Solve the system of linear equations ax = b, return x"""
    x = (a, b)
    return x
