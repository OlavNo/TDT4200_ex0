#include <stdlib.h>
#include <stdio.h>
#include "bitmap.h"

#define XSIZE 2560 // Size of before image
#define YSIZE 2048



void invertColor(uchar* image) {
	for (int i = 0; i < XSIZE * YSIZE * 3; i++)	
	{
		image[i] = 255 - image[i];
	}
}

void grayscale(uchar* image) {
	uchar red, green, blue;
	uchar gray;
	for (int i = 0; i < XSIZE * YSIZE * 3; i += 3)	
	{
		blue = image[i];
		green = image[i + 1];
		red = image[i + 2];
		
		gray = (uchar)(0.33 * red + 0.33 * green + 0.33 * blue)/3;

		image[i] = gray;
		image[i + 1] = gray;
		image[i + 2] = gray;
	}
}

void isolateColor(uchar* image, uchar c) {

	for (int i = 0; i < XSIZE * YSIZE * 3; i += 3)	
	{	
		switch (c)
		{
		case 'r':
			image[i] = 0; // blue
			image[i + 1] = 0; // green
			break;
		case 'g':
			image[i] = 0; // blue
			image[i + 2] = 0; // red
			break;
		case 'b':
			image[i + 1] = 0; // green
			image[i + 2] = 0; // red
			break;
		default:
			break;
		}
		
	}
}


void copyPixel(uchar* new, uchar* old, int posNew, int posOld) {
	
	new[posNew*3] = old[posOld*3];
	new[posNew*3 + 1] = old[posOld*3 + 1];
	new[posNew*3 + 2] = old[posOld*3 + 2];
}

void scaleRow(uchar* new, uchar* old, int rowNew, int rowOld) {
	for (int i = 1; i < XSIZE; i++)
	{
		copyPixel(new, old, i*2 + rowNew * XSIZE * 2, i + rowOld * XSIZE);
		copyPixel(new, old, i*2 - 1 + rowNew * XSIZE * 2, i + rowOld * XSIZE);
	}
}

uchar* doubleSize(uchar* image) {
	uchar *resized = calloc(4 * XSIZE * YSIZE * 3 , 1);
	
	for (int j = 1; j < YSIZE; j++)
	{
		scaleRow(resized, image, j*2, j);
		scaleRow(resized, image, j*2 - 1, j);	
	}
	
	return resized;
}


int main(void)
{
	uchar *image = calloc(XSIZE * YSIZE * 3, 1); // Three uchars per pixel (RGB)
	readbmp("before.bmp", image);

	
	// Alter the image here
	
	// invertColor(image);

	isolateColor(image, 'g');

	uchar *bigger = doubleSize(image);
	// grayscale(image);

	savebmp("after.bmp", bigger, XSIZE * 2, YSIZE * 2);

	free(image);
	free(bigger);
	return 0;
}
