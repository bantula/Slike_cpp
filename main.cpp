#include <iostream>
#include <fstream>
#include <sstream>
#include "ImageEditor.h"
using namespace std;

int main() {

	ImageEditor* img = new ImageEditor;

	ifstream input;
	input.open("test_in2.txt");
	stringstream ss;
	ss << input.rdbuf();
	string image = ss.str();
	input.close();

	img->loadImage(image);
	img->invertColors();
	image = img->saveImage();

	ofstream output;
	output.open("test_out.txt");
	output << image;
	output.close();

	delete img;

	return 0;
}