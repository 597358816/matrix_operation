#include"binary_matrix.h"


void outputBinaryMatrix(int** m, int length, int width) {
	if (!m) {
		printf("matrix is null");
		return;
	}
	int i, j;
	for (i = 0; i < length; i++) {
		for (j = 0; j < width; j++) {
			printf("%d ", m[i][j]);
		}
		printf("\n");
	}
}

void inputBinaryMatrix(int** m, int length, int width) {
	int i, j;
	for (i = 0; i < length; i++) {
		for (j = 0; j < width; j++) {
			scanf_s("%d", &m[i][j]);
			//超过2的话取模
			m[i][j] = mod(m[i][j], 2);
		}
	}
}

int** addBinaryMatrix(int** ma, int** mb, int length, int width) {
	int l, w;
	int** matrix = createMatrix(length, width);
	for (l = 0; l < length; l++) {
		for (w = 0; w < width; w++) {
			matrix[l][w] = ma[l][w] ^ mb[l][w];
		}
	}
	return matrix;
}

int** minusBinaryMatrix(int** ma, int** mb, int length, int width) {
	int l, w;
	int** matrix = createMatrix(length, width);
	for (l = 0; l < length; l++) {
		for (w = 0; w < width; w++) {
			matrix[l][w] = ma[l][w] ^ mb[l][w];
		}
	}
	return matrix;
}

int** multiplyBinaryMatrix(int** ma, int** mb, int a_length, int a_width, int b_length, int b_width) {
	if (a_width != b_length) {
		return nullptr;
	}
	else {
		int l, w, i;
		int** matrix = createMatrix(a_length, b_width);
		for (l = 0; l < a_length; l++) {
			for (w = 0; w < b_width; w++) {
				int sum = 0;
				for (i = 0; i < a_width; i++) {
					sum = ma[l][i] & mb[i][w] ^ sum;
				}
				matrix[l][w] = sum;
			}
		}
		return matrix;
	}
}

int geBinaryDeterminant(int** matrix, int size);
int** inverseBinaryMatrix(int** matrix, int size);
int getBinaryRank(int** matrix, int size);