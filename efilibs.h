// UEFI From Scratch for AARCH64 - ThatOSDev ( 2024 )
// https://github.com/ThatOSDev/EFI_AARCH64

#ifndef EFILIBS_H
#define EFILIBS_H

#include "clib.h"

#define MAX_LENGTH 22

             // ARGB             
#define ORANGE 0xffffa500
#define CYAN   0xff00ffff
#define RED    0xffff0000
#define GREEN  0xff00ff00
#define BLUE   0xff0000ff
#define GRAY   0xff888888
#define WHITE  0xffffffff
#define BLACK  0xff000000

EFI_HANDLE                       ImageHandle;
EFI_SYSTEM_TABLE                *SystemTable;
EFI_STATUS                       ERROR_STATUS;
EFI_GRAPHICS_OUTPUT_PROTOCOL    *gop;
EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *Volume;
EFI_FILE_PROTOCOL               *RootFS;
EFI_GRAPHICS_OUTPUT_BLT_PIXEL    GraphicsColor;  // Public Variable for now.

uint32_t DisplayWidth  = 0;
uint32_t DisplayHeight = 0;

typedef struct {
	uint32_t cols;  // Left / Right
	uint32_t rows;  // Up / Down
} Timer_Context;

EFI_EVENT timer_event;

// From the GNU-EFI
int64_t RtCompareGuid(EFI_GUID* Guid1, EFI_GUID* Guid2)
{
    int32_t *g1, *g2, r;
    g1 = (int32_t *) Guid1;
    g2 = (int32_t *) Guid2;
    r  = g1[0] - g2[0];
    r |= g1[1] - g2[1];
    r |= g1[2] - g2[2];
    r |= g1[3] - g2[3];
    return r;
}

int64_t CompareGuid(EFI_GUID* Guid1, EFI_GUID* Guid2)
{
    return RtCompareGuid (Guid1, Guid2);
}

void SetTextPosition(UINT32 Col, UINT32 Row)
{
    // Sets the Column and Row of the text screen cursor position.
    SystemTable->ConOut->SetCursorPosition(SystemTable->ConOut, Col, Row);
}

void ResetScreen(void)
{
    // This resets the whole console ( A.K.A. your display screen ) interface.
    SystemTable->ConOut->Reset(SystemTable->ConOut, 1);
}

void ClearScreen(void)
{
    // This clears the screen buffer, but does not reset it.
    SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
}

void printUInt64Digits(uint64_t num, uint64_t base)
{
    CHAR16 uint64Str[MAX_LENGTH] = {'\0'};
	
	const CHAR16* digits = u"0123456789ABCDEF";
	uint64_t i = 0;

	do
	{
		uint64Str[i++] = digits[num % base];
        num /= base;
	} while(num > 0);
	
    uint64Str[i--] = '\0';
	
	for(uint64_t j = 0; j < i; j++, i--)
	{
		CHAR16 temp = uint64Str[i];
		uint64Str[i]  = uint64Str[j];
		uint64Str[j]  = temp;
	}
	
	SystemTable->ConOut->OutputString(SystemTable->ConOut, uint64Str);
}

void printIntDigits(int32_t num)
{
    CHAR16 int32Str[12] = {'\0'};
	
	const CHAR16* digits = u"0123456789";
	uint64_t i = 0;
	int negative = (num < 0);
	if(negative) {num = -num;}
	
	do
	{
		int32Str[i++] = digits[num % 10];
		num /= 10;
	} while(num > 0);
	
	if(negative) {int32Str[i++] = '-';}
	
	int32Str[i--] = '\0';
	
	for(uint64_t j = 0; j < i; j++, i--)
	{
		CHAR16 temp = int32Str[i];
		int32Str[i] = int32Str[j];
		int32Str[j] = temp;
	}
	
	SystemTable->ConOut->OutputString(SystemTable->ConOut, int32Str);
}

