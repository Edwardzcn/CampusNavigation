#pragma once
#include "Place.h"
#include <string>
class Building :
	public Place
{
protected:
	std::string buName;
	std::string buInf;
	std::string buAddress;
	std::string buTel;
	//欠缺一个图片类
public:
	Building(int x,int y,std::string name,std::string inf,std::string addr,std::string tel,bool edit);
	~Building();
};

