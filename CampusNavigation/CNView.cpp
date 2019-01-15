#include "CNView.h"
#include <string>
#include <iostream>

using namespace std;

void Dijkstra(string X, string Y)
{
	string Name[6] = { "甲","乙","丙","丁","戊","己" };
	int x = 0, y = 0;
	int vexnum = 6;
	for (int i = 0; i < vexnum; i++)
	{
		if (X == Name[i])
		{
			x = i;
		}
		if (Y == Name[i])
		{
			y = i;
		}
	}
	D(x, y);
}


CNView::CNView()
{
}


CNView::~CNView()
{
}
