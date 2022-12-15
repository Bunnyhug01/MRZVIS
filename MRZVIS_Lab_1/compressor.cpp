#include "CImg\CImg.h"
#include "compressor.h"
#include "matrix.h"
#include <iostream>
#include <fstream>

Matrix<float> matrix;

void Neuron::values() {
	fill_weights();
	fill_input();
	find_alpha();
}

void Neuron::fill_weights() {
	
	for (int i = 0; i < neurons; i++) {

		weights[0][i] = new float[stelth_neurons];

		for (int j = 0; j < stelth_neurons; j++) {

			weights[0][i][j] = (((float)(rand()) / RAND_MAX * 2) - 1) * 0.1;
		}
	}

	for (int i = 0; i < stelth_neurons; i++) {

		weights[1][i] = new float[neurons];

		for (int j = 0; j < neurons; j++) {

			weights[1][i][j] = weights[0][j][i];

		}
	}
}

void Neuron::fill_input() {

	input = new float* [blocks_count];
	for (int i = 0; i < blocks_count; i++) {

		input[i] = new float[neurons];
	}

	int Li = -1;
	for (int i = 0; i < vertical_blocks_count; i++) {

		for (int j = 0; j < horizontal_blocks_count; j++) {

			int num = 0;
			Li++;

			for (int i1 = 0; i1 < block_height; i1++) {

				for (int j1 = 0; j1 < block_width; j1++) {

					for (int k = 0; k < color; k++) {

						input[Li][num++] = (2.0 * image(j * block_width + j1, i * block_height + i1, 0, k) / 255) - 1;
					}
				}
			}
		}
	}
}

void Neuron::find_alpha() {

	alpha1 = new double[blocks_count];
	for (int q = 0; q < blocks_count; q++) {

		alpha1[q] = step;

		for (int i = 0; i < neurons; i++) {

			alpha1[q] += (double(input[q][i]) * input[q][i]);

		}

		alpha1[q] = 1 / alpha1[q];
	}

}

void Neuron::compress(bool file) {

	if (file) {
		file_weights(neurons, stelth_neurons, 0, 0);
		file_weights(stelth_neurons, neurons, 1, 0);
	}
	
	save_image("compress");
}

void Neuron::decompress(bool file) {

	if (file) {
		file_weights(neurons, stelth_neurons, 0, 0);
		file_weights(stelth_neurons, neurons, 1, 0);
	}
	
	save_image("decompress");
}

void Neuron::train() {

	weight = new float[stelth_neurons];

	int it = 0;
	do
	{
		for (int q = 0; q < blocks_count; q++) {

			alpha2 = 0;

			stelth = matrix.multiply(weights, input, stelth_neurons, neurons, q);
			output = matrix.multiply(weights, stelth, neurons,stelth_neurons);

			alpha2 = step;
			for (int i = 0; i < stelth_neurons; i++) {
				alpha2 += (stelth[i] * stelth[i]);
			}

			alpha2 = 1 / alpha2;
			for (int i = 0; i < stelth_neurons; i++) {
				weight[i] = 0;
				for (int j = 0; j < neurons; j++) {
					weight[i] += (output[j] - input[q][j]) * weights[1][i][j];
				}
			}

			for (int i = 0; i < neurons; i++) {
				for (int j = 0; j < stelth_neurons; j++) {
					weights[0][i][j] -= (alpha1[q] * input[q][i] * weight[j]);
				}
			}

			for (int i = 0; i < stelth_neurons; i++) {
				for (int j = 0; j < neurons; j++) {
					weights[1][i][j] -= alpha2 * stelth[i] * (output[j] - input[q][j]);
				}
			}

		}

		find_error();

		std::cout << "Iteration: " << it << " Error: " << error << std::endl;
		it++;
	} while (error > maximum_error);

	file_weights(neurons, stelth_neurons, 0, 1);
	file_weights(stelth_neurons, neurons, 1, 1);
}

void Neuron::find_error() {

	double difference;

	error = 0;
	for (int q = 0; q < blocks_count; q++) {
		{
			Eq = 0;

			stelth = matrix.multiply(weights, input, stelth_neurons, neurons, q);
			output = matrix.multiply(weights, stelth, neurons, stelth_neurons);

			for (int i = 0; i < neurons; i++) {
				difference = (output[i] - input[q][i]);
				Eq += (difference * difference);
			}

			error += Eq;
		}
	}

}

void Neuron::save_image(std::string operation) {

	cimg_library::CImg<unsigned char> img(image_width, image_height, 1, 3);
	img.fill(0);

	int pixel = 0;
	for (int q = 0; q < blocks_count; q++) {

		stelth = matrix.multiply(weights, input, stelth_neurons, neurons, q);
		output = matrix.multiply(weights, stelth, neurons, stelth_neurons);

		int pos = 0;
		for (int i = 0; i < block_height; i++) {

			for (int j = 0; j < block_width; j++) {

				for (int k = 0; k < color; k++) {

					if (operation == "decompress")
						pixel = (int)(255 * ((output[pos++] + 1) / 2));
					else if (operation == "compress")
						pixel = (int)(255 * ((stelth[pos++] + 1) / 2));

					if (pixel > 255) {
						pixel = 255;
					}
					if (pixel < 0) {
						pixel = 0;
					}

					img(q % horizontal_blocks_count * block_width + j, q / vertical_blocks_count * block_height + i, 0, k) = pixel;
				}
			}
		}

	}

	if (operation == "decompress")
		img.save_bmp("output_images\\decompressed.bmp");
	else if (operation == "compress")
		img.save_bmp("output_images\\compressed.bmp");
}

void Neuron::file_weights(int n, int m, int weight_number, bool in) {
	
	std::string number = std::to_string(weight_number);
	std::string file = "weights\\weights" + number + ".txt";

	std::ofstream fout;
	std::ifstream fin;

	if (in)
		fout.open(file);
	else
		fin.open(file);

	for (int i = 0; i < n; i++) {
		if (!in)
			weights[weight_number][i] = new float[m];
		for (int j = 0; j < m; j++) {
			if (in) {
				fout << weights[weight_number][i][j] << std::endl;
			}		
			else
			{
				std::string weight;
				getline(fin, weight);
			
				weights[weight_number][i][j] = std::stof(weight);
			}
		}
	}

	fout.close();
	fin.close();
}
