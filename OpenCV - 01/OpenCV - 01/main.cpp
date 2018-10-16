#include "opencv2/opencv.hpp"
#include "functii_prelucrare.h"
using namespace cv;

int main(int, char**)
{
	unsigned short int a = 0;
	char s1[] = "image.bmp", s2[] = "image2.bmp", q[] = "image5.bmp";
	unsigned long int size = 0;
	VideoCapture cap(0);

	if (!cap.isOpened())
	{
		return -1;
	}

	/* Capture image and save it into s1 filName */
	std::cout << "Camera opened.\n";
	Mat frame;
	cap >> frame;
	
	//frame = imread(s1);
	
	imwrite(s1, frame);
	cvtColor(frame, frame, COLOR_BGR2GRAY);
	imwrite(s2, frame);

	/* read data from s1 fileName and save it into our My_ImageClass */

	My_ImageClass my_image;
	my_image.DataRead(s1);
	my_image.to_gray();
	my_image.DataWrite(q);



	std::cout << "Program ended.\n";
	return 0;
}
//nifjawifeisemf;sef