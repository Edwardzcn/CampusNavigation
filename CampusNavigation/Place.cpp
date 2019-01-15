#include "Place.h"



Place::Place(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Place::getXY(int * outx, int * outy)
{
	*outx = this->x;
	*outy = this->y;
}

void Place::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Place::reset()
{
}

//void Place::show()
//{
//}

Place::~Place()
{
}
