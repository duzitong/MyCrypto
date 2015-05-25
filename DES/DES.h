#pragma once

#include <stdio.h>

typedef unsigned char u8;
typedef unsigned int u32;

void rotateL(u8*, u8*, u8);
void getRoundKeys(u8*, u8*);
void roundFunction(u8*, u8*, u8*);
void encrypt(u8*, u8*, u8*);
void decrypt(u8*, u8*, u8*);
