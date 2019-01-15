#include "Site.h"


Site::Site(int x, int y, std::string name, std::string info, bool edit) :Place(x, y)
{
	this->editable = edit;
	this->siName = name;
	this->siInfo = info;
}

//void Site::reset(bool edit)
//{
//	this->editable = edit;
//}
//
//void Site::reset(int x, int y)
//{
//	this->setPosition(x, y);
//}
//
//void Site::siRreset(std::string name)
//{
//	this->siName = name;
//}
//
//void Site::reset(std::string name, std::string info)
//{
//	this->siName = name;
//	this->siInfo = info;
//}

void Site::reset(int x, int y, std::string name, std::string info, bool edit)
{
	this->setPosition(x, y);
	this->siName = name;
	this->siInfo = info;
	this->editable = edit;
}

void Site::show()
{

}

Site::~Site()
{

}
