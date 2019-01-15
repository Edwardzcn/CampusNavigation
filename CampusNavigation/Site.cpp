#include "Site.h"


Site::Site(int x, int y, std::string name, std::string info, bool edit) :Place(x, y)
{
	this->editable = edit;
	this->siName = name;
	this->siInfo = info;
}

Site::~Site()
{
}
