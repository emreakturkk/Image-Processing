#include "stdafx.h"
#include <windows.h>
#include "imge_bmp.h"
#include <iostream>
#include <math.h>

#define PI 3.14159265

using namespace std;

BYTE* LoadBMP(int* width, int* height, long* size, LPCTSTR bmpfile)
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
	if (ReadFile(file, &bmpheader, sizeof (BITMAPFILEHEADER), &bytesread, NULL) == false)  {
		       CloseHandle(file);
		       return NULL;
	      }
	//read bitmap info
	if (ReadFile(file, &bmpinfo, sizeof (BITMAPINFOHEADER), &bytesread, NULL) == false) {
		        CloseHandle(file);
		        return NULL;
	      }
	// check if file is actually a bmp
	if (bmpheader.bfType != 'MB')  	{
		       CloseHandle(file);
		       return NULL;
	      }
	// get image measurements
	*width = bmpinfo.biWidth;
	*height = abs(bmpinfo.biHeight); // abs mutlak deðer

	// check if bmp is uncompressed
	if (bmpinfo.biCompression != BI_RGB)  {
		      CloseHandle(file);
		      return NULL;
	      }
	// check if we have 24 bit bmp
	if (bmpinfo.biBitCount != 24) {
		      CloseHandle(file);
		      return NULL;
	     }

	// create buffer to hold the data
	*size = bmpheader.bfSize - bmpheader.bfOffBits;
	BYTE* Buffer = new BYTE[*size];
	// move file pointer to start of bitmap data
	SetFilePointer(file, bmpheader.bfOffBits, NULL, FILE_BEGIN);
	// read bmp data
	if (ReadFile(file, Buffer, *size, &bytesread, NULL) == false)  {
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
	memset(&bmfh, 0, sizeof (BITMAPFILEHEADER));
	memset(&info, 0, sizeof (BITMAPINFOHEADER));

	// fill the fileheader with data
	bmfh.bfType = 0x4d42;       // 0x4d42 = 'BM'
	bmfh.bfReserved1 = 0;
	bmfh.bfReserved2 = 0;
	bmfh.bfSize = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+paddedsize;
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
	if (file == NULL)  	{
		    CloseHandle(file);
		    return false;
	   }
	// write file header
	unsigned long bwritten;
	if (WriteFile(file, &bmfh, sizeof (BITMAPFILEHEADER), &bwritten, NULL) == false)  {
		       CloseHandle(file);
		       return false;
	      }
	// write infoheader
	if (WriteFile(file, &info, sizeof (BITMAPINFOHEADER), &bwritten, NULL) == false)  {
		     CloseHandle(file);
		     return false;
	      }
	// write image data
	if (WriteFile(file, Buffer, paddedsize, &bwritten, NULL) == false)  {
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
	for (int column = 0; column < width; column++)  {
		      newpos = row * width + column;
		      bufpos = (height - row - 1) * psw + column * 3;
		      newbuf[newpos] = BYTE(0.11*Buffer[bufpos + 2] + 0.59*Buffer[bufpos + 1] + 0.3*Buffer[bufpos]);
	      }

	return newbuf;
}//ConvetBMPToIntensity

BYTE* ConvertIntensityToBMP(BYTE* Buffer, int width, int height, long* newsize)
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
	*newsize = height * psw;

	// and create new buffer
	BYTE* newbuf = new BYTE[*newsize];

	// fill the buffer with zero bytes then we dont have to add
	// extra padding zero bytes later on
	memset(newbuf, 0, *newsize);

	// now we loop trough all bytes of the original buffer, 
	// swap the R and B bytes and the scanlines
	long bufpos = 0;
	long newpos = 0;
	for (int row = 0; row < height; row++)
	for (int column = 0; column < width; column++)  	{
		bufpos = row * width + column;     // position in original buffer
		newpos = (height - row - 1) * psw + column * 3;           // position in padded buffer
		newbuf[newpos] = Buffer[bufpos];       //  blue
		newbuf[newpos + 1] = Buffer[bufpos];   //  green
		newbuf[newpos + 2] = Buffer[bufpos];   //  red
	}

	return newbuf;
} //ConvertIntensityToBMP


BYTE* KMeansClustering(BYTE* buffer, int width, int height)
{
	int *hist = new int[256];
	for (int i = 0; i < 256; i++)
		hist[i] = 0;
	for (int i = 0; i < width*height; i++)
		hist[buffer[i]]++;
	/*for (int i = 0; i < 256; i++)
		std::cout << i << "." << hist[i] << endl;*/

	int T1, T2, tempT1 = 0, tempT2 = 0;
	T1 = 6, T2 = 255;
	int *T1c = NULL, *T2c = NULL;
	int boyut1 = 0, boyut2 = 0;

	while (1)
	{
		// Yakýnlýk
		for (int i = 0; i < 256; i++)
		{
			if (abs(i - T1) <= abs(i - T2))
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
		// Agýrlýk 
		float sum = 0.0;
		for (int i = 0; i < boyut1; i++)
			sum += (float)T1c[i];
		tempT1 = (int)round(sum / (float)boyut1);

		sum = 0.0;
		for (int i = 0; i < boyut2; i++)
			sum += (float)T2c[i];
		tempT2 = (int)round(sum / (float)boyut2);

		if (T1 == tempT1 && T2 == tempT2 )
		{
			cout << T1 << endl;
			cout << T2 << endl;
			break;
		}
		else
		{
			cout << T1 << endl;
			cout << T2 << endl;
			cout << "-------" << endl;
			Sleep(700);
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


	int *array1 = new int[boyut1];
	int *array2 = new int[boyut2];
	int k = 0, l = 0;
	for (int i = 0; i <256; i++)
	{
		if (abs(i - T1) <= abs(i - T2))
		{

				array1[k] = i;
				k++;
		}
		else
		{
			array2[l] = i;
			l++;
		}
	}

	cout << "BOYUT1:" <<boyut1 <<endl;
	cout << "BOYUT2:" << boyut2 << endl;

	cout << "T1:" << T1 << endl;
	cout << "T2:" << T2 << endl;

	cout << "T1 Kumesi" << endl;
	for (int i= 0; i < boyut1; i++)
	{
		cout << array1[i] << "." << T1c[i] << endl;
	}
	
	cout << "T2 Kumesi" << endl;
	for (int i = 0; i < boyut2; i++)
	{
		cout << array2[i] << "." << T2c[i] << endl;
	}

	/*for(int k = 0; k<boyut1;k++)
		for (int i = 0; i < width*height; i++)
		{
			if (array1[k] == (int)buffer[i])
				buffer[i] = BYTE(255);
		}
	for (int k = 0; k<boyut2; k++)
		for (int i = 0; i < width*height; i++)
		{
			if (array2[k] == (int)buffer[i])
				buffer[i] = BYTE(0);
		}*/

	/*for (int i = 0; i < 256; i++)
		hist[i] = 0;
	for (int i = 0; i < width*height; i++)
		hist[buffer[i]]++;
	for (int i = 0; i < 256; i++)
		std::cout << i << "." << hist[i] << endl;*/

	return buffer;
}