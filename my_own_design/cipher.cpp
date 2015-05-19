#include "cipher.h"

static const int Te4[256] =
{
  0x63636363U, 0x7c7c7c7cU, 0x77777777U, 0x7b7b7b7bU,
  0xf2f2f2f2U, 0x6b6b6b6bU, 0x6f6f6f6fU, 0xc5c5c5c5U,
  0x30303030U, 0x01010101U, 0x67676767U, 0x2b2b2b2bU,
  0xfefefefeU, 0xd7d7d7d7U, 0xababababU, 0x76767676U,
  0xcacacacaU, 0x82828282U, 0xc9c9c9c9U, 0x7d7d7d7dU,
  0xfafafafaU, 0x59595959U, 0x47474747U, 0xf0f0f0f0U,
  0xadadadadU, 0xd4d4d4d4U, 0xa2a2a2a2U, 0xafafafafU,
  0x9c9c9c9cU, 0xa4a4a4a4U, 0x72727272U, 0xc0c0c0c0U,
  0xb7b7b7b7U, 0xfdfdfdfdU, 0x93939393U, 0x26262626U,
  0x36363636U, 0x3f3f3f3fU, 0xf7f7f7f7U, 0xccccccccU,
  0x34343434U, 0xa5a5a5a5U, 0xe5e5e5e5U, 0xf1f1f1f1U,
  0x71717171U, 0xd8d8d8d8U, 0x31313131U, 0x15151515U,
  0x04040404U, 0xc7c7c7c7U, 0x23232323U, 0xc3c3c3c3U,
  0x18181818U, 0x96969696U, 0x05050505U, 0x9a9a9a9aU,
  0x07070707U, 0x12121212U, 0x80808080U, 0xe2e2e2e2U,
  0xebebebebU, 0x27272727U, 0xb2b2b2b2U, 0x75757575U,
  0x09090909U, 0x83838383U, 0x2c2c2c2cU, 0x1a1a1a1aU,
  0x1b1b1b1bU, 0x6e6e6e6eU, 0x5a5a5a5aU, 0xa0a0a0a0U,
  0x52525252U, 0x3b3b3b3bU, 0xd6d6d6d6U, 0xb3b3b3b3U,
  0x29292929U, 0xe3e3e3e3U, 0x2f2f2f2fU, 0x84848484U,
  0x53535353U, 0xd1d1d1d1U, 0x00000000U, 0xededededU,
  0x20202020U, 0xfcfcfcfcU, 0xb1b1b1b1U, 0x5b5b5b5bU,
  0x6a6a6a6aU, 0xcbcbcbcbU, 0xbebebebeU, 0x39393939U,
  0x4a4a4a4aU, 0x4c4c4c4cU, 0x58585858U, 0xcfcfcfcfU,
  0xd0d0d0d0U, 0xefefefefU, 0xaaaaaaaaU, 0xfbfbfbfbU,
  0x43434343U, 0x4d4d4d4dU, 0x33333333U, 0x85858585U,
  0x45454545U, 0xf9f9f9f9U, 0x02020202U, 0x7f7f7f7fU,
  0x50505050U, 0x3c3c3c3cU, 0x9f9f9f9fU, 0xa8a8a8a8U,
  0x51515151U, 0xa3a3a3a3U, 0x40404040U, 0x8f8f8f8fU,
  0x92929292U, 0x9d9d9d9dU, 0x38383838U, 0xf5f5f5f5U,
  0xbcbcbcbcU, 0xb6b6b6b6U, 0xdadadadaU, 0x21212121U,
  0x10101010U, 0xffffffffU, 0xf3f3f3f3U, 0xd2d2d2d2U,
  0xcdcdcdcdU, 0x0c0c0c0cU, 0x13131313U, 0xececececU,
  0x5f5f5f5fU, 0x97979797U, 0x44444444U, 0x17171717U,
  0xc4c4c4c4U, 0xa7a7a7a7U, 0x7e7e7e7eU, 0x3d3d3d3dU,
  0x64646464U, 0x5d5d5d5dU, 0x19191919U, 0x73737373U,
  0x60606060U, 0x81818181U, 0x4f4f4f4fU, 0xdcdcdcdcU,
  0x22222222U, 0x2a2a2a2aU, 0x90909090U, 0x88888888U,
  0x46464646U, 0xeeeeeeeeU, 0xb8b8b8b8U, 0x14141414U,
  0xdedededeU, 0x5e5e5e5eU, 0x0b0b0b0bU, 0xdbdbdbdbU,
  0xe0e0e0e0U, 0x32323232U, 0x3a3a3a3aU, 0x0a0a0a0aU,
  0x49494949U, 0x06060606U, 0x24242424U, 0x5c5c5c5cU,
  0xc2c2c2c2U, 0xd3d3d3d3U, 0xacacacacU, 0x62626262U,
  0x91919191U, 0x95959595U, 0xe4e4e4e4U, 0x79797979U,
  0xe7e7e7e7U, 0xc8c8c8c8U, 0x37373737U, 0x6d6d6d6dU,
  0x8d8d8d8dU, 0xd5d5d5d5U, 0x4e4e4e4eU, 0xa9a9a9a9U,
  0x6c6c6c6cU, 0x56565656U, 0xf4f4f4f4U, 0xeaeaeaeaU,
  0x65656565U, 0x7a7a7a7aU, 0xaeaeaeaeU, 0x08080808U,
  0xbabababaU, 0x78787878U, 0x25252525U, 0x2e2e2e2eU,
  0x1c1c1c1cU, 0xa6a6a6a6U, 0xb4b4b4b4U, 0xc6c6c6c6U,
  0xe8e8e8e8U, 0xddddddddU, 0x74747474U, 0x1f1f1f1fU,
  0x4b4b4b4bU, 0xbdbdbdbdU, 0x8b8b8b8bU, 0x8a8a8a8aU,
  0x70707070U, 0x3e3e3e3eU, 0xb5b5b5b5U, 0x66666666U,
  0x48484848U, 0x03030303U, 0xf6f6f6f6U, 0x0e0e0e0eU,
  0x61616161U, 0x35353535U, 0x57575757U, 0xb9b9b9b9U,
  0x86868686U, 0xc1c1c1c1U, 0x1d1d1d1dU, 0x9e9e9e9eU,
  0xe1e1e1e1U, 0xf8f8f8f8U, 0x98989898U, 0x11111111U,
  0x69696969U, 0xd9d9d9d9U, 0x8e8e8e8eU, 0x94949494U,
  0x9b9b9b9bU, 0x1e1e1e1eU, 0x87878787U, 0xe9e9e9e9U,
  0xcecececeU, 0x55555555U, 0x28282828U, 0xdfdfdfdfU,
  0x8c8c8c8cU, 0xa1a1a1a1U, 0x89898989U, 0x0d0d0d0dU,
  0xbfbfbfbfU, 0xe6e6e6e6U, 0x42424242U, 0x68686868U,
  0x41414141U, 0x99999999U, 0x2d2d2d2dU, 0x0f0f0f0fU,
  0xb0b0b0b0U, 0x54545454U, 0xbbbbbbbbU, 0x16161616U,
};

