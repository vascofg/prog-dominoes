#ifndef BONEYARD_H
#define BONEYARD_H

#include "Bone.h"
#include <vector>

using namespace std;

class Boneyard
{

public:
	Boneyard(); //Default constructor for the Boneyard class
	int getNumAvailableBones(); //Gets the number of available bones in the boneyard
	void displayNumBones(); //Outputs the result of getNumAvailableBones
	Bone takeBone(); //Gets a bone from the boneyard
	bool isEmpty(); //Returns true if the boneyard is empty and false if it isn't

private:
	vector<Bone> availableBones; //Vector of bones that contains the available bones in the boneyard

};
#endif
