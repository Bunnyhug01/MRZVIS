#include "network.h"
#include "matrix.h"

#include <iostream>
#include <cmath>
#include <fstream>
#include <string>

Matrix<double> matrix;

void Network::train(bool file) {

	matrix.fill_null(data, 1 , neurons);

	if (file == false) {

		first_weights = fill_weight(size, neurons);
		second_weights = fill_weight(neurons, 1);
		data_weights = fill_weight(neurons, neurons);

	}
	else {

		first_weights = file_weights_out(1,size, neurons);
		second_weights = file_weights_out(2, neurons, 1);
		data_weights = file_weights_out(3, neurons, neurons);

	}
	

	learn();
	matrix.fill_null(data, 1, neurons);

}

void Network::predict() {

	int seq_size = sequence.size();

	for (int i = 0; i < predictions_count; i++) {
		for (int j = 0; j < size; j++) {
			vectorInput[0][j] = sequence[seq_size - size + i + j];
		}
		calculate_output();
		sequence.push_back(output);
	}

	std::cout << "Result: " << std::endl;
	for (int i = 0; i < sequence.size(); i++)
		std::cout << sequence[i] << " ";

	std::cout << std::endl;
}

double** Network::fill_weight(int rows, int cols){

	double** weights = new double* [rows];
	for (int i = 0; i < rows; i++) {

		weights[i] = new double[cols];

		for (int j = 0; j < cols; j++) {

			weights[i][j] = (double)(rand()) / RAND_MAX * 2 - 1;

		}

	}

	return weights;
}

void Network::calculate_output() {

	for (int i = 0; i < neurons; i++) {

		currentData[0][i] = 0;
		for (int j = 0; j < size; j++) {

			currentData[0][i] += vectorInput[0][j] * first_weights[j][i];

		}

		for (int k = 0; k < neurons; k++) {

			currentData[0][i] += data[0][k] * data_weights[k][i];

		}

		currentData[0][i] = th_activation(currentData[0][i]);

	}

	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < neurons; j++) {

			data[i][j] = currentData[i][j];

		}
	}

	output = 0;
	for (int i = 0; i < neurons; i++) {
		for (int j = 0; j < 1; j++) {
			output += currentData[j][i] * second_weights[i][j];
		}
	}

	output = th_activation(output);

}

void Network::learn() {

	double finError = 0;
	int it = 0;

	do
	{

		if (it < iteration_count) {

			for (int row = 0; row < neurons; row++) {
				
				for (int i = 0; i < 1; i++) {

					for (int j = 0; j < size; j++) {
						vectorInput[i][j] = input[row][j];
					}
				}

				calculate_output();
				
				double error = output - sequence[sequence.size() - neurons + row];

				for (int i = 0; i < neurons; i++) {

					for (int j = 0; j < 1; j++) {

						second_weights[i][j] = second_weights[i][j] - alpha * error * currentData[j][i];

					}

				}
				
				for (int i = 0; i < size; i++) {

					for (int j = 0; j < neurons; j++) {

						first_weights[i][j] = first_weights[i][j] - alpha * error * second_weights[j][0] * th_derivative(currentData[0][j]) * input[row][size - 1 - i];

					}

				}

				for (int i = 0; i < neurons; i++) {

					for (int j = 0; j < neurons; j++) {

						data_weights[i][j] = data_weights[i][j] - alpha * error * second_weights[j][0] * th_derivative(currentData[0][j]) * data[0][j];

					}

				}

			}

			finError = 0;

			for (int l = 0; l < neurons; l++) {

				for (int i = 0; i < 1; i++) {

					for (int j = 0; j < size; j++) {
						vectorInput[i][j] = input[l][j];
					}
				}

				calculate_output();

				double error = output - sequence[sequence.size() - neurons + l];
				finError += 0.5 * pow(error, 2);
			}

			if (it % 1000 == 0) {
				std::cout << "Iteration: " << it << " Error: " << finError << std::endl;
			}

			it++;
		}
		else {
			break;
		}

	} while (finError > error);

	file_weights(first_weights, 1, size, neurons);
	file_weights(second_weights, 2, neurons, 1);
	file_weights(data_weights, 3, neurons, neurons);

}

double Network::th_activation(double x) {
	return tanh(x);
}

double Network::th_derivative(double x) {
	return 1 / (pow(cosh(x), 2));
}

void Network::file_weights(double** weights, int weight_number, int rows, int cols) {

	std::string number = std::to_string(weight_number);
	std::string file = "weights\\weights" + number + ".txt";

	std::ofstream fout;
	
	fout.open(file);

	for (int i = 0; i < rows; i++) {

		for (int j = 0; j < cols; j++) {

			fout << weights[i][j] << std::endl;


		}
	}

	fout.close();
	
}

double** Network::file_weights_out(int weight_number, int rows, int cols) {

	double** weights;

	std::ifstream fin;

	std::string number = std::to_string(weight_number);
	std::string file = "weights\\weights" + number + ".txt";

	fin.open(file);

	weights = new double* [rows];

	for (int i = 0; i < rows; i++) {

		weights[i] = new double[cols];

		for (int j = 0; j < cols; j++) {

			std::string weight;
			getline(fin, weight);

			weights[i][j] = std::stof(weight);

		}
	}

	fin.close();

	return weights;
}