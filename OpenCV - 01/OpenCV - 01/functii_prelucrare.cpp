#include "functii_prelucrare.h"

My_ImageClass::My_ImageClass()
{
	fileSize = 0;
	data = 0;
	gray_data_header = 0;

	FILE *fp = fopen("My_Header.ext", "rb");
	if (!fp)
	{
		printf("Error opening file");
		exit(1);
	}

	fseek(fp, 0, SEEK_END);

	long nrBytes = ftell(fp);

	if (nrBytes <= 0)
	{
		printf("File empty");
		exit(1);
	}

	rewind(fp);

	gray_data_header = new Byte[nrBytes + 640 * 480];
	//cout << endl << nrBytes + 640 * 480 << endl;

	long readResult = fread(gray_data_header, sizeof(Byte), nrBytes, fp);

	if (readResult != nrBytes)
	{
		printf("Incorrect read");
		delete[] gray_data_header;
		fclose(fp);
		exit(1);
	}
	fileSize = readResult;
	fclose(fp);
}
My_ImageClass::~My_ImageClass()
{
	fileSize = 0;
	if (data)
	{
		delete[] data;
		data = 0;
	}
	if (gray_data_header)
	{
		delete[] gray_data_header;
		gray_data_header = 0;
	}
}

Byte* My_ImageClass::DataRead(char *fileName)
{
	if (data)
	{
		delete[] data;
		data = 0;
		cout << "ERROR: Data overwrite!" << endl;
	}

	fileSize = 0;
	if (!fileName) return 0;
	FILE *fp = fopen(fileName, "rb");
	if (!fp)
	{
		printf("Error opening file");
		return 0;
	}
	fseek(fp, 0, SEEK_END);
	long nrBytes = ftell(fp);
	if (nrBytes <= 0)
	{
		printf("File empty");
		return 0;
	}
	rewind(fp);
	data = new Byte[nrBytes];
	long readResult = fread(data, sizeof(Byte), nrBytes, fp);
	if (readResult != nrBytes)
	{
		printf("Incorrect read");
		delete[] data;
		fclose(fp);
		return 0;
	}
	fileSize = readResult;
	fclose(fp);
	return data;
}
long My_ImageClass::DataWrite(char *fileName)
{
	if (!gray_data_header || fileSize <= 0)
	{
		printf("Invalid gray_data_header");
		return 0;
	}
	if (!fileName)
	{
		printf("Invalid file name");
		return 0;
	}
	FILE *fp = fopen(fileName, "wb");
	if (!fp)
	{
		printf("Error creating file");
		return 0;
	}

	rewind(fp);
	long writeResult = fwrite(gray_data_header, sizeof(Byte), 1078 + 640 * 480, fp);
	cout << " -- " << writeResult << endl;
	rewind(fp);
	if (writeResult != (1078 + 640 * 480))
	{
		printf("Incorrect Write");
		fclose(fp);
		return 0;
	}
	return writeResult;
}
unsigned long int My_ImageClass::getWidthPixels()
{
	unsigned long int *width = (unsigned long int*)&data[18];
	cout << "Width: " << *width << " pixels.\n";
	return *width;
}
unsigned long int My_ImageClass::getHeightPixels()
{
	unsigned long int *height = (unsigned long int*)&data[22];
	cout << "Height: " << *height << " pixels.\n";
	return *height;
}
unsigned long int My_ImageClass::getOffset()
{
	unsigned long int *offset = (unsigned long int*)&data[10];
	cout << "The image starts after " << *offset << " bytes.\n";
	return *offset;
}
unsigned short int My_ImageClass::getBitsPerPixel()
{
	unsigned short int *bitsPerPixel = (unsigned short int*)&data[28];
	cout << "Bits per pixel: " << *bitsPerPixel << "\n";

	return *bitsPerPixel;
}

PixelColor My_ImageClass::positionColor(unsigned int x, unsigned int y)
{
	unsigned int x_m = getHeightPixels() - 1 - y;
	unsigned int y_m = x;

	unsigned long long int position = (x_m * getWidthPixels() + y_m) * 3 + getOffset();

	PixelColor a;

	a.b = data[position];
	a.g = data[position + 1];
	a.r = data[position + 2];

	cout << "(" << (int)a.r << ", " << (int)a.g << ", " << (int)a.b << ")\n";

	return a;
}

void My_ImageClass::negative()
{
	for (unsigned long i = getOffset(); i < fileSize; ++i)
	{
		data[i] = 0xff - data[i];
	}
}

void My_ImageClass::to_gray()
{
	unsigned long int *offset = (unsigned long int*)&gray_data_header[10];
	cout << " - toGgray" << endl;
	for (int i = 54; i < (fileSize - 2); i += 3)
	{
		gray_data_header[*offset + (i - 54) / 3] = (data[i] + data[i + 1] + data[i + 2]) / 3;
	}
	cout << " - toGray ended" << endl;
}
