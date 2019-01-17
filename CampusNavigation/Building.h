#pragma once
#include "Place.h"
#include <string>
class Building :
	public Place
{
protected:
	//std::string buName;
	//std::string buInfo;
	//std::string buAddress;
	//std::string buTel;
	//欠缺一个图片类
public:
	std::string buName;
	std::string buInfo;
	std::string buAddress;
	std::string buTel;
	Building(int x,int y,std::string name,std::string info,std::string addr,std::string tel,bool edit);
	void reset(int x, int y, std::string name, std::string info, std::string addr, std::string tel, bool edit);
	void show();
	~Building();
};

