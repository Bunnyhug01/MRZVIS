#include "hopfield.h"
#include "matrix.h"

#include<iostream>
#include <fstream>
#include <algorithm>

Matrix<float> matrix;

void HopfieldNetwork::train() {

	start_matrix = parse_image(train_images, start_matrix, matrix_rows, matrix_cols);
	train_weights();
}

void HopfieldNetwork::recognize(bool file) {
	
	input = parse_image(corrupted_image, input, 1, matrix_cols);

	if (file)
		file_weights(matrix_cols, matrix_cols, 0);

	int image_number = work();

	if (status)
		show_image(image_number);
	else
		std::cout << "No coincidences" << std::endl;
}

void HopfieldNetwork::train_weights() {

	float oneDivisionN = 1 / float(matrix_cols);

	transposed_matrix = matrix.transpose(start_matrix, matrix_rows, matrix_cols);

	weights = matrix.multiply(transposed_matrix, start_matrix, matrix_cols , matrix_rows, matrix_cols);
	weights = matrix.number_multiply(weights, matrix_cols, matrix_cols, oneDivisionN);
	weights = matrix.nullify_diagonal(weights, matrix_cols, matrix_cols);


	file_weights(matrix_cols, matrix_cols, 1);
}

int HopfieldNetwork::work() {

	int error = 0;

	while (error < this->error) {	

		input = matrix.transpose(input, 1, matrix_cols);
		output = matrix.multiply(weights, input, matrix_cols, matrix_cols, 1);


		for (int i = 0; i < matrix_cols; i++) {

			for (int j = 0; j < 1; j++) {

				if (output[i][j] >= 0)
					output[i][j] = 1;
				else
					output[i][j] = -1;

			}

		}

		output = matrix.transpose(output, matrix_cols, 1);

		int image_number = 0;
		status = false;

		for (int i = 0; i < matrix_rows; i++) {

			int compare_count = 0;

			for (int j = 0; j < matrix_cols; j++) {

				if (output[0][j] == start_matrix[i][j])
					compare_count++;

			}

			if (compare_count == matrix_cols) {
				status = true;
				image_number = i + 1;

				break;
			}

		}

		if (status)
			return image_number;
		else {

			error++;

			for (int i = 0; i < 1; i++) {

				for (int j = 0; j < matrix_cols; j++) {

					input[i][j] = output[i][j];

				}

			}

			for (int i = 0; i < 1; i++) {

				for (int j = 0; j < matrix_cols; j++) {

					output[i][j] = 0;

				}

			}

		}

	}

}

float** HopfieldNetwork::parse_image(std::vector<std::string> images, float** start_matrix, int matrix_rows, int matrix_cols) {

	std::ifstream fin;
	
	start_matrix = new float* [matrix_rows];
	for (int i = 0; i < matrix_rows; i++) {

		int counter = 0;
		start_matrix[i] = new float[matrix_cols];

		fin.open(images[i]);

		for (int j = 0; j < image_rows; j++) {

			for (int k = 0; k <= image_cols; k++) {

				char input;
				fin.get(input);

				if (input == '0')
					input = '1';
				else if (input == ' ')
					input = '0';

				if (input != '\n') {

					start_matrix[i][k + counter] = (float)(input - '0');

					if (start_matrix[i][k + counter] == 0)
						start_matrix[i][k + counter] = -1;

				}

				if (k == image_cols)
					counter += k;

			}

		}

		fin.close();

	}

	return start_matrix;

}

void HopfieldNetwork::show_image(int image_number) {

	std::ifstream fin_image, fin_corrupted_image;

	std::string image_name = "train_images\\image" + std::to_string(image_number) + ".txt";
	std::string corrupted_image_name = "corrupted_images\\image" + std::to_string(image_number) + ".txt";

	
	fin_corrupted_image.open(corrupted_image_name);

	std::cout << "Corrupted Image" << std::endl;
	for (int i = 0; i < image_rows; i++) {

		std::string line;
		getline(fin_corrupted_image, line);

		std::cout << line << std::endl;

	}

	fin_corrupted_image.close();


	fin_image.open(image_name);

	std::cout << std::endl << "Image" << std::endl;
	for (int i = 0; i < image_rows; i++) {

		std::string line;
		getline(fin_image, line);

		std::cout << line << std::endl;

	}

	fin_image.close();
}


void HopfieldNetwork::file_weights(int rows, int cols, bool in) {

	std::string file = "weights\\weights.txt";

	std::ofstream fout;
	std::ifstream fin;

	if (in)
		fout.open(file);
	else {
		fin.open(file);

		weights = new float * [rows];
	}
		

	for (int i = 0; i < rows; i++) {

		if (!in)
			weights[i] = new float[cols];

		for (int j = 0; j < cols; j++) {

			if (in) {
				fout << weights[i][j] << std::endl;
			}
			else
			{
				std::string weight;
				getline(fin, weight);

				weights[i][j] = std::stof(weight);
			}
		}
	}
	
	fout.close();
	fin.close();
}