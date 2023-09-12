#include "MT.h"

#include <assert.h>
#include <cmath>
#include <math.h>
#include "3d/PrimitiveDrawer.h"

PrimitiveDrawer* primitiveDrawer = nullptr;

float Clamp(float number, float min, float max) {
	if (min > number) {
		return min;
	} else if (max < number) {
		return max;
	} else {
		return number;
	}
}

int GetRandom(int min, int max) {
	static int flag;

	if (flag == 0) {
		srand((int)time(NULL));
		flag = 1;
	}

	return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}

// float GetRandom(float min, float max) {
//	static float flag;
//
//	if (flag == 0) {
//		srand((float)time(NULL));
//		flag = 1;
//	}
//
//	return min + (float)(rand() * (max - min + 1.0f) / (1.0f + RAND_MAX));
// }

Vector3 Add(const Vector3& v1, const Vector3& v2) {
	Vector3 num = {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
	return num;
}

Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 num = {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
	return num;
}

Vector3 Multiply(float scalar, const Vector3& v) {
	Vector3 num = {scalar * v.x, scalar * v.y, scalar * v.z};
	return num;
}

float Dot(const Vector3& v1, const Vector3& v2) {
	float num = {v1.x * v2.x + v1.y * v2.y + v1.z * v2.z};
	return num;
}

float Length(const Vector3& v) {
	float num = {sqrtf(v.x * v.x + v.y * v.y + v.z * v.z)};
	return num;
}

Vector3 Normalize(const Vector3& v) {
	Vector3 num = {v.x / Length(v), v.y / Length(v), v.z / Length(v)};
	return num;
}

// void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
//	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
//	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
//	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
//	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
// }

Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 mat = {m1.m[0][0] + m2.m[0][0], m1.m[0][1] + m2.m[1][1], m1.m[0][2] + m2.m[0][2],
	                 m1.m[0][3] + m2.m[0][3], m1.m[1][0] + m2.m[1][0], m1.m[1][1] + m2.m[1][1],
	                 m1.m[1][2] + m2.m[1][2], m1.m[1][3] + m2.m[1][3], m1.m[2][0] + m2.m[2][0],
	                 m1.m[2][1] + m2.m[2][1], m1.m[2][2] + m2.m[2][2], m1.m[2][3] + m2.m[2][3],
	                 m1.m[3][0] + m2.m[3][0], m1.m[3][1] + m2.m[3][1], m1.m[3][2] + m2.m[3][2],
	                 m1.m[3][3] + m2.m[3][3]};
	return mat;
}

Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 mat = {m1.m[0][0] - m2.m[0][0], m1.m[0][1] - m2.m[1][1], m1.m[0][2] - m2.m[0][2],
	                 m1.m[0][3] - m2.m[0][3], m1.m[1][0] - m2.m[1][0], m1.m[1][1] - m2.m[1][1],
	                 m1.m[1][2] - m2.m[1][2], m1.m[1][3] - m2.m[1][3], m1.m[2][0] - m2.m[2][0],
	                 m1.m[2][1] - m2.m[2][1], m1.m[2][2] - m2.m[2][2], m1.m[2][3] - m2.m[2][3],
	                 m1.m[3][0] - m2.m[3][0], m1.m[3][1] - m2.m[3][1], m1.m[3][2] - m2.m[3][2],
	                 m1.m[3][3] - m2.m[3][3]};
	return mat;
}

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 resultMatrix = {};

	resultMatrix.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] +
	                       m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0];
	resultMatrix.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] +
	                       m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1];
	resultMatrix.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] +
	                       m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2];
	resultMatrix.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] +
	                       m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3];

	resultMatrix.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] +
	                       m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0];
	resultMatrix.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] +
	                       m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1];
	resultMatrix.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] +
	                       m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2];
	resultMatrix.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] +
	                       m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3];

	resultMatrix.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] +
	                       m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0];
	resultMatrix.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] +
	                       m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1];
	resultMatrix.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] +
	                       m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2];
	resultMatrix.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] +
	                       m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3];

	resultMatrix.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] +
	                       m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0];
	resultMatrix.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] +
	                       m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1];
	resultMatrix.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] +
	                       m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2];
	resultMatrix.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] +
	                       m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3];

	return resultMatrix;
}

