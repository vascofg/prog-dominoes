#include "Bone.h"
#include "genericFunctions.h"

using namespace std;


Bone::Bone() //Default bone constructor
{
	value1 = 7;
	value2 = 7;
}


Bone::Bone(int val1, int val2) //Bone constructor
{
	value1 = val1;
	value2 = val2;
}


unsigned int Bone::getValue1() //Get the first value of the bone
{
	return value1;
}


unsigned int Bone::getValue2() //Get the second value of the bone
{
	return value2;
}

bool operator==(Bone b1, Bone b2) //Returns true if the two given bones are the same
{
	return (b1.getValue1() == b2.getValue1() && b1.getValue2() == b2.getValue2());
}

void Bone::display(int x, int y) //Displays the spinner
{
	gotoxy(x+1,y);
	cout << getValue1() << (char)179 << getValue2();
}

void Bone::display(int &x, int &y, char row) //Displays the bone
{
	setcolor(WHITE);
	if (toupper(row) == 'E' || toupper(row) == 'W')
		if (isDouble())
		{                       //if it's a double on the left or right row
			gotoxy(x,y-2);
			cout << ' ';
			gotoxy(x,y-1);
			cout << value1;
			gotoxy(x,y);
			cout << (char)196;
			gotoxy(x,y+1);
			cout << value1;
			gotoxy(x,y+2);
			cout << ' ';
			if (toupper(row) == 'E')
				x = x + 2;
			else
				x = x - 2;
		}
		else if (toupper(row) == 'E')
		{                       //if it's not a double and it is on the rigth row
			gotoxy(x,y);
			cout << value1;
			cout << (char)179;
			cout << value2;
			cout << ' ';
			x = x + 4;
		}
		else					//if it's not a double and it is on the left row
		{
			gotoxy(x,y);
			cout << value1;
			gotoxy(x-1,y);
			cout << (char)179;
			gotoxy(x-2,y);
			cout << value2;
			gotoxy(x-3,y);
			cout << ' ';
			x = x - 4;
		}
	else
		if (isDouble())        //if it's a double on the top or bottom row
		{
			gotoxy(x-2,y);
			cout << ' ';
			cout << value1;
			cout << (char)179;
			cout << value1;
			cout << ' ';
			if (toupper(row) == 'N')
				y = y - 2;
			else
				y = y + 2;
		}
		else if (toupper(row) == 'S')
		{					   //if it's not a double and it is on the bottom row
			gotoxy(x,y);
			cout << value1;
			gotoxy(x,y+1);
			cout << (char)196;
			gotoxy(x,y+2);
			cout << value2;
			gotoxy(x,y+3);
			cout << ' ';
			y = y + 4;
		}
		else
		{					   //if it's not a double and it is on the bottom row
			gotoxy(x,y);
			cout << value1;
			gotoxy(x,y-1);
			cout << (char)196;
			gotoxy(x,y-2);
			cout << value2;			
			gotoxy(x,y-3);
			cout << ' ';
			y = y - 4;
		}
	setcolor(GREEN);
}


bool Bone::isDouble() //Returns true if the bone is a double or false if it isn't
{
	if (value1 == value2)
		return true;
	else
		return false;
}

void Bone::swap() //Swaps the first value of the bone with it's second value
{
	unsigned int temp = value1;
	value1 = value2;
	value2 = temp;
}

unsigned int whereBonesConnect(Bone vecBone, Bone playBone) //Returns the value of the side of the bone in the board that connects to the bone being played
{
	if (vecBone.getValue1() == 7)
		return playBone.getValue2();

	if (vecBone.getValue2() == playBone.getValue1() || vecBone.getValue2() == playBone.getValue2())
		return vecBone.getValue2();

	return 7;
}