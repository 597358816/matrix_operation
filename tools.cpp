#include"tools.h"
void swap(int* a, int* b)
{
	int t = *a; *a = *b; *b = t;
}

//由于c语言不支持负数取模，这里手动编写
int mod(int a, int b) {
	a = a % b;
	if (a < 0) {
		a += b;
	}
	return a;
}


int** createMatrix(int length, int width) {
	int l, w;
	int** matrix = (int**)malloc(length * sizeof(int*));
	int i;
	for (i = 0; i < length; i++) {
		matrix[i] = (int*)malloc(width * sizeof(int));
	}
	return matrix;
}

void freeMatrix(int **m, int length) {
	//释放内存
	int i;
	for (i = 0; i < length; i++) {
		free(m[i]);
	}
	free(m);
}