float InverseNum(const Matrix4x4& m, int a, int b, int c, int d, int e, int f, int g, int h) {
	float resultNum;
	resultNum = m.m[a - 1][b - 1] * m.m[c - 1][d - 1] * m.m[e - 1][f - 1] * m.m[g - 1][h - 1];
	return resultNum;
}
float InverseNum2(const Matrix4x4& m, int a, int b, int c, int d, int e, int f) {
	float resultNum;
	resultNum = m.m[a - 1][b - 1] * m.m[c - 1][d - 1] * m.m[e - 1][f - 1];
	return resultNum;
}

Matrix4x4 Inverse(const Matrix4x4& m) {
	Matrix4x4 resultInverse = {};
	float resultNum;
	resultNum = InverseNum(m, 1, 1, 2, 2, 3, 3, 4, 4) + InverseNum(m, 1, 1, 2, 3, 3, 4, 4, 2) +
	            InverseNum(m, 1, 1, 2, 4, 3, 2, 4, 3) - InverseNum(m, 1, 1, 2, 4, 3, 3, 4, 2) -
	            InverseNum(m, 1, 1, 2, 3, 3, 2, 4, 4) - InverseNum(m, 1, 1, 2, 2, 3, 4, 4, 3) -
	            InverseNum(m, 1, 2, 2, 1, 3, 3, 4, 4) - InverseNum(m, 1, 3, 2, 1, 3, 4, 4, 2) -
	            InverseNum(m, 1, 4, 2, 1, 3, 2, 4, 3) + InverseNum(m, 1, 4, 2, 1, 3, 3, 4, 2) +
	            InverseNum(m, 1, 3, 2, 1, 3, 2, 4, 4) + InverseNum(m, 1, 2, 2, 1, 3, 4, 4, 3) +
	            InverseNum(m, 1, 2, 2, 3, 3, 1, 4, 4) + InverseNum(m, 1, 3, 2, 4, 3, 1, 4, 2) +
	            InverseNum(m, 1, 4, 2, 2, 3, 1, 4, 3) - InverseNum(m, 1, 4, 2, 3, 3, 1, 4, 2) -
	            InverseNum(m, 1, 3, 2, 2, 3, 1, 4, 4) - InverseNum(m, 1, 2, 2, 4, 3, 1, 4, 3) -
	            InverseNum(m, 1, 2, 2, 3, 3, 2, 4, 1) - InverseNum(m, 1, 3, 2, 4, 3, 2, 4, 1) -
	            InverseNum(m, 1, 4, 2, 2, 3, 3, 4, 1) + InverseNum(m, 1, 4, 2, 3, 3, 2, 4, 1) +
	            InverseNum(m, 1, 3, 2, 2, 3, 4, 4, 1) + InverseNum(m, 1, 2, 2, 4, 3, 3, 4, 1);

	resultInverse.m[0][0] = (InverseNum2(m, 2, 2, 3, 3, 4, 4) + InverseNum2(m, 2, 3, 3, 4, 4, 2) +
	                         InverseNum2(m, 2, 4, 3, 2, 4, 3) - InverseNum2(m, 2, 4, 3, 3, 4, 2) -
	                         InverseNum2(m, 2, 3, 3, 2, 4, 4) - InverseNum2(m, 2, 2, 3, 4, 4, 3)) *
	                        (1 / resultNum);
	resultInverse.m[0][1] = (InverseNum2(m, 1, 4, 3, 3, 4, 2) + InverseNum2(m, 1, 3, 3, 2, 4, 4) +
	                         InverseNum2(m, 1, 2, 3, 4, 4, 3) - InverseNum2(m, 1, 2, 3, 3, 4, 4) -
	                         InverseNum2(m, 1, 3, 3, 4, 4, 2) - InverseNum2(m, 1, 4, 3, 2, 4, 3)) *
	                        (1 / resultNum);
	resultInverse.m[0][2] = (InverseNum2(m, 1, 2, 2, 3, 4, 4) + InverseNum2(m, 1, 3, 2, 4, 4, 2) +
	                         InverseNum2(m, 1, 4, 2, 2, 4, 3) - InverseNum2(m, 1, 4, 2, 3, 4, 2) -
	                         InverseNum2(m, 1, 3, 2, 2, 4, 4) - InverseNum2(m, 1, 2, 2, 4, 4, 3)) *
	                        (1 / resultNum);
	resultInverse.m[0][3] = (InverseNum2(m, 1, 4, 2, 3, 3, 2) + InverseNum2(m, 1, 3, 2, 2, 3, 4) +
	                         InverseNum2(m, 1, 2, 2, 4, 3, 3) - InverseNum2(m, 1, 2, 2, 3, 3, 4) -
	                         InverseNum2(m, 1, 3, 2, 4, 3, 2) - InverseNum2(m, 1, 4, 2, 2, 3, 3)) *
	                        (1 / resultNum);

	resultInverse.m[1][0] = (InverseNum2(m, 2, 4, 3, 3, 4, 1) + InverseNum2(m, 2, 3, 3, 1, 4, 4) +
	                         InverseNum2(m, 2, 1, 3, 4, 4, 3) - InverseNum2(m, 2, 1, 3, 3, 4, 4) -
	                         InverseNum2(m, 2, 3, 3, 4, 4, 1) - InverseNum2(m, 2, 4, 3, 1, 4, 3)) *
	                        (1 / resultNum);
	resultInverse.m[1][1] = (InverseNum2(m, 1, 1, 3, 3, 4, 4) + InverseNum2(m, 1, 3, 3, 4, 4, 1) +
	                         InverseNum2(m, 1, 4, 3, 1, 4, 3) - InverseNum2(m, 1, 4, 3, 3, 4, 1) -
	                         InverseNum2(m, 1, 3, 3, 1, 4, 4) - InverseNum2(m, 1, 1, 3, 4, 4, 3)) *
	                        (1 / resultNum);
	resultInverse.m[1][2] = (InverseNum2(m, 1, 4, 2, 3, 4, 1) + InverseNum2(m, 1, 3, 2, 1, 4, 4) +
	                         InverseNum2(m, 1, 1, 2, 4, 4, 3) - InverseNum2(m, 1, 1, 2, 3, 4, 4) -
	                         InverseNum2(m, 1, 3, 2, 4, 4, 1) - InverseNum2(m, 1, 4, 2, 1, 4, 3)) *
	                        (1 / resultNum);
	resultInverse.m[1][3] = (InverseNum2(m, 1, 1, 2, 3, 3, 4) + InverseNum2(m, 1, 3, 2, 4, 3, 1) +
	                         InverseNum2(m, 1, 4, 2, 1, 3, 3) - InverseNum2(m, 1, 4, 2, 3, 3, 1) -
	                         InverseNum2(m, 1, 3, 2, 1, 3, 4) - InverseNum2(m, 1, 1, 2, 4, 3, 3)) *
	                        (1 / resultNum);

	resultInverse.m[2][0] = (InverseNum2(m, 2, 1, 3, 2, 4, 4) + InverseNum2(m, 2, 2, 3, 4, 4, 1) +
	                         InverseNum2(m, 2, 4, 3, 1, 4, 2) - InverseNum2(m, 2, 4, 3, 2, 4, 1) -
	                         InverseNum2(m, 2, 2, 3, 1, 4, 4) - InverseNum2(m, 2, 1, 3, 4, 4, 2)) *
	                        (1 / resultNum);
	resultInverse.m[2][1] = (InverseNum2(m, 1, 4, 3, 2, 4, 1) + InverseNum2(m, 1, 2, 3, 1, 4, 4) +
	                         InverseNum2(m, 1, 1, 3, 4, 4, 2) - InverseNum2(m, 1, 1, 3, 2, 4, 4) -
	                         InverseNum2(m, 1, 2, 3, 4, 4, 1) - InverseNum2(m, 1, 4, 3, 1, 4, 2)) *
	                        (1 / resultNum);
	resultInverse.m[2][2] = (InverseNum2(m, 1, 1, 2, 2, 4, 4) + InverseNum2(m, 1, 2, 2, 4, 4, 1) +
	                         InverseNum2(m, 1, 4, 2, 1, 4, 2) - InverseNum2(m, 1, 4, 2, 2, 4, 1) -
	                         InverseNum2(m, 1, 2, 2, 1, 4, 4) - InverseNum2(m, 1, 1, 2, 4, 4, 2)) *
	                        (1 / resultNum);
	resultInverse.m[2][3] = (InverseNum2(m, 1, 4, 2, 2, 3, 1) + InverseNum2(m, 1, 2, 2, 1, 3, 4) +
	                         InverseNum2(m, 1, 1, 2, 4, 3, 2) - InverseNum2(m, 1, 1, 2, 2, 3, 4) -
	                         InverseNum2(m, 1, 2, 2, 4, 3, 1) - InverseNum2(m, 1, 4, 2, 1, 3, 2)) *
	                        (1 / resultNum);

	resultInverse.m[3][0] = (InverseNum2(m, 2, 3, 3, 2, 4, 1) + InverseNum2(m, 2, 2, 3, 1, 4, 1) +
	                         InverseNum2(m, 2, 1, 3, 3, 4, 2) - InverseNum2(m, 2, 1, 3, 2, 4, 3) -
	                         InverseNum2(m, 2, 2, 3, 3, 4, 1) - InverseNum2(m, 2, 3, 3, 1, 4, 2)) *
	                        (1 / resultNum);
	resultInverse.m[3][1] = (InverseNum2(m, 1, 1, 3, 2, 4, 3) + InverseNum2(m, 1, 2, 3, 3, 4, 1) +
	                         InverseNum2(m, 1, 3, 3, 1, 4, 2) - InverseNum2(m, 1, 3, 3, 2, 4, 1) -
	                         InverseNum2(m, 1, 2, 3, 1, 4, 3) - InverseNum2(m, 1, 1, 3, 3, 4, 2)) *
	                        (1 / resultNum);
	resultInverse.m[3][2] = (InverseNum2(m, 1, 3, 2, 2, 4, 1) + InverseNum2(m, 1, 2, 2, 1, 4, 3) +
	                         InverseNum2(m, 1, 1, 2, 3, 4, 2) - InverseNum2(m, 1, 1, 2, 2, 4, 3) -
	                         InverseNum2(m, 1, 2, 2, 3, 4, 1) - InverseNum2(m, 1, 3, 2, 1, 4, 2)) *
	                        (1 / resultNum);
	resultInverse.m[3][3] = (InverseNum2(m, 1, 1, 2, 2, 3, 3) + InverseNum2(m, 1, 2, 2, 3, 3, 1) +
	                         InverseNum2(m, 1, 3, 2, 1, 3, 2) - InverseNum2(m, 1, 3, 2, 2, 3, 1) -
	                         InverseNum2(m, 1, 2, 2, 1, 3, 3) - InverseNum2(m, 1, 1, 2, 3, 3, 2)) *
	                        (1 / resultNum);

	return resultInverse;
}

