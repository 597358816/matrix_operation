#pragma once
#include<stdio.h>
#include<stdlib.h>
#include"euclid.h"
#include"tools.h"
void outputBinaryMatrix(int** m, int length, int width);
void inputBinaryMatrix(int** m, int length, int width);
int** addBinaryMatrix(int** ma, int** mb, int length, int width);
int** minusBinaryMatrix(int** ma, int** mb, int length, int width);
int** multiplyBinaryMatrix(int** ma, int** mb, int a_length, int a_width, int b_length, int b_width);
int geBinaryDeterminant(int** matrix, int size);
int** inverseBinaryMatrix(int** matrix, int size);
int getBinaryRank(int** matrix, int size);
