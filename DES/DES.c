#include "DES.h"

// All table outputs are subtracted by 1 for c language starts index from 0

// Initial Permutation
static const u8 IP[64] = 
{
  57, 49, 41, 33, 25, 17,  9, 1,
  59, 51, 43, 35, 27, 19, 11, 3,
  61, 53, 45, 37, 29, 21, 13, 5,
  63, 55, 47, 39, 31, 23, 15, 7,
  56, 48, 40, 32, 24, 16,  8, 0,
  58, 50, 42, 34, 26, 18, 10, 2,
  60, 52, 44, 36, 28, 20, 12, 4,
  62, 54, 46, 38, 30, 22, 14, 6
};

// IP reverse
static const u8 IP_[64] = 
{
  39, 7, 47, 15, 55, 23, 63, 31,
  38, 6, 46, 14, 54, 22, 62, 30,
  37, 5, 45, 13, 53, 21, 61, 29,
  36, 4, 44, 12, 52, 20, 60, 28,
  35, 3, 43, 11, 51, 19, 59, 27,
  34, 2, 42, 10, 50, 18, 58, 26,
  33, 1, 41,  9, 49, 17, 57, 25,
  32, 0, 40,  8, 48, 16, 56, 24
};

// E bit-selection table
static const u8 E[48] = 
{
  31,  0,  1,  2,  3,  4,
   3,  4,  5,  6,  7,  8,
   7,  8,  9, 10, 11, 12,
  11, 12, 13, 14, 15, 16,
  15, 16, 17, 18, 19, 20,
  19, 20, 21, 22, 23, 24,
  23, 24, 25, 26, 27, 28,
  27, 28, 29, 30, 31, 0
};

// PC1
static const u8 PC1[56] = 
{
  56, 48, 40, 32, 24, 16,  8,
   0, 57, 49, 41, 33, 25, 17,
   9,  1, 58, 50, 42, 34, 26,
  18, 10,  2, 59, 51, 43, 35,
  62, 54, 46, 38, 30, 22, 14,
   6, 61, 53, 45, 37, 29, 21,
  13,  5, 60, 52, 44, 36, 28,
  20, 12,  4, 27, 19, 11,  3
};

// Key shift by round table
static const u8 move[16] = 
{
  1, 1, 2, 2, 2, 2, 2, 2,
  1, 2, 2, 2, 2, 2, 2, 1
};

// PC2
static const u8 PC2[48] = 
{
  13, 16, 10, 23,  0,  4,
   2, 27, 14,  5, 20,  9,
  22, 18, 11,  3, 25,  7,
  15,  6, 26, 19, 12,  1,
  40, 51, 30, 36, 46, 54,
  29, 39, 50, 44, 32, 47,
  43, 48, 38, 55, 33, 52,
  45, 41, 49, 35, 28, 31
};

// S Box
static const u8 SBox[8][64] = 
{
  {  /* S0 */
    14,  0,  4, 15, 13,  7,  1,  4,  2, 14, 15,  2, 11, 13,  8,  1,
     3, 10, 10,  6,  6, 12, 12, 11,  5,  9,  9,  5,  0,  3,  7,  8,
     4, 15,  1, 12, 14,  8,  8,  2, 13,  4,  6,  9,  2,  1, 11,  7,
    15,  5, 12, 11,  9,  3,  7, 14,  3, 10, 10,  0,  5,  6,  0, 13
  },
  {  /* S1 */
    15,  3,  1, 13,  8,  4, 14,  7,  6, 15, 11,  2,  3,  8,  4, 14,
     9, 12,  7,  0,  2,  1, 13, 10, 12,  6,  0,  9,  5, 11, 10,  5,
     0, 13, 14,  8,  7, 10, 11,  1, 10,  3,  4, 15, 13,  4,  1,  2,
     5, 11,  8,  6, 12,  7,  6, 12,  9,  0,  3,  5,  2, 14, 15,  9
  },
  {  /* S2 */
    10, 13,  0,  7,  9,  0, 14,  9,  6,  3,  3,  4, 15,  6,  5, 10,
     1,  2, 13,  8, 12,  5,  7, 14, 11, 12,  4, 11,  2, 15,  8,  1,
    13,  1,  6, 10,  4, 13,  9,  0,  8,  6, 15,  9,  3,  8,  0,  7,
    11,  4,  1, 15,  2, 14, 12,  3,  5, 11, 10,  5, 14,  2,  7, 12
  },
  {  /* S3 */
     7, 13, 13,  8, 14, 11,  3,  5,  0,  6,  6, 15,  9,  0, 10,  3,
     1,  4,  2,  7,  8,  2,  5, 12, 11,  1, 12, 10,  4, 14, 15,  9,
    10,  3,  6, 15,  9,  0,  0,  6, 12, 10, 11,  1,  7, 13, 13,  8,
    15,  9,  1,  4,  3,  5, 14, 11,  5, 12,  2,  7,  8,  2,  4, 14
  },
  {  /* S4 */
     2, 14, 12, 11,  4,  2,  1, 12,  7,  4, 10,  7, 11, 13,  6,  1,
     8,  5,  5,  0,  3, 15, 15, 10, 13,  3,  0,  9, 14,  8,  9,  6,
     4, 11,  2,  8,  1, 12, 11,  7, 10,  1, 13, 14,  7,  2,  8, 13,
    15,  6,  9, 15, 12,  0,  5,  9,  6, 10,  3,  4,  0,  5, 14,  3
  },
  {  /* S5 */
    12, 10,  1, 15, 10,  4, 15,  2,  9,  7,  2, 12,  6,  9,  8,  5,
     0,  6, 13,  1,  3, 13,  4, 14, 14,  0,  7, 11,  5,  3, 11,  8,
     9,  4, 14,  3, 15,  2,  5, 12,  2,  9,  8,  5, 12, 15,  3, 10,
     7, 11,  0, 14,  4,  1, 10,  7,  1,  6, 13,  0, 11,  8,  6, 13
  },
  {  /* S6 */
     4, 13, 11,  0,  2, 11, 14,  7, 15,  4,  0,  9,  8,  1, 13, 10,
     3, 14, 12,  3,  9,  5,  7, 12,  5,  2, 10, 15,  6,  8,  1,  6,
     1,  6,  4, 11, 11, 13, 13,  8, 12,  1,  3,  4,  7, 10, 14,  7,
    10,  9, 15,  5,  6,  0,  8, 15,  0, 14,  5,  2,  9,  3,  2, 12
  },
  {  /* S7 */
    13,  1,  2, 15,  8, 13,  4,  8,  6, 10, 15,  3, 11,  7,  1,  4,
    10, 12,  9,  5,  3,  6, 14, 11,  5,  0,  0, 14, 12,  9,  7,  2,
     7,  2, 11,  1,  4, 14,  1,  7,  9,  4, 12, 10, 14,  8,  2, 13,
     0, 15,  6, 12, 10,  9, 13,  0, 15,  3,  3,  5,  5,  6,  8, 11
  }
};