Matrix4x4 Transpose(const Matrix4x4& m) {
	Matrix4x4 mat = {m.m[0][0], m.m[1][0], m.m[2][0], m.m[3][0], m.m[0][1], m.m[1][1],
	                 m.m[2][1], m.m[3][1], m.m[0][2], m.m[1][2], m.m[2][2], m.m[3][2],
	                 m.m[0][3], m.m[0][3], m.m[2][3], m.m[3][3]};
	return mat;
}

Matrix4x4 MakeIdentity4x4() {
	Matrix4x4 mat = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	                 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
	return mat;
}

Matrix4x4 MakeRotateXMatrix(float radian) {
	Matrix4x4 mat = {1,
	                 0,
	                 0,
	                 0,
	                 0,
	                 std::cosf(radian),
	                 std::sinf(radian),
	                 0,
	                 0,
	                 -std::sinf(radian),
	                 std::cosf(radian),
	                 0,
	                 0,
	                 0,
	                 0,
	                 1};
	return mat;
}

Matrix4x4 MakeRotateYMatrix(float radian) {
	Matrix4x4 mat = {std::cosf(radian), 0, -std::sinf(radian), 0, 0, 1, 0, 0,
	                 std::sinf(radian), 0, std::cosf(radian),  0, 0, 0, 0, 1};
	return mat;
}

