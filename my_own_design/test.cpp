#include <iostream>
#include "cipher.h"
using namespace std;

int main()
{
	int rk[44];
	char key[16] = {1,2,3,4,5,6,7,8};
	char plain[16] = {0xff,0}, cipher[16];
	KeyExpansion(rk, key);
	Encrypt(plain, cipher ,rk, 16);
	Decrypt(cipher, plain, rk, 16);
	for (int i = 0; i < 16; i++)
		for (int j = 7; j >= 0 ; j --)
			cout << ((cipher[i] >> j) & 1);
	cout << endl;
	for (int i = 0; i < 16; i++)
		for (int j = 7; j >= 0 ; j --)
			cout << ((plain[i] >> j) & 1);
	return 0;
}