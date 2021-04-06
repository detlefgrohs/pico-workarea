#include <iostream>
#include <string>
#include <tuple>

#include "Header.h"

FONT_INFO fontInfo = firaCode_16ptFontInfo;

int displayWidth = 240;
int displayHeight = 135;
char* display = new char[displayWidth * displayHeight];

void clearDisplay() {
	for (int x = 0; x < displayWidth; x++)
		for (int y = 0; y < displayHeight; y++)
			display[x + (y * displayWidth)] = '.';
}
void getLine() {
	std::string s;
	std::getline(std::cin, s);
}

void setDisplayPixel(Position position, char value) {
	display[position.X + (position.Y * displayWidth)] = value;
}

void printDisplay() {
	for (int y = 0; y < displayHeight; y++) {
		for (int x = 0; x < displayWidth; x++)
			std::cout << display[x + (y * displayWidth)];
		std::cout << "\n";
	}
}

Position drawCharacter(Position position, char character) {
	if (character == ' ') return {(uint_16)(2 + position.X + fontInfo.spacePixels), position.Y };
	if (character > fontInfo.endChar) return { position.X, position.Y };

	int chPos = character - fontInfo.startChar;

	uint_8 widthBits = fontInfo.charInfo[chPos].widthBits;
	uint_8 heightBits = fontInfo.charInfo[chPos].heightBits;
	uint_16 offset = fontInfo.charInfo[chPos].offset;
	uint_8 rowSize = ((widthBits - 1) / 8) + 1;

	for (uint_16 bitmapY = 0; bitmapY < heightBits; bitmapY++)
		for (uint_16 bitmapX = 0; bitmapX < widthBits; bitmapX++) {
			uint_16 fondDataOffset = offset + ((bitmapX >> 3) + (bitmapY * rowSize));
			uint_8 fontData = fontInfo.data[fondDataOffset];
			uint_8 pixel = (fontData >> (7 - (bitmapX & 0b00000111))) & 0b00000001;
			if (pixel)
				setDisplayPixel({ (uint_16)(position.X + 1 + bitmapX), (uint_16)(position.Y + bitmapY) }, 'O');
		}
	return { (uint_16)(position.X + widthBits + 2), position.Y };
}

Position drawText(Position position, std::string text) {
	for (std::string::iterator it = text.begin(); it != text.end(); ++it)
		position = drawCharacter(position, *it);
	return position;
}

int main() {
	clearDisplay();

	drawText({ 0, 0 }, "0123456789");

	drawText({ 0, fontInfo.heightPages }, "Hello World!");

	drawText({ 0, (uint_16)(2 * fontInfo.heightPages) }, "Wt=0000.0g");

	printDisplay();

	getLine();
}