static const int rcon[] =
{
  0x01000000, 0x02000000, 0x04000000, 0x08000000,
  0x10000000, 0x20000000, 0x40000000, 0x80000000,
  0x1B000000, 0x36000000,
  /* for 128-bit blocks, Rijndael never uses more than 10 rcon values */
};

static const unsigned char sbox[] = 
{51, 179, 187, 59, 115, 243, 251, 123, 119, 247, 255, 127, 55, 183, 191, 63, 49, 177, 185, 57, 113, 241, 249, 121, 117, 245, 253, 125, 53, 181, 189, 61, 0, 128, 136, 8, 64, 192, 200, 72, 68, 196, 204, 76, 4, 132, 140, 12, 19, 147, 155, 27, 83, 211, 219, 91, 87, 215, 223, 95, 23, 151, 159, 31, 48, 176, 184, 56, 112, 240, 248, 120, 116, 244, 252, 124, 52, 180, 188, 60, 16, 144, 152, 24, 80, 208, 216, 88, 84, 212, 220, 92, 20, 148, 156, 28, 18, 146, 154, 26, 82, 210, 218, 90, 86, 214, 222, 94, 22, 150, 158, 30, 33, 161, 169, 41, 97, 225, 233, 105, 101, 229, 237, 109, 37, 165, 173, 45, 17, 145, 153, 25, 81, 209, 217, 89, 85, 213, 221, 93, 21, 149, 157, 29, 3, 131, 139, 11, 67, 195, 203, 75, 71, 199, 207, 79, 7, 135, 143, 15, 1, 129, 137, 9, 65, 193, 201, 73, 69, 197, 205, 77, 5, 133, 141, 13, 2, 130, 138, 10, 66, 194, 202, 74, 70, 198, 206, 78, 6, 134, 142, 14, 35, 163, 171, 43, 99, 227, 235, 107, 103, 231, 239, 111, 39, 167, 175, 47, 50, 178, 186, 58, 114, 242, 250, 122, 118, 246, 254, 126, 54, 182, 190, 62, 32, 160, 168, 40, 96, 224, 232, 104, 100, 228, 236, 108, 36, 164, 172, 44, 34, 162, 170, 42, 102, 230, 238, 110, 98, 226, 234, 106, 38, 174, 166, 46};