// P Box
static const u8 PBox[32] =
{
  15,  6, 19, 20, 28, 11, 27, 16,
   0, 14, 22, 25,  4, 17, 30,  9,
   1,  7, 23, 13, 31, 26,  2,  8,
  18, 12, 29,  5, 21, 10,  3, 24
};

// Macros
#define CLRBIT( STR, IDX ) ( (STR)[(IDX)/8] &= ~(0x01 << (7 - ((IDX)%8))) )

#define SETBIT( STR, IDX ) ( (STR)[(IDX)/8] |= (0x01 << (7 - ((IDX)%8))) )

#define GETBIT( STR, IDX ) (( ((STR)[(IDX)/8]) >> (7 - ((IDX)%8)) ) & 0x01)

void rotateL(u8 *left, u8 *right, u8 times)
{
  u8 i;
  for (i = 0; i < times; i++)
  {
    u8 carry;
    u8 carry_;
    // rotate left
    carry = (left[3] >> 7);
    carry_ = (left[2] >> 7);
    left[2] = (left[2] << 1) + carry;
    carry = (left[1] >> 7);
    left[1] = (left[1] << 1) + carry_;
    carry_ = (left[0] >> 7);
    left[0] = (left[0] << 1) + carry;
    left[3] = (left[3] << 1) + (carry_ << 4);
    // rotate right
    carry = (right[3] >> 7);
    carry_ = (right[2] >> 7);
    right[2] = (right[2] << 1) + carry;
    carry = (right[1] >> 7);
    right[1] = (right[1] << 1) + carry_;
    carry_ = (right[0] >> 7);
    right[0] = (right[0] << 1) + carry;
    right[3] = (right[3] << 1) + (carry_ << 4);
  }
}

void getRoundKeys(u8 *key, u8 *rkeys)
{
  u8 c[4], d[4];
  int i, j;
  // Initialize c, d
  for (i = 0; i < 4; i++)
  {
    c[i] = d[i] = 0;
  }
  // Use PC1
  for (i = 0; i < 28; i++)
  {
    if (GETBIT(key, PC1[i]))
      SETBIT(c, i);
    if (GETBIT(key, PC1[i+28]))
      SETBIT(d, i);
  }
  // Round function of key expansion
  for (i = 0; i < 16; i++)
  {
    rotateL(c, d, move[i]);
    // Initialize round keys
    for (j = 0; j < 6; j++)
      rkeys[6*i+j] = 0;   
    // Use PC2
    for (j = 0; j < 48; j++)
    {
      if (PC2[j] < 28)
      {
        if (GETBIT(c, PC2[j]))
          SETBIT(rkeys + (6*i), j);
      }
      else
      {
        if (GETBIT(d, PC2[j] - 28))
          SETBIT(rkeys + (6*i), j);
      }
    }
  }
}

