#ifndef __Tools__
#define __Tools__
#include <string>
#include <iostream>
#include <sstream>
#include <math.h>
#include <time.h>
#include "EasyBMP.h"
#include <assert.h>
#include "Constant.h"


using namespace std;

namespace Tools
{
	inline void draw(string *mystring)
	{
		/*for(int i=0; i<BLOCK_SIZE; i++)
		{
			
			std::cout << mystring[i] <<endl;
		}
		char a;
		std::cin >> a;*/
		BMP AnImage;
		// Set size to 640 × 480
		AnImage.SetSize(BLOCK_SIZE,BLOCK_SIZE);
		// Set its color depth to 32-bits
		AnImage.SetBitDepth(32);

		// Set one of the pixels
		for(int i=0;i<BLOCK_SIZE - 1;i++)
		{
			for(int j=0;j<BLOCK_SIZE - 1;j++)
			{
				if(mystring[i][j] != '-')
				{
					if(mystring[i][j] == 'H')
					{
						AnImage(i,j)->Red = 255;
						AnImage(i,j)->Green = 0;
						AnImage(i,j)->Blue = 0;
						AnImage(i,j)->Alpha = 0;
					}
					else if(mystring[i][j] == 'A')
					{
						AnImage(i,j)->Red = 0;
						AnImage(i,j)->Green = 255;
						AnImage(i,j)->Blue = 0;
						AnImage(i,j)->Alpha = 0;
					}
					else if(mystring[i][j] == 'B')
					{
						AnImage(i,j)->Red = 255;
						AnImage(i,j)->Green = 0;
						AnImage(i,j)->Blue = 255;
						AnImage(i,j)->Alpha = 0;
					}
					else if(mystring[i][j] == 'P')
					{
						AnImage(i,j)->Red = 0;
						AnImage(i,j)->Green = 0;
						AnImage(i,j)->Blue = 255;
						AnImage(i,j)->Alpha = 0;
					}
					else
					{
						AnImage(i,j)->Red = 0;
						AnImage(i,j)->Green = 0;
						AnImage(i,j)->Blue = 0;
						AnImage(i,j)->Alpha = 0;
					}
				}
				else
				{
					AnImage(i,j)->Red = 255;
					AnImage(i,j)->Green = 255;
					AnImage(i,j)->Blue = 255;
					AnImage(i,j)->Alpha = 0;
				}
			}
		}

		AnImage.WriteToFile("Output.bmp");
		cout << "image created";
	};
	static bool binitialized = false;
	inline int rng(int min,int max)
	{
		if(!binitialized)
		{
			binitialized = true;
			srand(time(NULL));
		}
		return ( rand() % (max + 1 - min) ) + min;
	};
	inline float round(float _f)
	{
		return floor(_f + 0.5f);
	};
}
#endif
