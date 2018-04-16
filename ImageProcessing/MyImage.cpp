#include <Windows.h>
#include <math.h>
#include "MyImage.h"

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
	float matrix[9] = { 0.25, 0.5, 0.25,
		0.5, 1, 0.5,
		0.25, 0.5, 0.25 };

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

	BYTE* tBuf = new BYTE[(h - 2)*(w - 2)];
	int sum = 0;
	int a = 0;

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
					sum += tempBuffer[(i + k)*w + j + l] * matrix[pos];

				}

			}
			tBuf[a++] = BYTE(sum);
			sum = 0;

		}
	}

	return tBuf;
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

BYTE* HistogramEqualization(BYTE* buffer, int width, int height)
{
	int pixel = width * height;
	int level = 255;
	int *stretch = new int[256];

	int *histogram = Histogram(buffer, width, height);
	//sýfýrlama
	for (unsigned int i = 0; i < 256; i++)
		stretch[i] = 0;

	// Stretch islemi
	float sum = 0.0;
	for (unsigned int i = 0; i <= level; i++)
	{
		sum += histogram[i];
		stretch[i] = (int)round((sum / pixel) *level);
	}

	for (unsigned int k = 0; k < 256; k++)
	{
		for (unsigned int pos = 0; pos < width*height; pos++)
		{
			if (buffer[pos] == BYTE(k))
			{
				buffer[pos] = BYTE(stretch[k]);
			}
		}
	}
	return buffer;
}

