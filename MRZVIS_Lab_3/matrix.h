#pragma once

template<typename T>
class Matrix {

private:
	T** matrix;

public:
	T** fill_null(T** matrix, int row_size, int col_size);
};

template<typename T>
T** Matrix<T>::fill_null(T** matrix, int row_size, int col_size) {

	this->matrix = new T * [row_size];

	for (int i = 0; i < row_size; i++) {

		this->matrix[i] = new T[col_size];

		for (int j = 0; j < col_size; j++) {

			this->matrix[i][j] = 0;

		}

	}

	return this->matrix;

}