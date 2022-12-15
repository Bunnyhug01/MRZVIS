#pragma once

template<typename T>
class Matrix{

private:
	T** matrix;

public:

	T** transpose(T** matrix, int row_size, int col_size);
	T** multiply(T** first_matrix, T** second_matrix, int row_size, int first_col_size, int second_col_size);
	T** number_multiply(T** matrix, int row_size, int col_size, T number);
	T** nullify_diagonal(T** matrix, int row_size, int col_size);
};

template<typename T>
T** Matrix<T>::transpose(T** matrix, int row_size, int col_size) {
	
	this->matrix = new T* [col_size];

	for (int i = 0; i < col_size; i++) {

		this->matrix[i] = new T[row_size];

		for (int j = 0; j < row_size; j++) {

			this->matrix[i][j] = matrix[j][i];

		}
	}

	return this->matrix;

}

template<typename T>
T** Matrix<T>::multiply(T** first_matrix, T** second_matrix, int row_size, int first_col_size, int second_col_size) {

	this->matrix = new T* [row_size];

	for (int i = 0; i < row_size; i++) {

		this->matrix[i] = new T[second_col_size];

		for (int j = 0; j < second_col_size; j++) {

			this->matrix[i][j] = 0;

			for (int k = 0; k < first_col_size; k++) {

				this->matrix[i][j] += first_matrix[i][k] * second_matrix[k][j];

			}

		}

	}

	return this->matrix;

}

template<typename T>
T** Matrix<T>::number_multiply(T** matrix, int row_size, int col_size, T number) {

	this->matrix = new T* [row_size];

	for (int i = 0; i < row_size; i++) {

		this->matrix[i] = new T[col_size];

		for (int j = 0; j < col_size; j++) {

			this->matrix[i][j] = matrix[i][j] * number;

		}
	}

	return this->matrix;

}

template<typename T>
T** Matrix<T>::nullify_diagonal(T** matrix, int row_size, int col_size) {

	this->matrix = new T* [row_size];

	for (int i = 0; i < row_size; i++) {

		this->matrix[i] = new T[col_size];

		for (int j = 0; j < col_size; j++) {

			matrix[i][i] = 0;
			this->matrix[i][j] = matrix[i][j];

		}
	}

	return this->matrix;

}