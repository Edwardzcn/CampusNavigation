#pragma once
#include "Place.h"
#include <string>
class Site :
	public Place
{
protected:
	std::string siName;
	std::string siInfo;
	//欠缺一个图片类
public:

	Site(int x,int y,std::string name,std::string info,bool edit);
	~Site();
};

