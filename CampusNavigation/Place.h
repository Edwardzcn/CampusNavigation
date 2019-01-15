#pragma once
class Place
{
protected:
	//保护继承 坐标
	int x;
	int y;
	bool editable = false;
	Place* nextPlace = NULL;
	//缺少一个id。。
public:
	Place(int x,int y);
	void setPosition(int x, int y);
	~Place();
};

