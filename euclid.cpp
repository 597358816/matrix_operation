#include"euclid.h"
int gcd(int a, int b) {

	if (a < b) {
		a ^= b;
		b ^= a;
		a ^= b;
	}

	while (b != 0) {
		int temp = a;
		a = b;
		b = temp % b;
	}

	return a;
}

//扩展欧几里得求b在GF(m)下的乘法逆元 b和m只有互质才有逆元。
int euclid(int m, int b) {
	int A[4];
	A[1] = 1;
	A[2] = 0;
	A[3] = m;
	int B[4];
	B[1] = 0;
	B[2] = 1;
	B[3] = b;

	while (true) {
		if (0 == B[3]) {
			//printf("no inverse element\n");
			return 0;
		}
		else if (1 == B[3]) {
			//printf("inverse element: %d\n",B[2]);
			if (B[2] > 0) {
				return B[2];
			}
			else {
				return B[2] + m;
			}
		}

		int quotient = A[3] / B[3];

		int T[4];
		T[1] = A[1] - quotient * B[1];
		T[2] = A[2] - quotient * B[2];
		T[3] = A[3] - quotient * B[3];

		A[1] = B[1];
		A[2] = B[2];
		A[3] = B[3];
		B[1] = T[1];
		B[2] = T[2];
		B[3] = T[3];
	}
	return 0;
}