#ifndef BONE_H
#define BONE_H

class Bone
{
	friend unsigned int whereBonesConnect(Bone vecBone, Bone playBone); //Returns the value of the side of the bone in the board that connects to the bone being played

public:
	Bone(); //Default bone constructor
	Bone(int val1, int val2); //Bone constructor
	unsigned int getValue1(); //Get the first value of the bone
	unsigned int getValue2(); //Get the second value of the bone
	void display(int x, int y); //Displays the spinner
	void display(int &x, int &y, char row); //Displays the bone
	void swap(); //Swaps the first value of the bone with it's second value
	bool isDouble(); //Returns true if the bone is a double or false if it isn't

private:
	unsigned int value1; //First value of the bone
	unsigned int value2; //Second value of the bone

};

bool operator==(Bone b1, Bone b2); //Returns true if the two given bones are the same

#endif
