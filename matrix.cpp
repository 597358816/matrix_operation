#include"matrix.h"

//矩阵输出
void outputMatrix(int** m, int length, int width) {
	if (!m) {
		printf("matrix is null");
		return;
	}
	int i, j;
	for (i = 0; i < length; i++) {
		for (j = 0; j < width; j++) {
			printf("%d ",m[i][j]);
		}
		printf("\n");
	}
}

//矩阵输入
void inputMatrix(int** m, int length, int width) {
	int i, j;
	for (i = 0; i < length; i++) {
		for (j = 0; j < width; j++) {
			scanf_s("%d", &m[i][j]);
		}
	}
}

//矩阵加法
int** addMatrix(int** ma, int** mb, int length, int width, int domain) {
	int l, w;
	int** matrix = createMatrix(length, width);
	for (l = 0; l < length; l++) {
		for (w = 0; w < width; w++) {
			matrix[l][w] = mod((ma[l][w] + mb[l][w]), domain);
		}
	}
	return matrix;
}

//矩阵减法
int** minusMatrix(int** ma, int** mb, int length, int width, int domain) {
	int l, w;
	int** matrix = createMatrix(length, width);
	for (l = 0; l < length; l++) {
		for (w = 0; w < width; w++) {
			matrix[l][w] = mod((ma[l][w] - mb[l][w]), domain);
		}
	}
	return matrix;
}


//矩阵乘法（未测试）
int** multiplyMatrix(int** ma, int** mb, int a_length, int a_width, int b_length, int b_width, int domain) {
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
					sum += ma[l][i] * mb[i][w];
				}
				matrix[l][w] = mod(sum, domain);
			}
		}
		return matrix;
	}
}

//求行列式
int getDeterminant(int** matrix, int size, int domain) {
	//把内容赋值给新矩阵,对新矩阵进行操作，不破坏原有矩阵
	int i,l,w;
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
			if (another_row == size){
				//找不到则行列式结果为0
				return 0;
			}
			else {
				//找到后整行进行交换
				for (i = row; i < size; i++) {
					swap(&m[row][i], &m[another_row][i]);
				}
				//行列式两行交换，值取相反数
				answer = domain - answer;
			}
		}
		//记录对角线上的元素
		int tmp = m[row][row];
		answer = mod(answer * tmp, domain);
		for (i = 0; i < size; i++) {
			//提取因数，把对角线上的元素化为1
			m[row][i] = mod(m[row][i] * euclid(domain, tmp), domain);
		}
		for (another_row = row + 1; another_row < size; another_row++) {
			//把该行下方的所有行化阶梯型
			int times = m[another_row][row];
			for (i = row; i < size; i++) {
				m[another_row][i] = mod(m[another_row][i] - times * m[row][i], domain);
			}
		}
	}
	//释放内存
	freeMatrix(m, size);
	return answer;
}

//矩阵求逆
int** inverseMatrix(int** matrix, int size, int domain) {
	int i, l, w;
	//把内容赋值给新矩阵,对新矩阵进行操作，不破坏原有矩阵
	int** origin = createMatrix(size, size);
	int	**answer = createMatrix(size, size);

	//辅助矩阵的值设为e
	for (l = 0; l < size; l++) {
		for (w = 0; w < size; w++) {
			origin[l][w] = matrix[l][w];
			if (l == w) {
				answer[l][w] = 1;
			}
			else{
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
		//记录对角线上的元素
		int tmp = origin[row][row];
		for (i = 0; i < size; i++) {
			//提取因数，把对角线上的元素化为1
			origin[row][i] = mod(origin[row][i] * euclid(domain, tmp), domain);
			answer[row][i] = mod(answer[row][i] * euclid(domain, tmp), domain);
		}
		for (another_row = row + 1; another_row < size; another_row++) {
			//把该行下方的所有行化阶梯型
			int times = origin[another_row][row];
			for (i = 0; i < size; i++) {
				origin[another_row][i] = mod(origin[another_row][i] - times * origin[row][i], domain);
				answer[another_row][i] = mod(answer[another_row][i] - times * answer[row][i], domain);
			}
		}
		
	}
	for (row = size - 1; row >= 0; row--) {
		for (another_row = row - 1; another_row >=0; another_row--) {
			//把该行上方的所有行对角化
			int times = origin[another_row][row];
			for (i = size - 1; i >= 0; i--) {
				origin[another_row][i] = mod(origin[another_row][i] - times * origin[row][i], domain);
				answer[another_row][i] = mod(answer[another_row][i] - times * answer[row][i], domain);
			}
		}
	}
	
	//释放内存
	freeMatrix(origin, size);
	return answer;
}






int getRank(int** matrix, int size, int domain) {
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
			int times = m[another_row][row];
			for (i = line; i < size; i++) {
				m[another_row][i] = mod(m[another_row][i] - times * m[row][i] * euclid(domain, m[row][line]), domain);
			}
		}
	}
	freeMatrix(m, size);
	return rank;
}
