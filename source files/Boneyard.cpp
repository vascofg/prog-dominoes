#include <cstdlib>
#include "Boneyard.h"
#include "genericFunctions.h"


Boneyard::Boneyard() //Default constructor for the Boneyard class
{
	for (int i = 0; i <= 6; i++)
	{
		for (int k = i; k <= 6; k++)
		{
			Bone tempBone(i,k);
			availableBones.push_back(tempBone);
		}
	}
	random_shuffle(availableBones.begin(), availableBones.end());

	
	/*for (int i = 0; i <= 2; i++)
	{
		for (int k = i; k <= 6; k++)
		{
			Bone tempBone;
			if (i == 2)
				tempBone = Bone(1,6);
			else
				tempBone = Bone(1,2);
			availableBones.push_back(tempBone);
		}
	}*/
}

void Boneyard::displayNumBones() //Outputs the result of getNumAvailableBones
{
	setcolor(GREEN);
	gotoxy(93,53);
	int a = getNumAvailableBones();
	cout << "Boneyard has ";
	if (a < 10)
		cout << ' ';
	cout << a << " bones left.";
	setcolor(GREEN);
}
int Boneyard::getNumAvailableBones() //Gets the number of available bones in the boneyard
{
	return availableBones.size();
}


Bone Boneyard::takeBone() //Gets a bone from the boneyard
{
	random_shuffle(availableBones.begin(), availableBones.end());
	size_t vlen = availableBones.size();
	int k = rand() % vlen;
	Bone tempBone = availableBones[k];
	removeFromVector(availableBones, k);
	return tempBone;
}


bool Boneyard::isEmpty() //Returns true if the boneyard is empty and false if it isn't
{
	if (availableBones.size() == 0)
		return true;
	else
		return false;
}