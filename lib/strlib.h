#ifndef STRLIB_H
#define STRLIB_H

int StrSize(char* buffer);

void Input(char* buffer);

void ConcatStr(char* buffer, char* sub);

int SameStr(char* main, char* sub, int num);

void SetStr(char* from, char* to);

int intLen(int num);

int lastNum(int num);

char* ToStr(int num);

void encrypt(unsigned char* data, unsigned int bufferSize, unsigned int seed);

void decrypt(unsigned char* data, unsigned int bufferSize, unsigned int seed);

#endif
