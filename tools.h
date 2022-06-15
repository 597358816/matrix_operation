#pragma once
#include<stdio.h>
#include<stdlib.h>
void swap(int* a, int* b);
int mod(int a, int b);
int** createMatrix(int length, int width);
void freeMatrix(int** m, int length);