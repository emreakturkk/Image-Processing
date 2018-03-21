#include <Windows.h>
#include <math.h>

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

BYTE* DigitalZoom(BYTE* Buffer, int width, int height)
{
	int h = 2 * height + 1;
	int w = 2 * width + 1;
	int bufPos;
	int i = 0;
	int flag = 0;
	float matrix[9] = { 0, 0.5, 0,
						0.5, 1, 0.5,
						0, 0.5, 0 };

	BYTE* tempBuffer = new BYTE[w*h];
	
	for (unsigned int row = 0; row <h; row++)
	{
		for (unsigned int column = 0; column <w; column++)
		{
			bufPos = row * w + column;
			if (row % 2 == 0)
			{
				tempBuffer[bufPos] = BYTE(0);
			}
			else
			{
				if (column == 0 || column == w - 1)
				{
					tempBuffer[bufPos] = BYTE(0);
					flag = 1;
				}
				else if (flag == 1)
				{
					tempBuffer[bufPos] = Buffer[i++];
					flag = 0;
					
				}
				else
				{
					tempBuffer[bufPos] = BYTE(0);
					flag = 1;

				}
			}
		}
	}

	/*BYTE* tBuf = tempBuffer;
	int pos = 0, pos1 = 0;
	float sum = 0.0;
	int f = 0;
	int xx = 0, yy = 0;

	for (int row = 0; yy <= h - 2; row++)
	{
		for (int column = 0; xx <= w - 2; column++)
		{	
			pos = row * w + column;

			sum = 0;
			f = 0;
			for (int k = row; k < 3 + row; k++)
			{
				for (int l = column; l < 3 + column; l++)
				{
					pos1 = k * w + l;
					sum += (float)tBuf[pos1] * matrix[f];
					f++;
				}

			}
			xx++;
			buf[(row+1 * w) + column+1] = BYTE((int)round(sum));
		}
		yy++;
	}*/


	return tempBuffer;
}

int *Histogram(BYTE* buffer, int width, int height)
{
	int *histogram = new int[256];

	for (unsigned int i = 0; i < 256; i++)
		histogram[i] = 0;

	for (unsigned int pos = 0; pos <width*height; pos++)
	{
		int t = buffer[pos];
		histogram[t]++;
	}
	return histogram;
}

BYTE* Stretch(BYTE* Buffer, int width, int height)
{
	float Pixel = width * height; // Toplam pixel sayisi
	float level = 255; // Maksimum gri deðer seviyesi   
	int *stretch = new int[256]; // yeni seviye deðerleri
	BYTE* new_intensity = Buffer; // Yeni Y intensity pointerý

	int *histogram = Histogram(new_intensity, width, height);
	//sýfýrlama
	for (unsigned int i = 0; i < 256; i++)
		stretch[i] = 0;

	// Stretch islemi
	float sum = 0.0;
	for (unsigned int i = 0; i <= level; i++)
	{
		sum += histogram[i];
		stretch[i] = (int)round((sum / Pixel) *level);
	}

	for (unsigned int k = 0; k < 256; k++)
	{
		for (unsigned int pos = 0; pos < width*height; pos++)
		{
			if (new_intensity[pos] == (BYTE)k)
			{
				new_intensity[pos] = (BYTE)stretch[k];
			}
		}
	}
	return new_intensity;
}