Matrix4x4 MakeRotateZMatrix(float radian) {
	Matrix4x4 mat = {
	    std::cosf(radian),
	    std::sinf(radian),
	    0,
	    0,
	    -std::sinf(radian),
	    std::cosf(radian),
	    0,
	    0,
	    0,
	    0,
	    1,
	    0,
	    0,
	    0,
	    0,
	    1};
	return mat;
}

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
	Matrix4x4 rotateMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));

	Matrix4x4 mat = {
	    scale.x * rotateMatrix.m[0][0],
	    scale.x * rotateMatrix.m[0][1],
	    scale.x * rotateMatrix.m[0][2],
	    0,
	    scale.y * rotateMatrix.m[1][0],
	    scale.y * rotateMatrix.m[1][1],
	    scale.y * rotateMatrix.m[1][2],
	    0,
	    scale.z * rotateMatrix.m[2][0],
	    scale.z * rotateMatrix.m[2][1],
	    scale.z * rotateMatrix.m[2][2],
	    0,
	    translate.x,
	    translate.y,
	    translate.z,
	    1};
	return mat;
}

// void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix) {
//	for (int row = 0; row < 4; ++row) {
//		for (int column = 0; column < 4; ++column) {
//			Novice::ScreenPrintf(
//			    x + column * kColumnWidth, y + row * kRowHeight, "%6.02f", matrix.m[row][column]);
//		}
//	}
// }

Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {
	Matrix4x4 mat = {
	    (1 / aspectRatio) * (1 / std::tanf(fovY / 2)),
	    0,
	    0,
	    0,
	    0,
	    1 / std::tanf(fovY / 2),
	    0,
	    0,
	    0,
	    0,
	    farClip / (farClip - nearClip),
	    1,
	    0,
	    0,
	    (-nearClip * farClip) / (farClip - nearClip),
	    0};
	return mat;
}

