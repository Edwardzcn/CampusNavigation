#pragma once
#include "Place.h"
class Normal :
	public Place
{
public:
	Normal(int x, int y, bool edit);
	void rest(int x, int y);
	void show();
	virtual ~Normal();
};

