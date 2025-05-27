#pragma once

void MatrixMultiply(float* m, float* a, float* b) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i * 4 + j] = a[i * 4 + 0] * b[0 * 4 + j] +
				a[i * 4 + 1] * b[1 * 4 + j] +
				a[i * 4 + 2] * b[2 * 4 + j] +
				a[i * 4 + 3] * b[3 * 4 + j];
		}
	}
}

void PerspectiveMatrix(float* m, float fovY, float aspect, float zNear, float zFar) {
    float f = 1.0f / tanf(fovY * 0.5f * 3.14159265359f / 180.0f);
    m[0] = f / aspect; m[1] = 0; m[2] = 0; m[3] = 0;
    m[4] = 0; m[5] = f; m[6] = 0; m[7] = 0;
    m[8] = 0; m[9] = 0; m[10] = (zFar + zNear) / (zNear - zFar); m[11] = -1;
    m[12] = 0; m[13] = 0; m[14] = (2 * zFar * zNear) / (zNear - zFar); m[15] = 0;
}

void PerspectiveMatrixInfiniteFar(float* m, float fovY, float aspect, float zNear) {
	float f = 1.0f / tanf(fovY * 0.5f * 3.14159265359f / 180.0f);
	m[0] = f / aspect; m[1] = 0; m[2] = 0; m[3] = 0;
	m[4] = 0; m[5] = f; m[6] = 0; m[7] = 0;
	m[8] = 0; m[9] = 0; m[10] = -1.0f; m[11] = -1.0f;
	m[12] = 0; m[13] = 0; m[14] = -2.0f * zNear; m[15] = 0;
}

void RotationMatrix(float* m, float theta_x, float theta_y) {
	float cosX = cos(theta_x);
	float sinX = sin(theta_x);
	float cosY = cos(theta_y);
	float sinY = sin(theta_y);
	float x[16];
	float y[16];
	for (int i = 0; i < 16; i++) {
		x[i] = 0;
		y[i] = 0;
	}
	x[0] = 1; x[1] = 0; x[2] = 0; x[3] = 0;
	x[4] = 0; x[5] = cosX; x[6] = -sinX; x[7] = 0;
	x[8] = 0; x[9] = sinX; x[10] = cosX; x[11] = 0;
	x[12] = 0; x[13] = 0; x[14] = 0; x[15] = 1;
	y[0] = cosY; y[1] = 0; y[2] = sinY; y[3] = 0;
	y[4] = 0; y[5] = 1; y[6] = 0; y[7] = 0;
	y[8] = -sinY; y[9] = 0; y[10] = cosY; y[11] = 0;
	y[12] = 0; y[13] = 0; y[14] = 0; y[15] = 1;
	MatrixMultiply(m, x, y);
}

void TranslationMatrix(float* m, float x, float y, float z) {
	for (int i = 0; i < 16; i++) {
		m[i] = 0;
	}
	m[0] = 1; m[1] = 0; m[2] = 0; m[3] = 0;
	m[4] = 0; m[5] = 1; m[6] = 0; m[7] = 0;
	m[8] = 0; m[9] = 0; m[10] = 1; m[11] = 0;
	m[12] = x; m[13] = y; m[14] = z; m[15] = 1;
}






void ProjectionMatrix(float* m, float fovY, float aspect, float zNear, float theta_x, float theta_y, float translation_z) {
	float projection[16];
	float rotation[16];
	float translation[16];
	PerspectiveMatrixInfiniteFar(projection, fovY, aspect, zNear);
	TranslationMatrix(translation, 0, 0, -translation_z);
	RotationMatrix(rotation, theta_x, theta_y);
	MatrixMultiply(m, translation, projection);
	MatrixMultiply(m, rotation, m);
}