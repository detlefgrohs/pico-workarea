// EmbeddedFontWorkarea.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <tuple>


#include "Header.h"

FONT_INFO fontInfo = firaCode_16ptFontInfo;

int displayWidth = 240;//240;
int displayHeight = 135; //135;
char* display = new char[displayWidth * displayHeight];

void clearDisplay()
{
	for (int x = 0; x < displayWidth; x++)
		for (int y = 0; y < displayHeight; y++)
			display[x + (y * displayWidth)] = '.';
}

void setDisplayPixel(int x, int y, char val)
{
	display[x + (y * displayWidth)] = val;
}

void printDisplay()
{
	for (int y = 0; y < displayHeight; y++) {
		for (int x = 0; x < displayWidth; x++)
			std::cout << display[x + (y * displayWidth)];
		std::cout << "\n";
	}
}

void getLine()
{
	std::string s;
	std::getline(std::cin, s);
}

int drawCharacter(int x, int y, char ch)
{
	if (ch == ' ') return x + fontInfo.spacePixels + 2;
	if (ch > fontInfo.endChar) return x;
	
	int chPos = ch - fontInfo.startChar;

	uint_8 widthBits = fontInfo.charInfo[chPos].widthBits;
	uint_8 heightBits = fontInfo.charInfo[chPos].heightBits;
	uint_16 offset = fontInfo.charInfo[chPos].offset;
	uint_8 rowSize = ((widthBits - 1) / 8) + 1;

	for (uint_16 bitmapY = 0; bitmapY < heightBits; bitmapY++)
		for (uint_16 bitmapX = 0; bitmapX < widthBits; bitmapX++)
		{
			uint_16 fondDataOffset = offset + ((bitmapX >> 3) + (bitmapY * rowSize));
			uint_8 fontData = fontInfo.data[fondDataOffset];
			uint_8 pixel = (fontData >> (7 - (bitmapX & 0b00000111))) & 0b00000001;
			if (pixel)
				setDisplayPixel(x + 1 + bitmapX, y + bitmapY, 'O');
			//else
				//setDisplayPixel(x + 1 + bitmapX, y + bitmapY, ' ');
		}
	return x + widthBits + 2;
}

int drawText(int x, int y, std::string str)
{
	int maxY = 0;
	for (std::string::iterator it = str.begin(); it != str.end(); ++it)
	{
		x = drawCharacter(x, y, *it);
	}
	return x;
}

int main()
{
	clearDisplay();

	drawText(0, 0, "0123456789");

	drawText(0, fontInfo.heightPages, "Hello World!");

	drawText(0, fontInfo.heightPages * 2, "Wt=0000.0g");
	
	printDisplay();

	getLine();

	

	
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
