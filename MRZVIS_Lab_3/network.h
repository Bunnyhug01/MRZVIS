#pragma once

#include <vector>

class Network {

public:
	Network(std::vector<double> sequence, int size, double error, double alpha, int predictions_count, int iteration_count) {

		this->sequence = sequence;

		this->size = size;
		this->error = error;
		this->alpha = alpha;
		this->iteration_count = iteration_count;
		this->predictions_count = predictions_count;
		
		this->neurons = sequence.size() - size;

		this->currentData = new double* [1];
		this->data = new double* [1];

		this->currentData[0] = new double[neurons];
		this->data[0] = new double[neurons];

		this->input = new double* [this->neurons];
		this->vectorInput = new double* [1];
		
		this->vectorInput[0] = new double[this->size];

		for (int i = 0; i < this->neurons; i++) {

			this->input[i] = new double[this->size];

			for (int j = 0; j < this->size; j++) {

				this->input[i][j] = this->sequence[i + j];
			}

		}

	};
	
	void train(bool file);
	void predict();

private:

	std::vector<double> sequence;

	double** first_weights;
	double** second_weights;
	double** data_weights;

	double** input;
	double** vectorInput;
	double** data;
	double** currentData;

	double output;

	int rows, cols;
	int neurons, size;
	int iteration_count;
	int predictions_count;

	double error;
	double alpha;

	double** fill_weight(int rows, int cols);

	void calculate_output();
	void learn();
	void file_weights(double** weights, int weight_number, int rows, int cols);
	double** file_weights_out(int weight_number, int rows, int cols);


	double th_activation(double x);
	double th_derivative(double x);
};