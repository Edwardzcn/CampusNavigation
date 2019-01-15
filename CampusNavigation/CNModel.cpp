#define DEBUGVEXNUM 10 //debug键值对数量（点数量）
#define DEBUGEDGENUM 23 //debug边数量
#define INF 0x3f3f3f3f
#define MDEBUG 

#include "CNModel.h"
#include <string>
#include <ctime>
#include <iostream>
#include <cstdlib>
//调试生成英文单词函数
std::string debugGetName() {
	debugGetName(-1);
}
std::string debugGetName(int len) {
	//参数为构造长度.
	int t = std::time(NULL);
	std::srand(t);
	if (len == -1) len = rand() % 5 + 5;
	int flag0;
	std::string temp(len, '$');
	for (int i = 0; i < len; i++) {
		if (rand() % 2 == 0) {
			temp[i] = 'A' + rand() % 26;
		}
		else {
			temp[i] = 'a' + rand() % 26;
		}
	}
	return temp;
}

Node *addNode()
{
	Node *cur = (Node*)malloc(sizeof(Node));
	if (cur == NULL)
	{
		printf("malloc failed!\n");
		exit(0);
	}
	return cur;
}

void CNModel::cnDij(int s)
{
	//迪杰斯特拉算法 
	int min;
	int vexnum = this->cnMap.size();
	// debug 模式下应该会显示
#ifdef MDEBUG
	std::cout << "目前结点数为" << vexnum << endl;
#endif

	int u = 0;

	for (int i = 0; i < vexnum; i++)
	{
		this->cnVis[i] = 0;
		this->cnDis[i] = this->cnMatrix[s][i];
	}
	this->cnVis[s] = 1;
	for (int k = 0; k < vexnum; k++)
	{
		min = INF+1;
		for (int i = 0; i < vexnum; i++)
		{
			if (this->cnVis[i] == 0 && min > this->cnDis[i])
			{
				min = this->cnDis[i];
				u = i;
			}
		}
		this->cnVis[u] = 1;
		for (int i = 0; i < vexnum; i++)
		{
			if (!this->cnVis[i] && this->cnDis[i] > this->cnDis[u] + this->cnMatrix[u][i])
			{
				this->cnDis[i] = this->cnDis[u] + this->cnMatrix[u][i];
			}
		}
	}

	//cout << "最短路径值为：" << this->cnDis[y] << endl;
}

void CNModel::debug2() { //适用于ryx的数据
	this->cnMap.clear();
	this->cnMap.insert(make_pair("甲", 0));
	this->cnMap.insert(make_pair("乙", 1));
	this->cnMap.insert(make_pair("丙", 2));
	this->cnMap.insert(make_pair("丁", 3));
	this->cnMap.insert(make_pair("戊", 4));
	this->cnMap.insert(make_pair("己", 5));
	int tempn = 6;
#ifdef MDEBUG
#endif
	for (int i = 0; i < tempn; i++) {
		for (int j = 0; j < tempn; j++) {
			this->cnMatrix[i][j] = INF;
		}
	}


}

void CNModel::debug1() {  //适用于邻接矩阵版本
	int tempn = DEBUGVEXNUM;
	// 先行储存100个地点的strig int值
	this->cnMap.clear();
	for (int i = 0; i < tempn; i++) {
		string keyString = debugGetName();
		this->cnMap.insert(make_pair(keyString, i));
#ifdef MDEBUG
		std::cout << "key => " << keyString << "   value =>" << i;
#endif
	}
	//初始化矩阵
	for (int i = 0; i < tempn; i++) {
		for (int j = 0; j < tempn; j++) {
			this->cnMatrix[i][j] = INF;
		}
	}
	int tempe = DEBUGVEXNUM;
	for (int i = 0; i < tempe; i++) {
		int vexi = rand() % tempn;
		int vexj = rand() % tempn;
		this->cnMatrix[vexi][vexj] = rand() % 2000 + 1;
	}
#ifdef MDEBUG
	for (int i = 0; i < tempn; i++) {
		for (int j = 0; j < tempn; j++) {
			std::cout << this->cnMatrix[i][j] << "\t";
		}
		std::cout << endl;
	}
#endif
}

void CNModel::cnInitSite()
{
	this->debug1();
}

void CNModel::cnGetRoute(string start, string end)
{

}

CNModel::CNModel()
{
}


CNModel::~CNModel()
{
}
