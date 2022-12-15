#pragma once

template <typename T>
class Matrix {

public:
	T* multiply(T*** first_matrix,T** second_matrix ,int n, int m, int q);
	T* multiply(T*** first_matrix, T* second_matrix, int n, int m);
private:
	T* matrix;

};

template <typename T>
T* Matrix<T>::multiply(T*** first_matrix, T** second_matrix, int n, int m, int q) {

	matrix = new T[n];

	for (int i = 0; i < n; i++) {

		matrix[i] = 0;

		for (int j = 0; j < m; j++) {

			matrix[i] += first_matrix[0][j][i] * second_matrix[q][j];
		}
	}

	return matrix;
}

template <typename T>
T* Matrix<T>::multiply(T*** first_matrix, T* second_matrix, int n, int m) {

	matrix = new T[n];

	for (int i = 0; i < n; i++) {

		matrix[i] = 0;

		for (int j = 0; j < m; j++) {

			matrix[i] += first_matrix[1][j][i] * second_matrix[j];

		}
	}

	return matrix;
}