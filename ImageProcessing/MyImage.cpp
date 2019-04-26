#include <Windows.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "MyImage.h"

using namespace std;
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

BYTE* LoadBMP(int% width, int% height, long% size, LPCTSTR bmpfile)
{
	// declare bitmap structures
	BITMAPFILEHEADER bmpheader;
	BITMAPINFOHEADER bmpinfo;
	// value to be used in ReadFile funcs
	DWORD bytesread;
	// open file to read from
	HANDLE file = CreateFile(bmpfile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (NULL == file)
		return NULL; // coudn't open file

					 // read file header
	if (ReadFile(file, &bmpheader, sizeof(BITMAPFILEHEADER), &bytesread, NULL) == false) {
		CloseHandle(file);
		return NULL;
	}
	//read bitmap info
	if (ReadFile(file, &bmpinfo, sizeof(BITMAPINFOHEADER), &bytesread, NULL) == false) {
		CloseHandle(file);
		return NULL;
	}
	// check if file is actually a bmp
	if (bmpheader.bfType != 'MB') {
		CloseHandle(file);
		return NULL;
	}
	// get image measurements
	width = bmpinfo.biWidth;
	height = abs(bmpinfo.biHeight); // abs mutlak deðer

									 // check if bmp is uncompressed
	if (bmpinfo.biCompression != BI_RGB) {
		CloseHandle(file);
		return NULL;
	}
	// check if we have 24 bit bmp
	if (bmpinfo.biBitCount != 24) {
		CloseHandle(file);
		return NULL;
	}

	// create buffer to hold the data
	size = bmpheader.bfSize - bmpheader.bfOffBits;
	BYTE* Buffer = new BYTE[size];
	// move file pointer to start of bitmap data
	SetFilePointer(file, bmpheader.bfOffBits, NULL, FILE_BEGIN);
	// read bmp data
	if (ReadFile(file, Buffer, size, &bytesread, NULL) == false) {
		delete[] Buffer;
		CloseHandle(file);
		return NULL;
	}
	// everything successful here: close file and return buffer
	CloseHandle(file);

	return Buffer;
}//LOADPMB

bool SaveBMP(BYTE* Buffer, int width, int height, long paddedsize, LPCTSTR bmpfile)
{
	// declare bmp structures 
	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER info;

	// andinitialize them to zero
	memset(&bmfh, 0, sizeof(BITMAPFILEHEADER));
	memset(&info, 0, sizeof(BITMAPINFOHEADER));

	// fill the fileheader with data
	bmfh.bfType = 0x4d42;       // 0x4d42 = 'BM'
	bmfh.bfReserved1 = 0;
	bmfh.bfReserved2 = 0;
	bmfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + paddedsize;
	bmfh.bfOffBits = 0x36;		// number of bytes to start of bitmap bits

								// fill the infoheader

	info.biSize = sizeof(BITMAPINFOHEADER);
	info.biWidth = width;
	info.biHeight = height;
	info.biPlanes = 1;			// we only have one bitplane
	info.biBitCount = 24;		// RGB mode is 24 bits
	info.biCompression = BI_RGB;
	info.biSizeImage = 0;		// can be 0 for 24 bit images
	info.biXPelsPerMeter = 0x0ec4;     // paint and PSP use this values
	info.biYPelsPerMeter = 0x0ec4;
	info.biClrUsed = 0;			// we are in RGB mode and have no palette
	info.biClrImportant = 0;    // all colors are important

								// now we open the file to write to
	HANDLE file = CreateFile(bmpfile, GENERIC_WRITE, FILE_SHARE_READ,
		NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (file == NULL) {
		CloseHandle(file);
		return false;
	}
	// write file header
	unsigned long bwritten;
	if (WriteFile(file, &bmfh, sizeof(BITMAPFILEHEADER), &bwritten, NULL) == false) {
		CloseHandle(file);
		return false;
	}
	// write infoheader
	if (WriteFile(file, &info, sizeof(BITMAPINFOHEADER), &bwritten, NULL) == false) {
		CloseHandle(file);
		return false;
	}
	// write image data
	if (WriteFile(file, Buffer, paddedsize, &bwritten, NULL) == false) {
		CloseHandle(file);
		return false;
	}

	// and close file
	CloseHandle(file);

	return true;
} // SaveBMP

BYTE* ConvertBMPToIntensity(BYTE* Buffer, int width, int height)
{

	// first make sure the parameters are valid
	if ((NULL == Buffer) || (width == 0) || (height == 0))
		return NULL;

	// find the number of padding bytes

	int padding = 0;
	int scanlinebytes = width * 3;
	while ((scanlinebytes + padding) % 4 != 0)     // DWORD = 4 bytes
		padding++;
	// get the padded scanline width
	int psw = scanlinebytes + padding;

	// create new buffer
	BYTE* newbuf = new BYTE[width*height];

	// now we loop trough all bytes of the original buffer, 
	// swap the R and B bytes and the scanlines
	long bufpos = 0;
	long newpos = 0;
	for (int row = 0; row < height; row++)
		for (int column = 0; column < width; column++) {
			newpos = row * width + column;
			bufpos = (height - row - 1) * psw + column * 3;
			newbuf[newpos] = BYTE(0.11*Buffer[bufpos + 2] + 0.59*Buffer[bufpos + 1] + 0.3*Buffer[bufpos]);
		}

	return newbuf;
}//ConvetBMPToIntensity

BYTE* ConvertIntensityToBMP(BYTE* Buffer, int width, int height, long% newsize)
{
	// first make sure the parameters are valid
	if ((NULL == Buffer) || (width == 0) || (height == 0))
		return NULL;

	// now we have to find with how many bytes
	// we have to pad for the next DWORD boundary	

	int padding = 0;
	int scanlinebytes = width * 3;
	while ((scanlinebytes + padding) % 4 != 0)     // DWORD = 4 bytes
		padding++;
	// get the padded scanline width
	int psw = scanlinebytes + padding;
	// we can already store the size of the new padded buffer
	newsize = height * psw;

	// and create new buffer
	BYTE* newbuf = new BYTE[newsize];

	// fill the buffer with zero bytes then we dont have to add
	// extra padding zero bytes later on
	memset(newbuf, 0, newsize);

	// now we loop trough all bytes of the original buffer, 
	// swap the R and B bytes and the scanlines
	long bufpos = 0;
	long newpos = 0;
	for (int row = 0; row < height; row++)
		for (int column = 0; column < width; column++) {
			bufpos = row * width + column;     // position in original buffer
			newpos = (height - row - 1) * psw + column * 3;           // position in padded buffer
			newbuf[newpos] = Buffer[bufpos];       //  blue
			newbuf[newpos + 1] = Buffer[bufpos];   //  green
			newbuf[newpos + 2] = Buffer[bufpos];   //  red
		}

	return newbuf;
} //ConvertIntensityToBMP

int *Histogram(BYTE* buffer, int width, int height)
{
	int *histogram = new int[256];

	for (unsigned int i = 0; i < 256; i++)
		histogram[i] = 0;

	for (unsigned int pos = 0; pos < width*height; pos++)
	{
		int t = buffer[pos];
		histogram[t]++;
	}

	return histogram;
}

BYTE* HistogramEqualization(BYTE* buffer, int width, int height)
{
	int numPixel = width * height;
	int maxValue = 255;
	int *histogram = Histogram(buffer, width, height);

	BYTE *t = new BYTE[width * height];
	for (int i = 0; i < width * height; i++)
		t[i] = BYTE(0);

	float sum = 0.0;
	for (int i = 0; i < 256; i++)
	{
		sum += histogram[i];
		int value = round((sum / numPixel) * maxValue);    // New Histogram Value
		if (histogram[i] > 0)
		{
			// Set Image New Histogram Value 
			for (int pos = 0; pos < width*height; pos++)
			{
				if (buffer[pos] == BYTE(i))
				{
					if (t[pos] == 0)
					{
						buffer[pos] = BYTE(value);
						t[pos] = BYTE(1);
					}
				}
			}
		}

	}
	delete t;
	return buffer;
}

BYTE* DigitalZoom(BYTE* Buffer, int width, int height)
{
	// Expansion Matrix: 2N+1 X 2N+1
	int h = 2 * height + 1;
	int w = 2 * width  + 1;

	// Convolution Mask Matrix
	float mask[9] = { 0.25, 0.5, 0.25,
		                0.5, 1, 0.5,
		                0.25, 0.5, 0.25 };

	// Expansion with Zero
	BYTE* tempBuffer = new BYTE[w * h];
	int i = 0;
	int flag = 0;
	for (unsigned int row = 0; row <h; row++)
	{
		for (unsigned int column = 0; column <w; column++)
		{
			int pos = row * w + column;
			if (row % 2 == 0)
			{
				tempBuffer[pos] = BYTE(0);
			}
			else
			{
				if (column == 0 || column == w - 1)
				{
					tempBuffer[pos] = BYTE(0);
					flag = 1;
				}
				else if (flag == 1)
				{
					tempBuffer[pos] = Buffer[i++];
					flag = 0;

				}
				else
				{
					tempBuffer[pos] = BYTE(0);
					flag = 1;

				}
			}
		}
	}

	// Convolution Mask Image: 2N-1 X 2N-1
	BYTE* tBuf = new BYTE[(h - 2)*(w - 2)];
	int sum = 0;
	int index = 0;

	for (int i = 0; i < h - 2; i++)
	{
		for (int j = 0; j < w - 2; j++)
		{
			int pos = -1;
			for (int k = 0; k < 3; k++)
			{
				for (int l = 0; l < 3; l++)
				{
					pos++;
					sum += tempBuffer[(i + k) * w + j + l] * mask[pos];
				}
			}
			tBuf[index++] = BYTE(sum);
			sum = 0;
		}
	}
	return tBuf;
}

BYTE* KMeansClustering(BYTE* buffer, int width, int height, int T11, int T22, int option)
{
	int *hist = new int[256];
	for (int i = 0; i < 256; i++)
		hist[i] = 0;
	for (int i = 0; i < width*height; i++)
		hist[buffer[i]]++;

	float T1 = 100, T2 = 151;
	float tempT1 = 0.0, tempT2 = 0.0;
	int *T1c = NULL, *T2c = NULL;
	int boyut1 = 0, boyut2 = 0;
	float variance1 = 100, variance2 = 200, tvariance1 = 0, tvariance2 = 0;

	// Euclidean Distance
	if (option == 0)
	{
		while (1)
		{
			for (int i = 0; i < 256; i++)
			{
				if (pow(i - T1, 2) <= pow(i - T2, 2))
				{
					if (T1c == NULL)
					{
						T1c = new int[boyut1 + 1];
						T1c[boyut1] = i;
						boyut1++;
					}
					else
					{
						int *t_T1c = new int[boyut1 + 1];
						for (int j = 0; j < boyut1; j++)
							t_T1c[j] = T1c[j];
						int *temp = T1c;
						delete[]temp;
						T1c = t_T1c;
						t_T1c = NULL;
						delete[]t_T1c;
						T1c[boyut1] = i;
						boyut1++;
					}
				}
				else
				{
					if (T2c == NULL)
					{
						T2c = new int[boyut2 + 1];
						T2c[boyut2] = i;
						boyut2++;
					}
					else
					{
						int *t_T2c = new int[boyut2 + 1];
						for (int j = 0; j < boyut2; j++)
							t_T2c[j] = T2c[j];
						int *temp = T2c;
						delete[]temp;
						T2c = t_T2c;
						t_T2c = NULL;
						delete[]t_T2c;
						T2c[boyut2] = i;
						boyut2++;
					}
				}
			}

			int sum = 0;
			int bolen = 0;
			for (int i = 0; i < boyut1; i++)
			{
				sum += T1c[i] * hist[T1c[i]];
				bolen += hist[T1c[i]];
			}

			tempT1 = (float)sum / bolen;

			sum = 0;
			bolen = 0;
			for (int i = 0; i < boyut2; i++)
			{
				sum += T2c[i] * hist[T2c[i]];
				bolen += hist[T2c[i]];
			}

			tempT2 = (float)sum / bolen;

			if (T1 == tempT1 && T2 == tempT2)
				break;
			else
			{
				int *temp = T1c;
				T1c = NULL;
				delete[]temp;
				int *temp1 = T2c;
				T2c = NULL;
				delete[]temp1;
				boyut1 = 0;
				boyut2 = 0;
				T1 = tempT1;
				T2 = tempT2;
			}
		}
	}

	// Mahalanobis Distance
	if (option == 1)
	{
		while (1)
		{
			for (int i = 0; i < 256; i++)
			{
				if ((pow(i - T1, 2) / variance1) <= (pow(i - T2, 2) / variance2))
				{
					if (T1c == NULL)
					{
						T1c = new int[boyut1 + 1];
						T1c[boyut1] = i;
						boyut1++;

					}
					else
					{
						int *t_T1c = new int[boyut1 + 1];
						for (int j = 0; j < boyut1; j++)
							t_T1c[j] = T1c[j];
						int *temp = T1c;
						delete[]temp;
						T1c = t_T1c;
						t_T1c = NULL;
						delete[]t_T1c;
						T1c[boyut1] = i;
						boyut1++;
					}
				}
				else
				{
					if (T2c == NULL)
					{
						T2c = new int[boyut2 + 1];
						T2c[boyut2] = i;
						boyut2++;
					}
					else
					{
						int *t_T2c = new int[boyut2 + 1];
						for (int j = 0; j < boyut2; j++)
							t_T2c[j] = T2c[j];
						int *temp = T2c;
						delete[]temp;
						T2c = t_T2c;
						t_T2c = NULL;
						delete[]t_T2c;
						T2c[boyut2] = i;
						boyut2++;
					}
				}
			}

			int sum = 0;
			int bolen = 0;
			for (int i = 0; i < boyut1; i++)
			{
				sum += T1c[i] * hist[T1c[i]];
				bolen += hist[T1c[i]];
			}
			tempT1 = (float)sum / bolen;


			sum = 0;
			bolen = 0;
			for (int i = 0; i < boyut2; i++)
			{
				sum += T2c[i] * hist[T2c[i]];
				bolen += hist[T2c[i]];
			}
			tempT2 = (float)sum / bolen;

			sum = 0;
			bolen = 0;
			for (int i = 0; i < boyut1; i++)
			{
				sum += pow(T1c[i] - tempT1, 2)*hist[T1c[i]];
				bolen += hist[T1c[i]];
			}
			tvariance1 = (float)sum / bolen;

			sum = 0;
			bolen = 0;
			for (int i = 0; i < boyut2; i++)
			{
				sum += pow(T2c[i] - tempT2, 2)*hist[T2c[i]];
				bolen += hist[T2c[i]];
			}
			tvariance2 = (float)sum / bolen;

			if (T1 == tempT1 && T2 == tempT2 && variance1 == tvariance1 && variance2 == tvariance2)
				break;
			else
			{
				int *temp = T1c;
				T1c = NULL;
				delete[]temp;
				int *temp1 = T2c;
				T2c = NULL;
				delete[]temp1;
				boyut1 = 0;
				boyut2 = 0;
				T1 = tempT1;
				T2 = tempT2;
				variance1 = tvariance1;
				variance2 = tvariance2;

			}
		}
	}
	for (int i = 0; i < width*height; i++)
	{
		if (pow(buffer[i] - T1, 2) <= pow(buffer[i] - T2, 2))
			buffer[i] = BYTE(T11);
		else
			buffer[i] = BYTE(T22);
	}

	return buffer;
}

BYTE* KMeansClusteringN(BYTE* buffer, int width, int height, int K)
{
	srand(time(NULL));

	int **C = new int *[K]; // kümeler
	int *S = new int[K];   // boyut
	float **T = new float *[K]; // t 
	float **tT = new float *[K];
	int **hist = new int *[3];

	hist[0] = new int[256]; // R;
	hist[1] = new int[256]; // G;
	hist[2] = new int[256]; // B;

	for (int i = 0; i < K; i++)
	{
		S[i] = 0;
	}
	for (int i = 0; i < K; i++)
	{
		C[i] = NULL;
	}

	for (int i = 0; i < K; i++)
	{
		T[i] = new float[3];
		tT[i] = new float[3];
	}

	for (int i = 0; i < K; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			T[i][j] = (float)(rand() % 256);
			tT[i][j] = 0;
		}
	}

	int bufPos = 0;
	while (1)
	{
		for (int r = 0; r < height; r++)
		{
			for (int c = 0; c < width; c++)
			{
				bufPos = r * width * 3 + c * 3;

				int k;
				double min = 9999999.0;
				double distance = 0.0;

				for (int i = 0; i < K; i++)
				{
					distance = sqrt(pow((int)buffer[bufPos] - T[i][0], 2) + pow((int)buffer[bufPos + 1] - T[i][1], 2) + pow((int)buffer[bufPos + 2] - T[i][2], 2));
					if (min > distance)
					{
						min = distance;
						k = i;
					}
				}
				if (C[k] == NULL)
				{
					C[k] = new int[S[k] + 1];
					C[k][S[k]] = bufPos;
					S[k]++;
				}
				else
				{
					int *tC = new int[S[k] + 1];
					for (int j = 0; j < S[k]; j++)
						tC[j] = C[k][j];

					int *temp = C[k];
					C[k] = tC;
					delete[]temp;
					tC = NULL;
					delete[]tC;
					C[k][S[k]] = bufPos;
					S[k]++;
				}
			}
		}
		for (int i = 0; i < K; i++)
		{
			for (int l = 0; l < 256; l++)
			{
				hist[0][l] = 0;
				hist[1][l] = 0;
				hist[2][l] = 0;
			}
			for (int j = 0; j < S[i]; j++)
			{
				hist[0][buffer[C[i][j]    ]]++;
				hist[1][buffer[C[i][j] + 1]]++;
				hist[2][buffer[C[i][j] + 2]]++;
			}

			float sum1 = 0, sum2 = 0, sum3 = 0;
			float bolen1 = 0, bolen2 = 0, bolen3 = 0;

			for (int k = 0; k < 256; k++)
			{
				bolen1 += hist[0][k];
				bolen2 += hist[1][k];
				bolen3 += hist[2][k];
				tT[i][0] += k * hist[0][k];
				tT[i][1] += k * hist[1][k];
				tT[i][2] += k * hist[2][k];
			}

			tT[i][0] /= bolen1;
			tT[i][1] /= bolen2;
			tT[i][2] /= bolen3;
		}

		int temp = 0;
		for (int i = 0; i < K; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (T[i][j] == tT[i][j])
					temp++;
			}
		}
		if (temp == K * 3)
		{
			break;
		}
		else
		{
			for (int i = 0; i < K; i++)
			{
				C[i] = NULL;
				S[i] = 0;
				for (int j = 0; j < 3; j++)
				{
					T[i][j] = tT[i][j];
					tT[i][j] = 0;
				}
			}

		}
	}
	int **RGB = new int *[K];
	for (int i = 0; i < K; i++)
		RGB[i] = new int[3];

	RGB[0][0] = 255;
	RGB[0][1] = 0;
	RGB[0][2] = 0;
	RGB[1][0] = 0;
	RGB[1][1] = 0;
	RGB[1][2] = 255;
	/*RGB[2][0] = 0;
	RGB[2][1] = 255;
	RGB[2][2] = 0;*/

	for (int i = 0; i < K; i++)
	{
		for (int j = 0; j < S[i]; j++)
		{
			buffer[C[i][j]] = BYTE(RGB[i][0]);
			buffer[C[i][j] + 1] = BYTE(RGB[i][1]);
			buffer[C[i][j] + 2] = BYTE(RGB[i][2]);
		}
	}
	
	return buffer;
}

