#pragma once
#include<stdio.h>
#include<stdlib.h>
#include"euclid.h"
#include"tools.h"
void outputMatrix(int** m, int length, int width);
void inputMatrix(int** m, int length, int width);
int** addMatrix(int** ma, int** mb, int length, int width, int domain);
int** minusMatrix(int** ma, int** mb, int length, int width, int domain);
int** multiplyMatrix(int** ma, int** mb, int a_length, int a_width, int b_length, int b_width, int domain);
int getDeterminant(int** matrix, int size, int domain);
int** inverseMatrix(int** matrix, int size, int domain);
int getRank(int** matrix, int size, int domain);
