class C_Unsigned_Int:
    def __init__(self, val):
        assert 0 <= val < (1 << 32)
        self.val = val

    def __add__(self, x):
        if type(x) == C_Unsigned_Int:
                return C_Unsigned_Int((self.val + x.val) % (1 << 32))
        elif type(x) == int:
                return C_Unsigned_Int((self.val + x) % (1 << 32))
        else:
                raise Exception('Type Error')

    def __and__(self, x):
        if type(x) == C_Unsigned_Int:
            return C_Unsigned_Int((self.val & x.val) % (1 << 32))
        elif type(x) == int:
            return C_Unsigned_Int((self.val & x) % (1 << 32))
        else:
            raise Exception('Type Error')

    def __iadd__(self, x):
        if type(x) == C_Unsigned_Int:
            self.val = (self.val + x.val) % (1 << 32)
        elif type(x) == int:
            self.val = (self.val + x) % (1 << 32)
        else:
            raise Exception('Type Error')

    def __iand__(self, x):
        if type(x) == C_Unsigned_Int:
            self.val = (self.val & x.val) % (1 << 32)
        elif type(x) == int:
            self.val = (self.val & x) % (1 << 32)
        else:
            raise Exception('Type Error')

    def __inv__(self):
        return C_Unsigned_Int(~self.val % (1 << 32))

    def __invert__(self):
        return C_Unsigned_Int(~self.val % (1 << 32))

    def __lshift__(self, b):
        assert type(b) == int
        return C_Unsigned_Int((self.val << b) % (1 << 32))

    def __or__(self, x):
        if type(x) == C_Unsigned_Int:
            return C_Unsigned_Int((self.val | x.val) % (1 << 32))
        elif type(x) == int:
            return C_Unsigned_Int((self.val | x) % (1 << 32))
        else:
            raise Exception('Type Error')
  
    def __rshift__(self, b):
        assert type(b) == int
        return C_Unsigned_Int((self.val >> b))
  
    def __xor__(self, x):
        if type(x) == C_Unsigned_Int:
            return C_Unsigned_Int((self.val ^ x.val) % (1 << 32))
        elif type(x) == int:
            return C_Unsigned_Int((self.val ^ x) % (1 << 32))
        else:
            raise Exception('Type Error')

    def rotateL(self, b):
        assert type(b) == int
        return (self << b) | (self >> (32 - b))

    def rotateR(self, b):
        assert type(b) == int
        return (self << (32 - b)) | (self >> b)
