#include"controlCon.h"
#include<windows.h>
#include<iostream>
#include<wincon.h>
void SetConsoleSize(int Width, int Height)
{
	COORD coord;
	coord.X = Width;
	coord.Y = Height;

	SMALL_RECT Rect;
	Rect.Top = 0;//���W����y
	Rect.Left = 0;//���W����x
	Rect.Bottom = Height - 1;//�k�U����y
	Rect.Right = Width - 1;//�k�U����x

	// Get handle of the standard output 
	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Handle)
	{
		std::cout << "Failure in getting the handle\n" << GetLastError();
		exit(EXIT_FAILURE);
	}

	//SetConsoleWindowInfo�MSetConsoleScreenBufferSize���ϥζ��ǡA�i��|�ɭP�@�Ǥ��i�w�������~!(�ϥ�try-catch�ѨM

	try{
		// Set the window size to that specified in Rect 
		if (!SetConsoleWindowInfo(Handle, TRUE, &Rect))
			throw GetLastError();

		// Set screen buffer size to that specified in coord 
		if (!SetConsoleScreenBufferSize(Handle, coord))
			throw GetLastError();

	}
	catch (const unsigned long& ErrorMessage){

		if (!SetConsoleScreenBufferSize(Handle, coord))
		{
			std::cout << "Failure in setting window size\n" << GetLastError();
			exit(EXIT_FAILURE);
		}


		if (!SetConsoleWindowInfo(Handle, TRUE, &Rect))
		{
			std::cout << "Failure in setting buffer size\n" << GetLastError();
			exit(EXIT_FAILURE);
		}
	}



}
void gotoXY(short x, short y)
{
	COORD coord;
	coord.X = x; coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/*
�_�I�y��(left_x,top_y)
���M���d�� area (�w�]0���d���i�ù�)
*/
void FillConsole(char ch /*= ' '*/, short left_x /* = 0 */, short top_y  /* = 0 */, unsigned int area /* = 0 */)
{
	COORD topLeft = { left_x, top_y };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);

	area = area ? area : screen.dwSize.X*screen.dwSize.Y;

	if (!FillConsoleOutputCharacter(
		console, ch, area, topLeft, &written
		))
	{
		std::cout << "Failure in clear console\n" << GetLastError();
		exit(EXIT_FAILURE);
	}

	if (!FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		area, topLeft, &written
		))
	{
		std::cout << "Failure in clear console\n" << GetLastError();
		exit(EXIT_FAILURE);

	}

	SetConsoleCursorPosition(console, topLeft);
}
void setCursorVisible(bool visible, HANDLE hConsole)
{
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = visible;
	cursor.dwSize = 1;
	SetConsoleCursorInfo(hConsole, &cursor);
}
