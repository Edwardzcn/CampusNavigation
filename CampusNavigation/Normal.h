#pragma once
#include "Place.h"
class Normal :
	public Place
{
public:
	Normal(int x, int y);
	void rest(int x, int y);
	void show();
	virtual ~Normal();
};

