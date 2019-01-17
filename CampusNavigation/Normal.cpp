#include "Normal.h"



Normal::Normal(int x, int y, bool edit) :Place(x, y)
{
	this->editable = edit;
}

void Normal::rest(int x, int y)
{
	this->setPosition(x, y);
}

void Normal::show()
{
}


Normal::~Normal()
{
}
