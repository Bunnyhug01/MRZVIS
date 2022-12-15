#include "hopfield.h"

#include <iostream>


using namespace std;

int main() {

	vector<string> images{"train_images\\image1.txt", "train_images\\image2.txt", "train_images\\image3.txt" };
	vector<string> corrupted_image{ "corrupted_images\\image3.txt"};

	HopfieldNetwork net(images, corrupted_image, 4, 5, 200);

	net.train();
	net.recognize(0);

}