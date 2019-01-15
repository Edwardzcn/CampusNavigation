#include "Building.h"


Building::Building(int x, int y, std::string name, std::string inf, std::string addr, std::string tel, bool edit) :Place(x, y)
{
	this->editable = edit;
	this->buName = name;
	this->buInf = inf;
	this->buAddress = addr;
	this->buTel = tel;
}

Building::~Building()
{
}