Matrix4x4 MakeOrthographicMatrix(
    float left, float top, float right, float bottom, float nearClip, float farClip) {
	Matrix4x4 mat = {
	    2 / (right - left),
	    0,
	    0,
	    0,
	    0,
	    2 / (top - bottom),
	    0,
	    0,
	    0,
	    0,
	    1 / (farClip - nearClip),
	    0,
	    (left + right) / (left - right),
	    (top + bottom) / (bottom - top),
	    nearClip / (nearClip - farClip),
	    1};
	return mat;
}

Matrix4x4 MakeViewportMatrix(
    float left, float top, float width, float height, float minDepth, float maxDepth) {
	Matrix4x4 resultViewport = {};

	resultViewport.m[0][0] = width / 2;
	resultViewport.m[0][1] = 0;
	resultViewport.m[0][2] = 0;
	resultViewport.m[0][3] = 0;

	resultViewport.m[1][0] = 0;
	resultViewport.m[1][1] = -height / 2;
	resultViewport.m[1][2] = 0;
	resultViewport.m[1][3] = 0;

	resultViewport.m[2][0] = 0;
	resultViewport.m[2][1] = 0;
	resultViewport.m[2][2] = maxDepth - minDepth;
	resultViewport.m[2][3] = 0;

	resultViewport.m[3][0] = left + width / 2;
	resultViewport.m[3][1] = top + height / 2;
	resultViewport.m[3][2] = minDepth;
	resultViewport.m[3][3] = 1;

	return resultViewport;
}

