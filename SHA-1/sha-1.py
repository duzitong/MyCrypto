from C_Unsigned_Int import C_Unsigned_Int

def f(b, c, d, i):
    """
    f function + k
    """
    if 0 <= i < 20:
        return (d ^ (b & (c ^ d))) + 0x5a827999
    elif 20 <= i < 40:
        return (b ^ c ^ d) + 0x6ed9eba1
    elif 40 <= i < 60:
        return ((b & c) | (d & (b | c))) + 0x8f1bbcdc
    else:
        return (b ^ c ^ d) + 0xca62c1d6 

def sha_1(iv, message):
    """
    iv: 5 * 32-bit: list of 5 int
    message: 16 * 32-bit: list of 16 int
    return 5 * 32-bit
    """
    assert len(iv) == 5
    assert len(message) == 16
    a, b, c, d, e = [C_Unsigned_Int(i) for i in iv]
    w = [0 for i in range(80)]
    for i, m in enumerate(message):
        w[i] = C_Unsigned_Int(m)
    for i in range(16, 80):
        w[i] = (w[i-3] ^ w[i-8] ^ w[i-14] ^ w[i-16]).rotateL(1) 
    for i in range(80):
        a,b,c,d,e = (a.rotateL(5)+f(b,c,d,i)+e+w[i]), a, b.rotateL(30), c, d
    a,b,c,d,e = a+iv[0], b+iv[1], c+iv[2], d+iv[3], e+iv[4]
    return [a,b,c,d,e]

iv1 = [0x506b0178, 0xff6d1890, 0x202291fd, 0x3ade3871, 0xb2c665ea]
message1 = [0x9d443828, 0xa5ea3df0, 0x86eaa0fa, 0x7783a736, 
            0x3324484d, 0xaf702aaa, 0xa3dab679, 0xd8a69e2d, 
            0x543820ed, 0xa7fffb52, 0xd3ff493f, 0xc3ff551e,
            0xfbffd97f, 0x55feeef2, 0x085af312, 0x088688a9]

iv2 = [0x506b0178, 0xff6d1891, 0xa02291fd, 0x3ade3871, 0xb2c665ea]
message2 = [0x3f443838, 0x81ea3dec, 0xa0eaa0ee, 0x5183a72c,
            0x3324485d, 0xab702ab6, 0x6fdab66d, 0xd4a69e2f,
            0x943820fd, 0x13fffb4e, 0xefff493b, 0x7fff5504,
            0xdbffd96f, 0x71feeeee, 0xe45af306, 0x048688ab]

for i in sha_1(iv1, message1):
    print('{:8x}'.format(i.val))

for i in sha_1(iv2, message2):
    print('{:8x}'.format(i.val))


