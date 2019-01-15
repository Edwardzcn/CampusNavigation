#include "Building.h"


Building::Building(int x, int y, std::string name, std::string info, std::string addr, std::string tel, bool edit) :Place(x, y)
{
	this->editable = edit;
	this->buName = name;
	this->buInfo = info;
	this->buAddress = addr;
	this->buTel = tel;
}

void Building::reset(int x, int y, std::string name, std::string info, std::string addr, std::string tel, bool edit)
{
	this->setPosition(x, y);
	this->buName = name;
	this->buInfo = info;
	this->buAddress = addr;
	this->buTel = tel;
	this->editable = edit;
}

void Building::show()
{
}

Building::~Building()
{
}