void roundFunction(u8 *left, u8* rkey, u8 *right)
{
  u8 e[6], sin[8], sout[8], p[4];
  int i;
  // Initialize e
  for (i = 0; i < 6; i++)
    e[i] = 0;
  // E
  for (i = 0; i < 48; i++)
    if (GETBIT(right, E[i]))
      SETBIT(e, i);
  // XOR round key
  for (i = 0; i < 6; i++)
    e[i] ^= rkey[i];
  // S Box
  // Fit e into sin
  for (i = 0; i < 8; i++)
    sin[i] = 0;
  for (i = 0; i < 2; i++)
  {
    // 0 and 4
    sin[4*i] = (e[3*i] >> 2);
    // 1 and 3
    sin[4*i + 1] = ((e[3*i] & 0x03) << 4 ) | (e[3*i + 1] >> 4);
    // 2 and 5
    sin[4*i + 2] = ((e[3*i + 1] & 0x0f) << 2 ) | (e[3*i + 2] >> 6);
    // 3 and 6
    sin[4*i + 3] = (e[3*i + 2] & 0x3f);
  }
  // Substitute
  for (i = 0; i < 8; i++)
    sout[i] = SBox[i][sin[i]];
  // Fit sout into p
  for (i = 0; i < 4; i++)
    p[i] = (sout[2*i] << 4) | (sout[2*i + 1]);
  // P Box
  for (i = 0; i < 4; i++)
    right[i] = 0;
  for (i = 0; i < 32; i++)
    if (GETBIT(p, PBox[i]))
      SETBIT(right, i);
  for (i = 0; i < 4; i++)
    right[i] ^= left[i];
}

void encrypt(u8 *plain, u8* rkeys, u8 *cipher)
{
  int i, j;
  u8 l[4], r[4], tmp[4];
  // Initialize l, r
  for (i = 0; i < 4; i++)
  {
    l[i] = r[i] = 0;
  }
  // IP
  for (i = 0; i < 32; i++)
  {
    if (GETBIT(plain, IP[i]))
      SETBIT(l, i);
    if (GETBIT(plain, IP[i+32]))
      SETBIT(r, i);
  }
  // Round function
  for (i = 0; i < 16; i++)
  {
    for (j = 0; j < 4; j++)
      tmp[j] = r[j];
    roundFunction(l, rkeys+(i*6), r);
    for (j = 0; j < 4; j++)
      l[j] = tmp[j];
  }
  // Swap back in the last round
  // Do it in mind
  // IPR
  // Initialize cipher
  for (i = 0; i < 8; i++)
    cipher[i] = 0;
  for (i = 0; i < 64; i++)
  {
    if (IP_[i] < 32)
    {
      if (GETBIT(r, IP_[i]))
        SETBIT(cipher, i);
    }
    else
    {
      if (GETBIT(l, IP_[i] - 32))
        SETBIT(cipher, i);
    }
  }
}

void decrypt(u8 *cipher, u8 *rkeys, u8 *decrypted)
{
  u8 irkeys[96];
  int i,j;
  for (i = 0; i < 16; i++)
    for (j = 0; j < 6; j++)
      irkeys[(15-i)*6 + j] = rkeys[i*6 + j];
  encrypt(cipher, irkeys, decrypted);
}

int main()
{
  u32 iKey[2];
  u32 iPlain[2];
  u32 oCipher[2];
  u8 key[8];
  u8 plain[8];
  u8 cipher[8];
  u8 decrypted[8];
  u8 rkeys[96];
  int i, j;
  FILE *cFile;
  FILE *kFile;
  FILE *pFile;
  for (i = 0; i < 2; i++)
  {
      iKey[i] = iPlain[i] = oCipher[i] = 0;
  }
  kFile = fopen("key.txt", "r");
  for (i = 0; i < 2; i++)
  {
    fscanf(kFile, "%x", &iKey[i]);
  }
  fclose(kFile);
  pFile = fopen("plain.txt", "r");
  for (i = 0; i < 2; i++)
  {
    fscanf(pFile, "%x", &iPlain[i]);
  }
  fclose(pFile);
  
  // change u32 into u8 array
  for (i = 0; i < 8; i++)
  {
    key[i] = (iKey[i / 4] >> (((3-i) % 4) * 8));
    plain[i] = (iPlain[i / 4] >> (((3-i) % 4) * 8));
  }
  // key -> round keys
  getRoundKeys(key, rkeys);
  // Encrypt
  encrypt(plain, rkeys, cipher);
  // change u8 array into u32
  for (i = 0; i < 4; i++)
  {
    oCipher[0] |= (cipher[i] << (8* (3-i)));
    oCipher[1] |= (cipher[4+i] << (8* (3-i)));
  }
  // Output
  cFile = fopen("cipher.txt", "w+");
  for (i = 0; i < 2; i++)
    fprintf(cFile, "%08x ", oCipher[i]);
  fclose(cFile);
  decrypt(cipher, rkeys, decrypted);
  printf("plain:\t");
  for (i = 0; i < 4; i++)
    printf("%02x", decrypted[i]);
  printf(" ");
  for (i = 4; i < 8; i++)
    printf("%02x", decrypted[i]);
  printf("\n");
  return 0;
}