BYTE* KMeansClustering(BYTE* buffer, int width, int height, int option)
{
	int *hist = new int[256];
	for (int i = 0; i < 256; i++)
		hist[i] = 0;
	for (int i = 0; i < width*height; i++)
		hist[buffer[i]]++;

	float T1 = 100, T2 = 151;
	float tempT1 = 0.0, tempT2 = 0.0;
	int *T1c = NULL, *T2c = NULL; // T1 T2 clustering array
	int boyut1 = 0, boyut2 = 0;   // T1 T2 array size
	float variance1 = 100, variance2 = 200, tvariance1 = 0, tvariance2 = 0;

	// Euclidean Distance
	if (option == 0)
	{
		while (1)
		{
			// Yakýnlýk
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
			{
				break;
			}

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
			{
				break;
			}

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
			buffer[i] = BYTE(255);
		else
			buffer[i] = BYTE(0);
	}

	return buffer;
}

BYTE* KMeansClusteringN(BYTE* buffer, int width, int height)
{

	float T1 = 50, T2 = 200, T3 = 175;
	float tempT1 = 0.0, tempT2 = 0.0, tempT3 = 0.0;
	int *T1c = NULL, *T2c = NULL, *T3c = NULL; // T1 T2 clustrering array
	int boyut1 = 0, boyut2 = 0, boyut3 = 0;  // T1 T2 array size

	int **hist = NULL;
	hist = new int *[3];
	hist[0] = new int[256]; // R;
	hist[1] = new int[256]; // G;
	hist[2] = new int[256]; // B;
	for (int i = 0; i < 256; i++)
	{
		hist[0][i] = 0;
		hist[1][i] = 0;
		hist[2][i] = 0;
	}

	for (int i = 0; i < height*width * 3; i += 3)
	{
		hist[0][buffer[i]]++;
		hist[1][buffer[i + 1]]++;
		hist[2][buffer[i + 2]]++;
	}

	while (1)
	{
		// Yakýnlýk
		for (int i = 0; i < 256; i++)
		{
			if (pow(i - T1, 2) <= pow(i - T2, 2) && pow(i - T1, 2) <= pow(i - T3, 2))
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
			else if (pow(i - T2, 2) <= pow(i - T1, 2) && pow(i - T2, 2) <= pow(i - T3, 2))
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
			else
			{
				if (T3c == NULL)
				{
					T3c = new int[boyut3 + 1];
					T3c[boyut3] = i;
					boyut3++;
				}
				else
				{
					int *t_T3c = new int[boyut3 + 1];
					for (int j = 0; j < boyut3; j++)
						t_T3c[j] = T3c[j];
					int *temp = T3c;
					delete[]temp;
					T3c = t_T3c;
					t_T3c = NULL;
					delete[]t_T3c;
					T3c[boyut3] = i;
					boyut3++;
				}
			}
		}

	
		int sum = 0;
		int bolen = 0;
		for (int i = 0; i < boyut1; i++)
		{
			sum += T1c[i] * hist[0][T1c[i]];
			bolen += hist[0][T1c[i]];
		}

		tempT1 = (float)sum / bolen;

		sum = 0;
		bolen = 0;
		for (int i = 0; i < boyut2; i++)
		{
			sum += T2c[i] * hist[1][T2c[i]];
			bolen += hist[1][T2c[i]];
		}

		tempT2 = (float)sum / bolen;

		sum = 0;
		bolen = 0;
		for (int i = 0; i < boyut3; i++)
		{
			sum += T3c[i] * hist[2][T3c[i]];
			bolen += hist[2][T3c[i]];
		}

		tempT3 = (float)sum / bolen;

		if (T1 == tempT1 && T2 == tempT2 && T3 == tempT3)
		{
			break;
		}

		else
		{
			int *temp = T1c;
			T1c = NULL;
			delete[]temp;
			int *temp1 = T2c;
			T2c = NULL;
			delete[]temp1;
			int *temp2 = T3c;
			T3c = NULL;
			delete[]temp2;
			boyut1 = 0;
			boyut2 = 0;
			boyut3 = 0;
			T1 = tempT1;
			T2 = tempT2;
			T3 = tempT3;
		}
	}

	for (int i = 0; i < width*height * 3; i += 3)
	{
		if (pow(buffer[i] - T1, 2) <= pow(buffer[i] - T2, 2) && pow(buffer[i] - T1, 2) <= pow(buffer[i] - T3, 2))
			buffer[i] = BYTE(0);
	}
	for (int i = 0; i < width*height * 3; i += 3)
	{
		if (pow(buffer[i] - T2, 2) <= pow(buffer[i] - T1, 2) && pow(buffer[i] - T2, 2) <= pow(buffer[i] - T3, 2))
			buffer[i + 1] = BYTE(150);
	}
	for (int i = 0; i < width*height * 3; i += 3)
	{
		if (pow(buffer[i] - T3, 2) <= pow(buffer[i] - T1, 2) && pow(buffer[i] - T3, 2) <= pow(buffer[i] - T2, 2))
			buffer[i + 2] = BYTE(250);
	}

	return buffer;
}

BYTE* Dilation(BYTE* buffer, int width, int height, int iteration)
{
	int bufPos = 0;
	int dilationMask[9] = { 1,1,1,
							1,1,1,
							1,1,1 };
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
	int erosionMask[maskVal] =		{ 1,1,1,
									1,1,1,
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
									buffer[(i + k)*width + (j + l)] = BYTE(1); // etiket //foreground
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

BYTE* ObjectDetect(BYTE* buffer, int width, int height)
{
	int etiket = 1;
	int collesion = 254;
	BYTE* tBuffer = new  BYTE[width*height];
	for (int i = 0; i < height*width; i++)
	{
		tBuffer[i] = buffer[i];
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			cout << (int)buffer[i*width + j] << "\t";
		}
		cout << endl;
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{

			if ((int)buffer[i * width + j] == 0)
			{
				// (0,0)
				if (i - 1 < 0 && j - 1 < 0)
				{
					buffer[i * width + j] = BYTE(etiket++);

				}
				// (0,width-1)
				else if (i == 0)
				{
					int flag = 0;
					for (int k = 1; k <= etiket; k++)
					{
						if (buffer[i * width + j - 1] == k)
						{
							buffer[i * width + j] = BYTE(k);
							flag = 1;
						}
					}
					if (flag == 0)
						buffer[i * width + j] = BYTE(etiket++);
				}

				// (i,0)
				else if (j == 0)
				{
					int flag = 0;
					for (int k = 1; k <= etiket; k++)
					{
						if (buffer[(i - 1) * width + j] == k)
						{
							buffer[i * width + j] = BYTE(k);
							flag = 1;
						}

					}
					if (flag == 0)
						buffer[i * width + j] = BYTE(etiket++);
				}

				else
				{
					int flag = 0;
					for (int k = 1; k <= etiket; k++)
					{
						if (buffer[(i - 1) * width + j] == k || buffer[(i)* width + j - 1] == k)
						{
							flag++;
						}

					}
					if (flag == 0)
						buffer[i * width + j] = BYTE(etiket++);
					else if (flag == 1)
					{
						for (int k = 1; k <= etiket; k++)
							if (buffer[(i - 1) * width + j] == k || buffer[(i)* width + j - 1] == k)
								buffer[i * width + j] = BYTE(k);
					}
					else if (flag == 2)
					{
						buffer[i * width + j] = BYTE(collesion);
					}

				}

			}
		}

	}
	/*for (int i = 0; i < height; i++)
	{
	for (int j = 0; j < width; j++)
	{

	if ((int)buffer[i * width + j] == collesion)
	{

	if (buffer[(i - 1) * width + j] <= buffer[i* width + j - 1])
	{
	BYTE x = buffer[i* width + j - 1];
	BYTE y = buffer[(i - 1) * width + j];
	buffer[i * width + j] = y;

	for (int h = 0; h < height*width; h++)
	{
	if (buffer[h] == x)
	{
	buffer[h] = y;
	}
	}

	}
	else if (buffer[(i - 1) * width + j] > buffer[i* width + j - 1])
	{
	BYTE x = buffer[(i - 1) * width + j];
	BYTE y = buffer[i* width + j - 1];

	buffer[i * width + j] = y;
	for (int h = 0; h < height*width; h++)
	{
	if (buffer[h] == x)
	{
	buffer[h] = y;
	}
	}
	}

	}
	}
	}*/

	int *hist = new int[256];
	for (int i = 0; i < 256; i++)
		hist[i] = 0;
	for (int i = 0; i < width*height; i++)
		hist[buffer[i]]++;

	for (int i = 0; i < 256; i++)
		if (hist[i] != 0)
			cout << i << ". " << hist[i] << endl;

	cout << endl;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			cout << (int)buffer[i*width + j] << "\t";
		}
		cout << endl;
	}
	cout << "Nesne Sayisi: " << etiket - 1 << endl;
	return buffer;
}