BYTE* Dilation(BYTE* buffer, int width, int height, int iteration)
{
	int bufPos = 0;
	int dilationMask[9] = { 0,1,0,
							1,1,1,
							0,1,0 };
	int maskPos = 0;
	BYTE* tempBuffer = new BYTE[width*height];

	for (int a = 1; a <= iteration; a++)
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				bufPos = i * width + j;
				maskPos = 0;
				if (buffer[bufPos] == BYTE(255)) // Binary 1
				{
					for (int k = -1; k < 2; k++)
					{
						for (int l = -1; l < 2; l++)
						{
							if ((i + k) < 0 || (i + k) >= height || (j + l) < 0 || (j + l) >= width)
							{
								// empty
							}
							else
							{
								if (dilationMask[maskPos] == 1)
								{
									buffer[(i + k)*width + (j + l)] = BYTE(1);
								}

							}
							maskPos++;
						}
					}
				}


			}
		}
		for (int i = 0; i < height*width; i++)
			if (buffer[i] == BYTE(1))
				buffer[i] = BYTE(255);
	}

	return buffer;
}

BYTE* Erosion(BYTE* buffer, int width, int height, int iteration)
{
	int bufPos = 0;
	const int maskVal = 9;
	int erosionMask[maskVal] = { 1,1,1,
								0,1,0,
								1,1,1 };
	int flagSayisi = 0;
	for (int i = 0; i < maskVal; i++)
		if (erosionMask[i] == 1)
			flagSayisi++;

	int maskPos = 0;

	for (int a = 1; a <= iteration; a++)
	{
		for (int i = 0; i < height; i++)
		{

			for (int j = 0; j < width; j++)
			{

				int flag = 0;
				bufPos = i * width + j;
				maskPos = 0;
				if (buffer[bufPos] == BYTE(255)) // foreground -> Binary 1
				{
					for (int k = -1; k < 2; k++)
					{
						for (int l = -1; l < 2; l++)
						{
							if ((i + k) < 0 || (i + k) >= height || (j + l) < 0 || (j + l) >= width)
							{

							}
							else
							{
								if ((buffer[(i + k)*width + (j + l)] == BYTE(255) || buffer[(i + k)*width + (j + l)] == BYTE(1)) && erosionMask[maskPos] == 1)
								{
									flag++;
								}

							}
							maskPos++;
						}
					}
					if (flag == flagSayisi) // mask eþleme sayýsý eþit mi 1 birlerin sayýsýna yani maskýn origini ile image 1 olan kýsmý andliyoz tüm deðerler true flagSayisi 1 lerin sayýsý
					{
						maskPos = 0;
						for (int k = -1; k < 2; k++)
						{
							for (int l = -1; l < 2; l++)
							{
								if (maskPos == 4)
								{
									buffer[(i + k)*width + (j + l)] = BYTE(1); // etiket - foreground
								}

								maskPos++;
							}
						}
					}
				}
			}
		}
		for (int i = 0; i < height*width; i++)
		{
			if (buffer[i] == BYTE(1)) // sadece etiketlenmiþ kýsýmlar foreground
			{
				buffer[i] = BYTE(255);
			}
			else // kalan tüm degerleri background yap
				buffer[i] = BYTE(0);
		}
	}
	return buffer;
}

