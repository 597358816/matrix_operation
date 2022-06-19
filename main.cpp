#include<stdio.h>
#include<stdlib.h>
#include"matrix.h"
#include"binary_matrix.h"
#define SIZE 8
#define DOMAIN 2
int main() {
	int** m = (int**)malloc(SIZE * sizeof(int*));
	int i;
	for (i = 0; i < SIZE; i++) {
		m[i] = (int*)malloc(SIZE * sizeof(int));
	}
	inputBinaryMatrix(m, SIZE, SIZE);
	printf("矩阵的秩是：%d\n", getBinaryRank(m, SIZE));
	printf("行列式为%d\n", getBinaryDeterminant(m, SIZE));
	printf("矩阵的逆：\n");
	outputBinaryMatrix(inverseBinaryMatrix(m, SIZE), SIZE, SIZE);
	return 0;
}