Vector3 Cross(const Vector3& v1, const Vector3& v2) {
	Vector3 num = {};
	num.x = v1.y * v2.z - v1.z * v2.y;
	num.y = v1.z * v2.x - v1.x * v2.z;
	num.z = v1.x * v2.y - v1.y * v2.x;

	return num;
}

Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m) {
	Vector3 result{
	    v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
	    v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1],
	    v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2]};
	return result;
}

Vector3 Multyply(const Vector3& v, const Matrix4x4& m) {
	Vector3 result = {};

	result.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z;
	result.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z;
	result.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z;

	return result;
}

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result = {};
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] +
	           1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] +
	           1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] +
	           1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] +
	          1.0f * matrix.m[3][3];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;
	return result;
}

Vector3 Slerp(const Vector3& v1, const Vector3& v2, float t) {
	float dot = Dot(v1, v2);

	t = Clamp(t, 0.0f, 1.0f);

	float theta = std::acosf(dot) * t;

	Vector3 intermediate = {v2.x - v1.x * dot, v2.y - v1.y * dot, v2.z - v1.z * dot};

	float s = std::sinf(theta);

	return {
	    v1.x * std::cosf(theta) + intermediate.x * s,
	    v1.y * std::cosf(theta) + intermediate.y * s,
	    v1.z * std::cosf(theta) + intermediate.z * s,
	};
}

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, Vector4 color) {
	const uint32_t kSubdivision = 16;
	const float kLonEvery = (2 * M_PI) / kSubdivision;
	const float kLatEvery = (M_PI) / kSubdivision;
	//緯度の方向に分割 -π/1 ～ π/2
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -M_PI / 2.0f + kLatEvery * latIndex; //現在の緯度
		//経度の方向に分割 0～2π
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery;
			//world座標系でのa, b, cを求める
			Vector3 a, b, c;
			a = { std::cos(lat) * std::cos(lon),
				std::sin(lat),
				std::cos(lat) * std::sin(lon) };

			b = { std::cos(lat + kLatEvery) * std::cos(lon),
				std::sin(lat + kLatEvery),
				std::cos(lat + kLatEvery) * std::sin(lon) };

			c = { std::cos(lat) * std::cos(lon + kLonEvery),
				std::sin(lat),
				std::cos(lat) * std::sin(lon + kLonEvery) };

			a.x *= sphere.radius;
			a.y *= sphere.radius;
			a.z *= sphere.radius;

			b.x *= sphere.radius;
			b.y *= sphere.radius;
			b.z *= sphere.radius;

			c.x *= sphere.radius;
			c.y *= sphere.radius;
			c.z *= sphere.radius;

			a.x += sphere.center.x;
			a.y += sphere.center.y;
			a.z += sphere.center.z;

			b.x += sphere.center.x;
			b.y += sphere.center.y;
			b.z += sphere.center.z;

			c.x += sphere.center.x;
			c.y += sphere.center.y;
			c.z += sphere.center.z;

			Matrix4x4 worldMatrixA = MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, a);

			Matrix4x4 worldViewProjectionMatrixA = Multiply(worldMatrixA, viewProjectionMatrix);

			Matrix4x4 worldMatrixB = MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, b);

			Matrix4x4 worldViewProjectionMatrixB = Multiply(worldMatrixB, viewProjectionMatrix);

			Matrix4x4 worldMatrixC = MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, c);

			Matrix4x4 worldViewProjectionMatrixC = Multiply(worldMatrixC, viewProjectionMatrix);

			Vector3 screenVertices[3]{};

			//NDCまで変換。Transformを使うと同時座標系->デカルト座標系の処理が行われ、結果的にZDvivideが行われることになる
			Vector3 ndcVertexA = Transform({ 0, 0, 0 }, worldViewProjectionMatrixA);
			//viewport変換を使ってScreen空間へ
			screenVertices[0] = Transform(ndcVertexA, viewportMatrix);

			//NDCまで変換。Transformを使うと同時座標系->デカルト座標系の処理が行われ、結果的にZDvivideが行われることになる
			Vector3 ndcVertexB = Transform({ 0, 0, 0 }, worldViewProjectionMatrixB);
			//viewport変換を使ってScreen空間へ
			screenVertices[1] = Transform(ndcVertexB, viewportMatrix);

			//NDCまで変換。Transformを使うと同時座標系->デカルト座標系の処理が行われ、結果的にZDvivideが行われることになる
			Vector3 ndcVertexC = Transform({ 0, 0, 0 }, worldViewProjectionMatrixC);
			//viewport変換を使ってScreen空間へ
			screenVertices[2] = Transform(ndcVertexC, viewportMatrix);

			primitiveDrawer->GetInstance()->DrawLine3d(screenVertices[0], screenVertices[1], color);

			primitiveDrawer->GetInstance()->DrawLine3d(screenVertices[0], screenVertices[2], color);
		}
	}
}

