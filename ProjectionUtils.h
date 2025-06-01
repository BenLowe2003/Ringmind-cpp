#pragma once

#include <cmath>
#include <iostream>

// OpenGL column-major order matrix multiplication
void MatrixMultiply(float* m, float* a, float* b) {
	for (int col = 0; col < 4; ++col) {
		for (int row = 0; row < 4; ++row) {
			m[col * 4 + row] =
				a[0 * 4 + row] * b[col * 4 + 0] +
				a[1 * 4 + row] * b[col * 4 + 1] +
				a[2 * 4 + row] * b[col * 4 + 2] +
				a[3 * 4 + row] * b[col * 4 + 3];
		}
	}
}

void PerspectiveMatrix(float* m, float fovY, float aspect, float zNear, float zFar) {
	float f = 1.0f / tanf(fovY * 0.5f * 3.14159265359f / 180.0f);
	m[0] = f / aspect; m[1] = 0; m[2] = 0; m[3] = 0;
	m[4] = 0; m[5] = f; m[6] = 0; m[7] = 0;
	m[8] = 0; m[9] = 0; m[10] = (zFar + zNear) / (zNear - zFar); m[11] = -1;
	m[12] = 0; m[13] = 0; m[14] = (2 * zFar * zNear) / (zNear - zFar); m[15] = 1;
}

void OrthographicMatrix(float* m, float left, float right, float bottom, float top, float zNear, float zFar) {
	for (int i = 0; i < 16; ++i) m[i] = 0.0f;
	m[0] = 2.0f / (right - left);
	m[5] = 2.0f / (top - bottom);
	m[10] = -2.0f / (zFar - zNear);
	m[12] = -(right + left) / (right - left);
	m[13] = -(top + bottom) / (top - bottom);
	m[14] = -(zFar + zNear) / (zFar - zNear);
	m[15] = 1.0f;
}

void transpose(float* mt, float* m) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			mt[4 * i + j] = m[4 * j + i];
		}
	}
}

void RotationMatrix(float* m, float theta_x, float theta_y) {
	float cosX = cos(theta_x);
	float sinX = sin(theta_x);
	float cosY = cos(theta_y);
	float sinY = sin(theta_y);
	float x[16] = { 1,0,0,0, 0,cosX,-sinX,0, 0,sinX,cosX,0, 0,0,0,1 };
	//float y[16] = {cosY, 0, sinY, 0,0,    1, 0,    0,-sinY, 0, cosY, 0,0,    0, 0,    1};
	float y[16] = {cosY, -sinY, 0, 0,sinY,  cosY, 0, 0,0,     0,    1, 0,0,     0,    0, 1};
	MatrixMultiply(m, x, y);
}

void TranslationMatrix(float* m, float x, float y, float z) {
	for (int i = 0; i < 16; i++) {
		m[i] = 0;
	}
	m[0] = 1; m[5] = 1; m[10] = 1; m[15] = 1;
	m[12] = x; m[13] = y; m[14] = z;
}

void ProjectionMatrix(float* m, float fovY, float aspect, float zNear, float zFar, float theta_x, float theta_y, float translation_z) {

	float projection[16];
	float rotation[16];
	float translation[16];
	float mt[16];
	TranslationMatrix(translation, 0, 0, translation_z);
	RotationMatrix(rotation, theta_x, theta_y);
	MatrixMultiply(m, translation, rotation);
	float orthoWidth = 1.0f;
	float orthoHeight = orthoWidth / aspect;
	PerspectiveMatrix(projection, fovY, aspect, zNear, zFar);
	//OrthographicMatrix(projection, -orthoWidth, orthoWidth, -orthoHeight, orthoHeight, zNear, zFar);
	MatrixMultiply(m, projection, m);

	//transpose(m, mt);

	//std::cout << "Projection Matrix: " << std::endl;
	//for (int i = 0; i < 16; ++i) std::cout << m[i] << ((i % 4 == 3) ? "\n" : " ");
}