static const unsigned char isbox[] = 
{32, 160, 176, 144, 44, 172, 188, 156, 35, 163, 179, 147, 47, 175, 191, 159, 80, 128, 96, 48, 92, 140, 108, 60, 83, 131, 99, 51, 95, 143, 111, 63, 224, 112, 240, 192, 236, 124, 252, 204, 227, 115, 243, 195, 239, 127, 255, 207, 64, 16, 208, 0, 76, 28, 220, 12, 67, 19, 211, 3, 79, 31, 223, 15, 36, 164, 180, 148, 40, 168, 184, 152, 39, 167, 183, 151, 43, 171, 187, 155, 84, 132, 100, 52, 88, 136, 104, 56, 87, 135, 103, 55, 91, 139, 107, 59, 228, 116, 248, 196, 232, 120, 244, 200, 231, 119, 251, 199, 235, 123, 247, 203, 68, 20, 212, 4, 72, 24, 216, 8, 71, 23, 215, 7, 75, 27, 219, 11, 33, 161, 177, 145, 45, 173, 189, 157, 34, 162, 178, 146, 46, 174, 190, 158, 81, 129, 97, 49, 93, 141, 109, 61, 82, 130, 98, 50, 94, 142, 110, 62, 225, 113, 241, 193, 237, 125, 254, 205, 226, 114, 242, 194, 238, 126, 253, 206, 65, 17, 209, 1, 77, 29, 221, 13, 66, 18, 210, 2, 78, 30, 222, 14, 37, 165, 181, 149, 41, 169, 185, 153, 38, 166, 182, 150, 42, 170, 186, 154, 85, 133, 101, 53, 89, 137, 105, 57, 86, 134, 102, 54, 90, 138, 106, 58, 229, 117, 249, 197, 233, 121, 245, 201, 230, 118, 250, 198, 234, 122, 246, 202, 69, 21, 213, 5, 73, 25, 217, 9, 70, 22, 214, 6, 74, 26, 218, 10};

#define GETU32(plaintext) (((int)(plaintext)[0] << 24) ^ \
                    ((int)(plaintext)[1] << 16) ^ \
                    ((int)(plaintext)[2] <<  8) ^ \
                    ((int)(plaintext)[3]))

#define PUTU32(ciphertext, st) { (ciphertext)[0] = (char)((st) >> 24); \
                         (ciphertext)[1] = (char)((st) >> 16); \
                         (ciphertext)[2] = (char)((st) >>  8); \
                         (ciphertext)[3] = (char)(st); }

#define shift(in, from, to) (((in >> from) & 1 ) << to)

