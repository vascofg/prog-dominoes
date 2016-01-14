#ifndef CHECKOS_H
#define CHECKOS_H

void clrscr(void);

void resizeConsole();

void setBackGroundColor(int code);

void setcolor(unsigned int color);

void gotoxy(int x, int y);

#ifdef WIN32			//If OS is windows, _getch is defined in <conio.h>
#include <conio.h>		//Also the color codes for the text color are different
#include <Windows.h>

#define GRAY 7
#define RED 12
#define BLUE 9
#define YELLOW 14
#define WHITE 15
#define BLACK 30
#define GREEN 10
#define LBLUE 3

#else					//If OS is not windows, _getch will be defined in checkos.cpp

#define GRAY 37
#define RED 31
#define BLUE 34
#define YELLOW 33
#define WHITE 37
#define BLACK 30
#define GREEN 32
#define LBLUE 36

int _getch(void);	//__getch function prototype for Linux

#endif

#endif