void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, Vector4 color) {
	Vector3 vers[8]{};
	vers[0] = { aabb.min.x, aabb.min.y, aabb.min.z };
	vers[1] = { aabb.min.x, aabb.min.y, aabb.max.z };
	vers[2] = { aabb.min.x, aabb.max.y, aabb.min.z };
	vers[3] = { aabb.max.x, aabb.min.y, aabb.min.z };
	vers[4] = { aabb.max.x, aabb.max.y, aabb.min.z };
	vers[5] = { aabb.min.x, aabb.max.y, aabb.max.z };
	vers[6] = { aabb.max.x, aabb.min.y, aabb.max.z };
	vers[7] = { aabb.max.x, aabb.max.y, aabb.max.z };

	Vector3 screenVers[8]{};
	for (int i = 0; i < 8; i++) {
		vers[i] = Transform(vers[i], viewProjectionMatrix);
		screenVers[i] = Transform(vers[i], viewportMatrix);
	}

	primitiveDrawer->GetInstance()->DrawLine3d(screenVers[0], screenVers[1], color);
	primitiveDrawer->GetInstance()->DrawLine3d(screenVers[0], screenVers[2], color);
	primitiveDrawer->GetInstance()->DrawLine3d(screenVers[0], screenVers[3], color);

	primitiveDrawer->GetInstance()->DrawLine3d(screenVers[1], screenVers[5], color);
	primitiveDrawer->GetInstance()->DrawLine3d(screenVers[1], screenVers[6], color);

	primitiveDrawer->GetInstance()->DrawLine3d(screenVers[2], screenVers[4], color);
	primitiveDrawer->GetInstance()->DrawLine3d(screenVers[2], screenVers[5], color);

	primitiveDrawer->GetInstance()->DrawLine3d(screenVers[3], screenVers[4], color);
	primitiveDrawer->GetInstance()->DrawLine3d(screenVers[3], screenVers[4], color);

	primitiveDrawer->GetInstance()->DrawLine3d(screenVers[4], screenVers[7], color);
	primitiveDrawer->GetInstance()->DrawLine3d(screenVers[5], screenVers[7], color);
	primitiveDrawer->GetInstance()->DrawLine3d(screenVers[6], screenVers[7], color);

}

bool IsCollision(const AABB& aabb1, const AABB& aabb2) {
	if ((aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) &&
		(aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y) &&
		(aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z)
		) {
		return true;
	}
	return false;
}

bool IsCollision(const AABB& aabb, const Sphere& sphere) {
	Vector3 clossestPoint{
		std::clamp(sphere.center.x, aabb.min.x, aabb.max.x),
		std::clamp(sphere.center.y, aabb.min.y, aabb.max.y),
		std::clamp(sphere.center.z, aabb.min.z, aabb.max.z)
	};
	float distance = Length(Subtract(clossestPoint, sphere.center));
	if (distance <= sphere.radius) {
		return true;
	}
	return false;
}
