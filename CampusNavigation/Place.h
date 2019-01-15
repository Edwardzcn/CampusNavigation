#pragma once
class Place
{
protected:
	//保护继承 坐标
	int x;
	int y;
	bool editable = false;
	//Place* nextPlace = NULL;
	//缺少一个id。。
public:
	Place(int x,int y);
	void getXY(int *outx, int *outy);
	void setPosition(int x, int y);
	void reset();
	virtual void show() = 0;
	~Place();
};