int KeyExpansion(int *rk, const char *key)
{
	int i = 0;
	int temp;

	rk[0] = GETU32(key     );
	rk[1] = GETU32(key +  4);
	rk[2] = GETU32(key +  8);
	rk[3] = GETU32(key + 12);
    for (;;)
    {
		temp  = rk[3];
		rk[4] = rk[0] ^
			(Te4[(temp >> 16) & 0xff] & 0xff000000) ^
			(Te4[(temp >>  8) & 0xff] & 0x00ff0000) ^
			(Te4[(temp      ) & 0xff] & 0x0000ff00) ^
			(Te4[(temp >> 24)       ] & 0x000000ff) ^
			rcon[i];
		rk[5] = rk[1] ^ rk[4];
		rk[6] = rk[2] ^ rk[5];
		rk[7] = rk[3] ^ rk[6];
		if (++i == 10)
			return 10;
		rk += 4;
    }
}

int Encrypt(char * plain, char * cipher, int *rk, int length)
{
	if (length != 16)
		return LENGTH_ERROR;
	unsigned char s[16], t[16];
	// Add round key
	for (int i = 0; i < length; i += 4)
		PUTU32(s+i, rk[i/4]);
	for (int i = 0; i < length; i ++)
		t[i] = plain[i] ^ s[i];
	// Round function
	for (int r = 0; r < 10; r++)
	{
		// Substitution
		for (int i = 0; i < length; i++)
			s[i] = sbox[t[i]];
		
		// Shift-bit
		for (int i = 0; i < length; i += 4)
		{
			for (int j = 0; j < 4; j++)
			{
				t[i+j]	= shift(s[i],   (7 - j), 7) + shift(s[i],   (3 - j), 6) 
						+ shift(s[i+1], (7 - j), 5) + shift(s[i+1], (3 - j), 4)
						+ shift(s[i+2], (7 - j), 3) + shift(s[i+2], (3 - j), 2)
						+ shift(s[i+3], (7 - j), 1) + shift(s[i+3], (3 - j), 0);
			}
		}
		
		// ARIA permutation
		s[0]	=	t[3]	^	t[4]	^	t[6]	^	t[8]	^	t[9]	^	t[13]	^	t[14];
		s[1]	=	t[2]	^	t[5]	^	t[7]	^	t[8]	^	t[9]	^	t[12]	^	t[15];
		s[2]	=	t[1]	^	t[4]	^	t[6]	^	t[10]	^	t[11]	^	t[12]	^	t[15];
		s[3]	=	t[0]	^	t[5]	^	t[7]	^	t[10]	^	t[11]	^	t[13]	^	t[14];
		s[4]	=	t[0]	^	t[2]	^	t[5]	^	t[8]	^	t[11]	^	t[14]	^	t[15];
		s[5]	=	t[1]	^	t[3]	^	t[4]	^	t[9]	^	t[10]	^	t[14]	^	t[15];
		s[6]	=	t[0]	^	t[2]	^	t[7]	^	t[9]	^	t[10]	^	t[12]	^	t[13];
		s[7]	=	t[1]	^	t[3]	^	t[6]	^	t[8]	^	t[11]	^	t[12]	^	t[13];
		s[8]	=	t[0]	^	t[1]	^	t[4]	^	t[7]	^	t[10]	^	t[13]	^	t[15];
		s[9]	=	t[0]	^	t[1]	^	t[5]	^	t[6]	^	t[11]	^	t[12]	^	t[14];
		s[10]	=	t[2]	^	t[3]	^	t[5]	^	t[6]	^	t[8]	^	t[13]	^	t[15];
		s[11]	=	t[2]	^	t[3]	^	t[4]	^	t[7]	^	t[9]	^	t[12]	^	t[14];
		s[12]	=	t[1]	^	t[2]	^	t[6]	^	t[7]	^	t[9]	^	t[11]	^	t[12];
		s[13]	=	t[0]	^	t[3]	^	t[6]	^	t[7]	^	t[8]	^	t[10]	^	t[13];
		s[14]	=	t[0]	^	t[3]	^	t[4]	^	t[5]	^	t[9]	^	t[11]	^	t[14];
		s[15]	=	t[1]	^	t[2]	^	t[4]	^	t[5]	^	t[8]	^	t[10]	^	t[15];
		
		// Add round key
		for (int i = 0; i < length; i += 4)
			PUTU32(t+i, rk[i/4 + 4 * r + 4]);
		for (int i = 0; i < length; i ++)
			t[i] = t[i] ^ s[i];
	}
	for (int i = 0; i < length; i++)
		cipher[i] = t[i];
	return SUCCESS;
}

