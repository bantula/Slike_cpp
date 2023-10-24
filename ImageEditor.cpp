#include "ImageEditor.h"
#include "Pixels.h"

ImageEditor::ImageEditor() {
	this->width = this->height = 0;
	this->pixels = nullptr;
}

ImageEditor::~ImageEditor() {
	for (int i = 0; i < this->height; i++) {
		for (int j = 0; j < this->width; j++) {
			delete this->pixels[i][j]; //Ovo briše piksele
		}
		delete[] this->pixels[i]; //Ovo briše niz pokazivaca na piksele
	}
	delete[] this->pixels;
}

int ImageEditor::readNumber(string str, int& pos) {
	int number = 0;
	while (str[pos] != '\n') {
		number = number * 10 + (str[pos] - '0'); //?ita višecifreni broj
		pos++;
	}
	pos++;
	return number;
}

Pixel* ImageEditor::readPixel(string str, int& pos) {
	Pixel* pixel = new Pixel;
	pixel->setRed(readNumber(str, pos));
	pixel->setGreen(readNumber(str, pos)); 
	pixel->setBlue(readNumber(str, pos)); 
	return pixel;
}

void ImageEditor::makeMatrix() {
	this->pixels = new Pixel** [this->height]; //Zanima nas konkretan piksel ove slike, ne neki random pixel

	for (int i = 0; i < this->height; i++) {
		this->pixels[i] = new Pixel* [this->width];
	}
}

void ImageEditor::loadImage(string image) {
	// Vrsimo algoritamsku dekompoziciju i delimo parsiranje ovog stringa na nekoliko delova
	int pos = 0;

	// Read dimensions
	this->width = readNumber(image, pos);
	this->height = image[pos] != '-' ? readNumber(image, pos) : this->width;
	pos += 2;

	/*if (image[pos] == '-') {
		this->height = width;
	}
	else {
		this->height = readNumber(image, pos);
	}
	pos += 2; preskace se novi red kao svaki drugi clan stringa */

	makeMatrix();

	// Read pixels
	for (int i = 0, j = 0; pos < image.length();) {
		pixels[i][j++] = readPixel(image, pos); //Pametan na?in da se izbegnu dve petlje
		if (j == width) {
			j = 0;
			i++;
		}
	}
}

string ImageEditor::saveImage() {
	string image;
	image.append(to_string(this->width));
	image.append("\n");
	if (this->width != this->height) {
		image.append(to_string(this->height));
		image.append("\n");
	}
	image.append("-\n");
	for (int i = 0; i < this->height; i++) {
		for (int j = 0; j < this->width; j++) {
			image.append(to_string(this->pixels[i][j]->getRed()));
			image.append("\n");
			image.append(to_string(this->pixels[i][j]->getGreen()));
			image.append("\n");
			image.append(to_string(this->pixels[i][j]->getBlue()));
			image.append("\n");
		}
	}
	return image;
}

void ImageEditor::invertColors() {
	for (int i = 0; i < this->height; i++) {
		for (int j = 0; j < this->width; j++) {
			this->pixels[i][j]->invertColors();
		}
	}
}

void ImageEditor::toGrayScale() {
	for (int i = 0; i < this->height; i++) {
		for (int j = 0; j < this->width; j++) {
			this->pixels[i][j]->toGrayscale();
		}
	}
}
