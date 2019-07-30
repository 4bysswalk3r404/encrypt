#ifndef ENCLIB_H
#define ENCLIB_H

unsigned int size(char* ptr);

void encrypt(unsigned char* data, unsigned int bufferSize, unsigned int seed);

void decrypt(unsigned char* data, unsigned int bufferSize, unsigned int seed);

char* concatenate(char* base, char* sub);

char* concatPoi(char** elements, int num);

int strSize(char* string);

unsigned int intLen(int num);

unsigned int lastNum(int num);

char* toStr(int num);

#endif