BYTE* Boundary(BYTE *buffer, int width, int height)
{
	BYTE* tBuffer = new BYTE[width*height];
	BYTE* bBuffer = new BYTE[width*height];


	for (int i = 0; i < width*height; i++)
	{
		tBuffer[i] = buffer[i];
	}

	BYTE *eBuffer = Erosion(buffer, width, height, 1);

	for (int i = 0; i < width*height; i++)
	{
		if ((int)tBuffer[i] - (int)eBuffer[i] > 0) // Bufferý Erosion Bufferýndan çýkarýyoz 
			bBuffer[i] = BYTE(255);
		else
			bBuffer[i] = BYTE(0);
	}

	return bBuffer;

}

BYTE* Opening(BYTE* buffer, int width, int height, int iteration)
{
	Erosion(buffer, width, height, iteration);
	Dilation(buffer, width, height, iteration);

	return buffer;
}

BYTE* Closinng(BYTE* buffer, int width, int height, int iteration)
{
	Dilation(buffer, width, height, iteration);
	Erosion(buffer, width, height, iteration);

	return buffer;
}

BYTE* ObjectDetect(BYTE* buffer, int width, int height, int %label)
{
	int etiket = 2;

	int *object = new int[width*height];
	for (int i = 0; i < height*width; i++)
	{
		if ((int)buffer[i] == 255)
			object[i] = 1;
		else
			object[i] = 0;
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (etiket == 99)
				etiket++;
			if ((int)buffer[i * width + j] == 255)
			{
				// (0,0)
				if (i == 0 && j == 0)
					object[i * width + j] = etiket++;
				// (0,j)
				else if (i == 0)
				{
					if (object[i * width + j - 1] != 0)
						object[i * width + j] = object[i * width + j - 1];
					else
						object[i * width + j] = etiket++;
				}

				// (i,0)
				else if (j == 0)
				{
					if (object[(i - 1) * width + j] != 0)
						object[i * width + j] = object[(i - 1) * width + j];
					else
						object[i * width + j] = etiket++;
				}
				// -----
				else
				{
					if (object[(i - 1) * width + j] == 0 && object[i* width + j - 1] == 0)
						object[i * width + j] = etiket++;
					else if (object[(i - 1) * width + j] == object[i* width + j - 1])
						object[i * width + j] = object[(i - 1) * width + j];
					else if (object[(i - 1) * width + j] != 0 && object[(i - 1) * width + j] != 'c' && object[i* width + j - 1] != 0 && object[i* width + j - 1] != 'c')
						object[i * width + j] = 'c';
					else if (object[(i - 1) * width + j] != 0 && object[i* width + j - 1] == 0)
						object[i * width + j] = object[(i - 1) * width + j];
					else if (object[i* width + j - 1] != 0 && object[(i - 1) * width + j] == 0)
						object[i * width + j] = object[i* width + j - 1];
					else if (object[i* width + j - 1] != 0 && object[(i - 1) * width + j] == 'c')
						object[i * width + j] = object[i* width + j - 1];
					else if (object[(i - 1)* width + j] != 0 && object[i * width + j - 1] == 'c')
						object[i * width + j] = object[(i - 1)* width + j];
				}

			}
		}

	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (object[i * width + j] == 'c')
			{

				if (object[(i - 1) * width + j] != 0 && object[(i - 1) * width + j]< object[i * width + j - 1])
				{
					object[i * width + j] = object[(i - 1) * width + j];
					int a = object[(i - 1) * width + j];
					int b = object[i * width + j - 1];

					for (int i = 0; i < height*width; i++)
					{
						if (object[i] == b)
							object[i] = a;
					}
				}
				else if (object[i * width + j - 1] != 0 && object[i * width + j - 1] < object[(i - 1) * width + j])
				{
					object[i * width + j] = object[i * width + j - 1];
					int a = object[(i - 1) * width + j];
					int b = object[i * width + j - 1];
					for (int i = 0; i < height*width; i++)
					{
						if (object[i] == a)
							object[i] = b;
					}
				}
				else
				{
					if (object[i * width + j - 1] != 0)
						object[i * width + j] = object[i * width + j - 1];
					else
						object[i * width + j] = object[(i - 1) * width + j];
				}
			}
		}
	}

	int *hist = new int[etiket];
	for (int i = 0; i < etiket; i++)
		hist[i] = 0;

	for (int i = 0; i < width*height; i++)
		hist[object[i]]++;

	label = 0;
	for (int i = 2; i < etiket; i++)
		if (hist[i] != 0)
			label++;

	int cmin = 99999, cmax = -99999;
	int rmin = 99999, rmax = -99999;
	for (int k = 2; k < etiket; k++)
	{
		int cmin = 99999, cmax = -99999;
		int rmin = 99999, rmax = -99999;
		if (hist[k] != 0)
		{
			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
				{
					if (object[i*width + j] == k)
					{
						if (cmin > j)
							cmin = j;
						else if (cmax < j)
							cmax = j;

						if (rmin > i)
							rmin = i;
						else if (rmax < i)
							rmax = i;
					}

				}
			}
			for (int m = rmin; m <= rmax; m++)
			{
				for (int n = cmin; n <= cmax; n++)
				{
					if (m == rmin || m == rmax)
						buffer[m*width + n] = BYTE(150);
					else
					{
						if (n == cmin || n == cmax)
							buffer[m*width + n] = BYTE(150);
					}
				}
			}
		}

	}
	return buffer;
}