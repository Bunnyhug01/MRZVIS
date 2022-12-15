#include <iostream>
#include "CImg\CImg.h"
#include "compressor.h"

using namespace std;

int main() {

	int block_height, block_width, stelth_neurons, maximum_error;
	int operation;

	cimg_library::CImg<unsigned char> image("images\\picture1.bmp");

	cout << "Enter the following values: " << endl;
	cout << "Block Height, Block Width, Stealth Neurons, Maximum Error" << endl;
	cin >> block_height >> block_width >> stelth_neurons >> maximum_error;

	Neuron compressor = Neuron(image, block_height, block_width, stelth_neurons, maximum_error);
	
	while (true) {

		cout << "Choose operation:\n 1. Train \n 2. Compression \n 3. Decompression \n 4.Exit" << endl;
		cin >> operation;

		switch (operation) {
			case 1:
			{
				compressor.train();
				break;
			}
			case 2:
			{
				compressor.compress(1);
				break;
			}
			case 3:
			{
				compressor.decompress(1);
				break;
			}
			case 4:
			{
				return false;
			}
			default:
			{
				cout << "From 1 to 5!" << endl;
			}
		}
	}
	
}
