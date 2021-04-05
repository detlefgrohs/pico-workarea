#pragma once

typedef unsigned char uint_8;
typedef unsigned short int uint_16;

// This structure describes a single character's display information
typedef struct
{
	const uint_8 widthBits;					// width, in bits (or pixels), of the character
	const uint_8 heightBits;
	const uint_16 offset;					// offset of the character's bitmap, in bytes, into the the FONT_INFO's data array

} FONT_CHAR_INFO;

// Describes a single font
typedef struct
{
	const uint_8 			heightPages;	// height, in pages (8 pixels), of the font's characters
	const uint_8 			startChar;		// the first character in the font (e.g. in charInfo and data)
	const uint_8 			endChar;		// the last character in the font
	const uint_8			spacePixels;	// number of pixels that a space character takes up
	const FONT_CHAR_INFO* charInfo;		// pointer to array of char information
	const uint_8* data;			// pointer to generated array of character visual representation

} FONT_INFO;

// Font data for Fira Code 16pt
extern const uint_8 firaCode_16ptBitmaps[];
extern const FONT_INFO firaCode_16ptFontInfo;
extern const FONT_CHAR_INFO firaCode_16ptDescriptors[];




