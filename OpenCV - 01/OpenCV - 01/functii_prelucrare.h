#pragma once
#include <stdio.h>
#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/plot.hpp"
#include "GraphUtils.h"
using namespace std;

typedef unsigned char Byte;
struct PixelColor
{
	Byte r, g, b;
};

class My_ImageClass
{
public:
	long fileSize;
	Byte *data;
	Byte *gray_data_header;
	float Histo[256];

public:
	My_ImageClass();
	~My_ImageClass();
	Byte* DataRead(char *fileName);
	long DataWrite(char *fileName);
	unsigned long int getWidthPixels();
	unsigned long int getHeightPixels();
	unsigned long int  getOffset();
	unsigned short int getBitsPerPixel();
	PixelColor positionColor(unsigned int x, unsigned int y);
	void negative();
	void to_gray();
};