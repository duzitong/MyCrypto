#ifndef CIPHER_H
#define CIPHER_H
#endif

/*********************************************************
rk - 44 int
rk[i] - 32 bit - 4 int
key - 128 bit - 16 char/byte
plain - 128 bit - 16 char/byte
cipher - 128 bit - 16 char/byte
**********************************************************/

#define LENGTH_ERROR	0
#define SUCCESS			1


int KeyExpansion(int *rk, const char *key);
int Encrypt(char* plain, char* cipher,int * rk, int length);
int Decrypt(char* cipher, char* plain,int * rk, int length);