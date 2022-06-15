#include<stdio.h>
#include<stdlib.h>
#include"matrix.h"
int main() {
	int** m = (int**)malloc(3 * sizeof(int*));
	int i;
	for (i = 0; i < 3; i++) {
		m[i] = (int*)malloc(3 * sizeof(int));
	}
	int a = 2, b = 1;
	swap(&a, &b);
	inputMatrix(m, 3, 3);
	printf("矩阵的秩是：%d\n", getRank(m, 3, 31));
	printf("行列式为%d\n", getDeterminant(m, 3, 31));
	printf("矩阵的逆：\n");
	outputMatrix(inverseMatrix(m, 3, 31), 3, 3);
	return 0;
}