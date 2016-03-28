def rotateL(m, b):
  """
  m: message to be rotated
  b: number of bits to be rotated
  return rotated message
  """
  assert m < (1<<32)
  return ((m << b) % (1 << 32)) | (m >> (32-b))

def rotateR(m, b):
  """
  m: message to be rotated
  b: number of bits to be rotated
  return rotated message
  """
  assert m < (1<<32)
  return ((m << (32-b)) % (1 << 32)) | (m >> b)

def f(b, c, d, i):
  """
  f function + k
  """
  if 0 <= i < 20:
    return ((b & c) ^ ((~b%(1<<32)) & d)) + 0x5a827999
  elif 20 <= i < 40:
    return (b ^ c ^ d) + 0x6ed6eba1
  elif 40 <= i < 60:
    return ((b & c) ^ (b & d) ^ (c & d)) + 0x8fabbcdc
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
  a, b, c, d, e = iv
  w = [0 for i in range(80)]
  for i, m in enumerate(message):
    w[i] = m
  for i in range(16, 80):
    w[i] = rotateL((w[i-3] ^ w[i-8] ^ w[i-14] ^ w[i-16]), 1) 
  for i in range(80):
    print(i, a)
    a,b,c,d,e = (rotateL(a,5)+f(b,c,d,i)+e+w[i]) % (1 << 32), a, rotateR(b,2), c, d
  a,b,c,d,e = (a+iv[0]) % (1 << 32), (b+iv[1]) % (1 << 32), (c+iv[2]) % (1 << 32),(d+iv[3]) % (1 << 32), (e+iv[4]) % (1 << 32),
  return [a,b,c,d,e]

iv1 = [0x506b0178, 0xff6d1890, 0x202291fd, 0x3ade3871, 0xb2c665ea]
message1 = [0x9d443828, 0xa5ea3df0, 0x86eaa0fa, 0x7783a736, 
            0x3324484d, 0xaf702aaa, 0xa3dab679, 0xd8a69e2d, 
            0x543820ed, 0xa7fffb52, 0xd3ff493f, 0xc3ff551e,
            0xfbffd97f, 0x55feeef2, 0x085af312, 0x088688a9
           ]

for i in sha_1(iv1, message1):
  print(hex(i))
