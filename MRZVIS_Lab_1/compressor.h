#pragma once
#include <string>

class Neuron {

public:
	Neuron(cimg_library::CImg<unsigned char> image, int block_height, int block_width, int stelth_neurons, int maximum_error) {
		this->image = image;
		this->block_height = block_height;
		this->block_width = block_width;
		this->stelth_neurons = stelth_neurons;
		this->maximum_error = maximum_error;

		this->image_height = this->image.height();
		this->image_width = this->image.width();

		this->neurons = this->block_height * this->block_width * color;

		this->vertical_blocks_count = this->image_height / this->block_height;
		this->horizontal_blocks_count = this->image_width / this->block_width;
		this->blocks_count = this->vertical_blocks_count * this->horizontal_blocks_count;

		weights[0] = new float* [neurons];
		weights[1] = new float* [this->stelth_neurons];

		stelth = new float[this->stelth_neurons];
		output = new float[neurons];

		values();
	}

	void compress(bool file);
	void train();
	void decompress(bool file);

private:
	cimg_library::CImg<unsigned char> image;

	int color = 3;
	int step = 400;

	int image_height;
	int image_width;

	int block_height, block_width;
	int stelth_neurons;
	double maximum_error;

	double error = 0;
	double Eq = 0;

	double* alpha1 = 0;
	double alpha2 = 0;

	int neurons;

	int vertical_blocks_count;
	int horizontal_blocks_count;

	int blocks_count;

	float** weights[2];
	float** input;
	float* stelth;
	float* output;
	float* weight;

	void fill_weights();
	void fill_input();
	void find_alpha();
	void values();
	void find_error();
	void save_image(std::string operation);
	void file_weights(int n,int m, int weight_number, bool in);
};