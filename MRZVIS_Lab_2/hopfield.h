#pragma once

#include<vector>
#include <string>

class HopfieldNetwork {

public:

	HopfieldNetwork(std::vector<std::string> train_images, std::vector<std::string> corrupted_image, int image_rows, int image_cols, int error) {

		this->train_images = train_images;
		this->image_rows = image_rows;
		this->image_cols = image_cols;

		this->matrix_rows = train_images.size();
		this->matrix_cols = this->image_rows * this->image_cols;

		this->corrupted_image = corrupted_image;


		this->error = error;
	}

	void train();
	void recognize(bool file);

private:

	int image_rows, image_cols;
	int matrix_rows, matrix_cols;

	int error;

	std::vector<std::string> train_images;
	std::vector<std::string> corrupted_image;

	float** start_matrix;
	float** transposed_matrix;
	float** input;
	float** output;
	float** weights;

	bool status;

	float** parse_image(std::vector<std::string> images, float** start_matrix, int matrix_rows, int matrix_cols);
	void show_image(int image_number);

	void train_weights();
	int work();
	void file_weights(int rows, int cols, bool in);

};