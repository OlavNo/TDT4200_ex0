#include <stdlib.h>
#include <stdio.h>
#include "bitmap.h"

#define XSIZE 2560 // Size of before image
#define YSIZE 2048
#define CHANNELS 3 // RGB colors


void invertColor(uchar* image) {
	for (int i = 0; i < XSIZE * YSIZE * CHANNELS; i++)	
	{
		image[i] = 255 - image[i];
	}
}

void grayscale(uchar* image) {
	uchar red, green, blue;
	uchar gray;
	for (int i = 0; i < XSIZE * YSIZE * CHANNELS; i += CHANNELS)	
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

	for (int i = 0; i < XSIZE * YSIZE * CHANNELS; i += CHANNELS)	
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

// Copy pixel from old index to new index
void copyPixel(uchar* newImage, uchar* oldImage, int newPos, int oldPos) {
	for (int i = 0; i < CHANNELS; i++)
	{
		newImage[newPos*CHANNELS + i] = oldImage[oldPos*CHANNELS + i];
	}
}

// Scale selected row using old image
void scaleRow(uchar* newImage, uchar* oldImage, int scale, int newRow, int oldRow) {
	
	int newOffset = newRow * XSIZE * scale;
	int oldOffset = oldRow * XSIZE;

	for (int i = scale - 1; i < XSIZE; i++)
	{
		int newPos = newOffset + i*scale;
		int oldPos = i + oldOffset;

		// place new pixels scale amount of times
		for (int j = 0; j < scale; j++)
		{
			copyPixel(newImage, oldImage, newPos - j, oldPos);
		}
	}
}

// Create a new image that is scaled
uchar* scaleImage(uchar* image, int scale) {
	uchar *resized = calloc(scale * scale * XSIZE * YSIZE * CHANNELS , 1);

	for (int j = scale - 1; j < YSIZE; j++)
	{
		int newRow = j*scale;
		
		// place new rows scale amount of times
		for (int i = 0; i < scale; i++)
		{
			scaleRow(resized, image, scale, newRow - i, j);
		}
	}
	
	return resized;
}


int main(void)
{
	uchar *image = calloc(XSIZE * YSIZE * CHANNELS, 1); // Three uchars per pixel (RGB)
	readbmp("before.bmp", image);

	int scale = 2;

	// grayscale(image);
	
	invertColor(image);

	isolateColor(image, 'r');


	uchar *largeImage = scaleImage(image, scale);

	savebmp("after.bmp", largeImage, XSIZE * scale, YSIZE * scale);

	free(image);
	free(largeImage);
	
	return 0;
}
