#include "network.h"

#include <iostream>
#include <vector>

using namespace std;


int main() {

	vector<vector <double>> sequence = { { 1, 0, -1, 0, 1, 0, -1, 0 }, {0.01, 0.01, 0.02, 0.03, 0.05, 0.08, 0.13, 0.21}, { 1, 0.5, 0.25, 0.125, 0.0625, 0.03125, 0.015625, 0.0078125}, { 0.0001, 0.0001, 0.0002, 0.0006, 0.0024, 0.0120, 0.0720, 0.5760} };

	Network net(sequence[1], 4, 0.0001, 0.0001, 4, 1000000);
	net.train(1);
	net.predict();

}