void wprintf(CHAR16* txt, ...)
{
	CHAR16 charStr[2]   = {'\0'};

	va_list args;
	va_start(args, txt);
	
	for(uint64_t i = 0; txt[i] != '\0'; i++)
	{
		if(txt[i] == '%')
		{
			i++;
			switch(txt[i])
			{
                case 'c': {
                    charStr[0] = (CHAR16)va_arg(args, int);
                    SystemTable->ConOut->OutputString(SystemTable->ConOut, charStr);
					break;
                }
				case 's':
				{
					uint16_t* varString = va_arg(args, uint16_t*);
					SystemTable->ConOut->OutputString(SystemTable->ConOut, varString);
					break;
				}
				case 'd':
				{
					int32_t number = va_arg(args, int32_t);
					printIntDigits(number);
					break;
				}
                case 'b':
				{
					uint64_t bin = va_arg(args, uint64_t);
					printUInt64Digits(bin, 2);
					break;
                }
				case 'x':
				{
					uint64_t hex = va_arg(args, uint64_t);
					printUInt64Digits(hex, 16);
					break;
				}
				case 'l':
				{
					if(txt[i+1] == 'l' && txt[i+2] == 'u')
					{
						i+=2;
                        uint64_t num = va_arg(args, uint64_t);
						printUInt64Digits(num, 10);
					}
					break;
				}

				default:
				{
					SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_RED);
				    SystemTable->ConOut->OutputString(SystemTable->ConOut, u"\r\nERROR : Invalid format: %");
					SystemTable->ConOut->OutputString(SystemTable->ConOut, &txt[i]);
					SystemTable->ConOut->OutputString(SystemTable->ConOut, u"\r\n");
					return;
					break;
				}
			}
		} else {
			charStr[0] = txt[i];
			charStr[1] = '\0';
			SystemTable->ConOut->OutputString(SystemTable->ConOut, charStr);
		}
	}

	va_end(args);
}

void HitAnyKey(void)
{
    // This clears the keyboard buffer.
    SystemTable->ConIn->Reset(SystemTable->ConIn, 1);

    // We setup the struct to take keyboard input.
    EFI_INPUT_KEY Key;

    // In a while loop to see if the keyboard has a key stroke in the buffer.
	// Added the __asm__("wfi\n\t"); code to slow the CPU down.
    while((SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &Key)) == EFI_NOT_READY) {__asm__("wfi\n\t");};
}

void Delay(uint64_t d)
{
    // The Stall function is set as microseconds.
    SystemTable->BootServices->Stall(d);
}

void SetTextColor(uint64_t color)
{
	SystemTable->ConOut->SetAttribute(SystemTable->ConOut, color);
}

// This sets the color of the pixels ( Graphics Color )
void SetGraphicsColor(UINT32 color)
{
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL GColor;
    GColor.Reserved = color >> 24;
    GColor.Red      = color >> 16;
    GColor.Green    = color >> 8;
    GColor.Blue     = color;
    GraphicsColor = GColor;
}

// This positions the pixel in the row and column ( X and Y )
void SetPixel(UINT32 xPos, UINT32 yPos)
{
    // TODO : Add in a choice instead of defaulting to EfiBltVideoFill.
    gop->Blt(gop, &GraphicsColor, EfiBltVideoFill, 0, 0, xPos, yPos, 1, 1, 0);
}

// This creates a filled box of pixels.
// NOTE : Call SetGraphicsColor prior to using this function.
void CreateFilledBox(UINT32 xPos, UINT32 yPos, UINT32 w, UINT32 h)
{
    // TODO : Add in a choice instead of defaulting to EfiBltVideoFill.
    gop->Blt(gop, &GraphicsColor, EfiBltVideoFill, 0, 0, xPos, yPos, w, h, 0);
}

void InitEFI(EFI_HANDLE handle, EFI_SYSTEM_TABLE  *table)
{
	ImageHandle   = handle;
	SystemTable   = table;
	ERROR_STATUS  = 0;
	ResetScreen();
	SetTextColor(EFI_GREEN);
}

#endif // EFILIBS_H
