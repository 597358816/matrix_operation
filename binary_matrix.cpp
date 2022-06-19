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

int getBinaryDeterminant(int** matrix, int size) {
	//把内容赋值给新矩阵,对新矩阵进行操作，不破坏原有矩阵
	int i, l, w;
	int** m = createMatrix(size, size);
	for (l = 0; l < size; l++) {
		for (w = 0; w < size; w++) {
			m[l][w] = matrix[l][w];
		}
	}
	int row, another_row;
	int answer = 1;
	for (row = 0; row < size; row++) {
		//以行为基础
		if (m[row][row] == 0) {
			//如果对角线上的元素为0
			for (another_row = row + 1; another_row < size; another_row++) {
				//找不为0的那一行进行交换
				if (m[another_row][row] != 0) {
					break;
				}
			}
			if (another_row == size) {
				//找不到则行列式结果为0
				return 0;
			}
			else {
				//找到后整行进行交换
				for (i = row; i < size; i++) {
					swap(&m[row][i], &m[another_row][i]);
				}
			}
		}
		for (another_row = row + 1; another_row < size; another_row++) {
			//把该行下方的所有行化阶梯型
			if (m[another_row][row] != 0) {
				for (i = row; i < size; i++) {
					m[another_row][i] = m[another_row][i] ^ m[row][i];
				}
			}
		}
	}
	//释放内存
	freeMatrix(m, size);
	return 1;
}
int** inverseBinaryMatrix(int** matrix, int size){
	int i, l, w;
	//把内容赋值给新矩阵,对新矩阵进行操作，不破坏原有矩阵
	int** origin = createMatrix(size, size);
	int** answer = createMatrix(size, size);

	//辅助矩阵的值设为e
	for (l = 0; l < size; l++) {
		for (w = 0; w < size; w++) {
			origin[l][w] = matrix[l][w];
			if (l == w) {
				answer[l][w] = 1;
			}
			else {
				answer[l][w] = 0;
			}
		}
	}

	int row, another_row;
	for (row = 0; row < size; row++) {
		//以行为基础
		if (origin[row][row] == 0) {
			//如果对角线上的元素为0
			for (another_row = row + 1; another_row < size; another_row++) {
				//找不为0的那一行进行交换
				if (origin[another_row][row] != 0) {
					break;
				}
			}
			if (another_row == size) {
				//找不到则不可逆，返回空
				return nullptr;
			}
			else {
				//找到后整行进行交换
				for (i = row; i < size; i++) {
					swap(&origin[row][i], &origin[another_row][i]);
					swap(&answer[row][i], &answer[another_row][i]);
				}
			}
		}
		for (another_row = row + 1; another_row < size; another_row++) {
			//把该行下方的所有行化阶梯型
			if (origin[another_row][row] != 0) {
				for (i = 0; i < size; i++) {
					origin[another_row][i] = origin[another_row][i] ^ origin[row][i];
					answer[another_row][i] = answer[another_row][i] ^ answer[row][i];
				}
			}
		}
	}
	//将上方化为阶梯型
	for (row = size - 1; row >= 0; row--) {
		for (another_row = row - 1; another_row >= 0; another_row--) {
			if (origin[another_row][row] != 0) {
				for (i = size - 1; i >= 0; i--) {
					origin[another_row][i] = origin[another_row][i] ^ origin[row][i];
					answer[another_row][i] = answer[another_row][i] ^ answer[row][i];
				}
			}
		}
	}

	//释放内存
	freeMatrix(origin, size);
	return answer;
}
int getBinaryRank(int** matrix, int size) {
	int i, l, w;
	//把内容赋值给新矩阵，对新矩阵进行操作，不破坏原有矩阵
	int** m = createMatrix(size, size);
	for (l = 0; l < size; l++) {
		for (w = 0; w < size; w++) {
			m[l][w] = matrix[l][w];
		}
	}
	int row, line, another_row;
	int rank = size;
	for (row = 0, line = 0; row < size, line < size; row++, line++) {
		//以行为基础
		if (m[row][line] == 0) {
			//如果阶梯元素为0
			for (another_row = row + 1; another_row < size; another_row++) {
				//找不为0的那一行进行交换
				if (m[another_row][line] != 0) {
					break;
				}
			}
			if (another_row != size) {
				//找到后进行交换
				for (i = line; i < size; i++) {
					swap(&m[row][i], &m[another_row][i]);
				}
			}
			else {
				//否则表明有一层为0，秩减一，行不变
				row--;
				rank--;
				continue;
			}
		}
		for (another_row = row + 1; another_row < size; another_row++) {
			//把该行下方的所有行化阶梯型
			if (m[another_row][line] != 0) {
				for (i = row; i < size; i++) {
					m[another_row][i] = m[another_row][i] ^ m[row][i];
				}
			}
		}
	}
	freeMatrix(m, size);
	return rank;
}