int Decrypt(char * cipher, char * plain, int *rk, int length)
{
	if (length != 16)
		return LENGTH_ERROR;
	unsigned char s[16], t[16];
	// Add round key
	for (int i = 0; i < length; i += 4)
		PUTU32(s+i, rk[i/4 + 40]);
	for (int i = 0; i < length; i ++)
		t[i] = cipher[i] ^ s[i];
	// Round function
	for (int r = 0; r < 10; r++)
	{
		// ARIA permutation
		s[0]	=	t[3]	^	t[4]	^	t[6]	^	t[8]	^	t[9]	^	t[13]	^	t[14];
		s[1]	=	t[2]	^	t[5]	^	t[7]	^	t[8]	^	t[9]	^	t[12]	^	t[15];
		s[2]	=	t[1]	^	t[4]	^	t[6]	^	t[10]	^	t[11]	^	t[12]	^	t[15];
		s[3]	=	t[0]	^	t[5]	^	t[7]	^	t[10]	^	t[11]	^	t[13]	^	t[14];
		s[4]	=	t[0]	^	t[2]	^	t[5]	^	t[8]	^	t[11]	^	t[14]	^	t[15];
		s[5]	=	t[1]	^	t[3]	^	t[4]	^	t[9]	^	t[10]	^	t[14]	^	t[15];
		s[6]	=	t[0]	^	t[2]	^	t[7]	^	t[9]	^	t[10]	^	t[12]	^	t[13];
		s[7]	=	t[1]	^	t[3]	^	t[6]	^	t[8]	^	t[11]	^	t[12]	^	t[13];
		s[8]	=	t[0]	^	t[1]	^	t[4]	^	t[7]	^	t[10]	^	t[13]	^	t[15];
		s[9]	=	t[0]	^	t[1]	^	t[5]	^	t[6]	^	t[11]	^	t[12]	^	t[14];
		s[10]	=	t[2]	^	t[3]	^	t[5]	^	t[6]	^	t[8]	^	t[13]	^	t[15];
		s[11]	=	t[2]	^	t[3]	^	t[4]	^	t[7]	^	t[9]	^	t[12]	^	t[14];
		s[12]	=	t[1]	^	t[2]	^	t[6]	^	t[7]	^	t[9]	^	t[11]	^	t[12];
		s[13]	=	t[0]	^	t[3]	^	t[6]	^	t[7]	^	t[8]	^	t[10]	^	t[13];
		s[14]	=	t[0]	^	t[3]	^	t[4]	^	t[5]	^	t[9]	^	t[11]	^	t[14];
		s[15]	=	t[1]	^	t[2]	^	t[4]	^	t[5]	^	t[8]	^	t[10]	^	t[15];
		
		// Shift-bit
		for (int i = 0; i < length; i += 4)
		{
			for (int j = 0; j < 4; j++)
			{
				t[i+j]	= shift(s[i],	(7- 2 * j), 7) + shift(s[i],   (6 - 2 * j), 3) 
						+ shift(s[i+1],	(7- 2 * j), 6) + shift(s[i+1], (6 - 2 * j), 2)
						+ shift(s[i+2], (7- 2 * j), 5) + shift(s[i+2], (6 - 2 * j), 1)
						+ shift(s[i+3], (7- 2 * j), 4) + shift(s[i+3], (6 - 2 * j), 0);
			}
		}

		// Substitution
		for (int i = 0; i < length; i++)
			s[i] = isbox[t[i]];
		
		// Add round key
		for (int i = 0; i < length; i += 4)
			PUTU32(t+i, rk[i/4 + 36 -  4 * r]);
		for (int i = 0; i < length; i ++)
			t[i] = t[i] ^ s[i];
	}
	for (int i = 0; i < length; i++)
		plain[i] = t[i];
	return SUCCESS;
}