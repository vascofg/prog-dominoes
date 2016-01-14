#include <iostream>
#include <string>
#include <sstream>
#include "checkos.h"

#ifndef WIN32  //if the system is not Windows

#include <termios.h>
#include <unistd.h>
#include <stdio.h>

using namespace std;	

int _getch(void)			//We searched the web for this definition for _getch in unix Operative Systems
{
struct termios oldt,
newt;
int ch;
tcgetattr( STDIN_FILENO, &oldt );
newt = oldt;
newt.c_lflag &= ~( ICANON | ECHO );
tcsetattr( STDIN_FILENO, TCSANOW, &newt );
ch = getchar();
tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
return ch;
}
// Some functions that change display graphics for the Linux/Unix operating system
// using ANSI escape sequences
// - clear screen
// - set foreground color
// - control cursor position
//
// ANSI ESCAPE SEQUENCES (for more information see):
// - http://ascii-table.com/ansi-escape-sequences.php
//
// ALTERNATIVE SOLUTION (use ncurses library):
// - http://www.tldp.org/HOWTO/NCURSES-Programming-HOWTO/
//
// JAS - Abr/2011
//================================================================================

string int_to_string(int n) //Converts an integer to a string
{  
	ostringstream outstr;
	outstr << n;
	return outstr.str();
}

//======================================================================
void clrscr() //Clears the screen
{
	cout << "\033[2J";
		cout.flush();
}

//======================================================================
void gotoxy(int x, int y) //Sets the cursor position at coordinates X, Y
{
	cout << "\033[" << y << ";" << x << "f";
	cout.flush();
}


//======================================================================
/*
Foreground colors  
30 Black  
31 Red  
32 Green  
33 Yellow  
34 Blue  
35 Magenta  
36 Cyan  
37 White
*/

void setcolor(unsigned int color) //Sets the text color
{
	cout << "\033[0;"+int_to_string(color)+"m";
	cout.flush();
}
void setBackGroundColor(int code) //Sets the background color
{	
	switch(code)
	{
	case 37:
		cout << "\033[0;47;30m";
		break;
	case 30:
		cout << "\033[0;40;37m";
		break;
	}
	cout.flush();
}
void resizeConsole() //Resizes the console (NOT WORKING ON GNOME-TERMINAL)
{
	cout << "\033[=6h";
	cout.flush();
}

#else

void setBackGroundColor(int code) //Sets the background color
{
    HANDLE hOut;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	switch (code)
	{
	case 15:
		SetConsoleTextAttribute(hOut, BACKGROUND_RED |\
			BACKGROUND_GREEN |\
			BACKGROUND_BLUE |\
			BACKGROUND_INTENSITY);
		break;
	case 30:
		SetConsoleTextAttribute(hOut, FOREGROUND_RED |\
			FOREGROUND_GREEN |\
			FOREGROUND_BLUE | 0);
		break;
	case 10:
		SetConsoleTextAttribute(hOut, BACKGROUND_GREEN |\
			BACKGROUND_INTENSITY);
		break;
	case 9:
		SetConsoleTextAttribute(hOut, BACKGROUND_BLUE |\
			BACKGROUND_INTENSITY);

	}
	return;
}
void clrscr(void) //Clears the screen
{
	COORD upperLeftCorner = {0,0};
	DWORD charsWritten;
	DWORD conSize;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO  csbi;

	GetConsoleScreenBufferInfo(hCon, &csbi);
	conSize = csbi.dwSize.X * csbi.dwSize.Y;

	// fill with spaces
	FillConsoleOutputCharacter(hCon, TEXT(' '), conSize, upperLeftCorner, &charsWritten);
	GetConsoleScreenBufferInfo(hCon, &csbi);
	FillConsoleOutputAttribute(hCon, csbi.wAttributes, conSize, upperLeftCorner, &charsWritten);

	// cursor to upper left corner
	SetConsoleCursorPosition(hCon, upperLeftCorner);
}

void gotoxy(int x, int y) //Sets the cursor position at coordinates X, Y
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//================================================================================
/* 
COLOR CODES:
1   blue
2   green
3   cyan
4   red
5   magenta
6   brown
7   lightgray
8   darkgray
9   lightblue
10  lightgreen
11  lightcyan
12  lightred
13  lightmagenta
14  yellow
15  white
*/
void setcolor(unsigned int color) //Sets the text color
{                                    
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon,color);
}  

/*//*================================================================================*/


void resizeConsole() //Resizes the output terminal window
{
    HANDLE hOut;
    COORD NewSBSize;
    SMALL_RECT DisplayArea = {0, 0, 0, 0};

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    NewSBSize.X = 121;
	NewSBSize.Y = 60;

    SetConsoleScreenBufferSize(hOut,
                               NewSBSize);

   DisplayArea.Right = NewSBSize.X - 1;
    DisplayArea.Bottom = NewSBSize.Y - 1;

   SetConsoleWindowInfo(hOut,
                         TRUE,
                         &DisplayArea);
}
#endif
