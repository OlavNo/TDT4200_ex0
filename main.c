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


uchar* resizedBmp(uchar* image, int scale) {
	uchar *resized = calloc(XSIZE * scale * YSIZE * scale * 3 , 1);
	

	for (int i = 0; i < XSIZE * YSIZE * 3; i++)
	{
		for (int j = 0; j < scale; j++)
		{
			resized[2*i + j] = image[i];
		}
	}
	return resized;
}


int main(void)
{
	uchar *image = calloc(XSIZE * YSIZE * 3, 1); // Three uchars per pixel (RGB)
	readbmp("before.bmp", image);

	
	// Alter the image here
	
	// invertColor(image);

	// isolateColor(image, 'r');

	uchar *bigger = resizedBmp(image, 2);
	// grayscale(image);

	savebmp("after.bmp", bigger, XSIZE * 2, YSIZE * 2);

	free(image);
	free(bigger);
	return 0;
}
