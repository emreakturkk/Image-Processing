#pragma once
#include <windows.h>

BYTE* LoadBMP(int% width, int% height, long% size, LPCTSTR bmpfile);
BYTE* ConvertBMPToIntensity(BYTE* Buffer, int width, int height);
BYTE* DigitalZoom(BYTE* Buffer, int width, int height );
int *Histogram(BYTE* buffer, int width, int height);
BYTE* Stretch(BYTE* Buffer, int width, int height);