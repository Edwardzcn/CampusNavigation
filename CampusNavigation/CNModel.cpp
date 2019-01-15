#include "CNModel.h"
#include <string>
#include <ctime>
#include <iostream>
#include <cstdlib>
//调试生成英文单词函数
#define DEBUGVEXNUM 10 //debug键值对数量（点数量）
#define DEBUGEDGENUM 39 //debug边数量
#define INF 0x3f3f3f3f
#define MDEBUG 


std::string CNModel::debugGetName(int len) {
	//参数为构造长度.
	if (len == -1) len = rand() % 5 + 5;
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
std::string CNModel::debugGetName() {
	return debugGetName(-1);
}

void CNModel::cnDij(int s)
{
	//迪杰斯特拉算法 
	int min;
	int vexnum = (int)this->cnMap.size();
	// debug 模式下应该会显示
#ifdef MDEBUG
	std::cout << "目前结点数为" << vexnum << std::endl;
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
		min = INF + 1;
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
#ifdef MDEBUG
	for (int i = 0; i < vexnum; i++)
		std::cout <<s<<"到"<<i<< "最短路径值为：" << this->cnDis[i] << std::endl;
#endif
}

void CNModel::debug2() { //适用于ryx的数据
	this->cnMap.clear();
	this->cnMap.insert(std::make_pair("甲", 0));
	this->cnMap.insert(std::make_pair("乙", 1));
	this->cnMap.insert(std::make_pair("丙", 2));
	this->cnMap.insert(std::make_pair("丁", 3));
	this->cnMap.insert(std::make_pair("戊", 4));
	this->cnMap.insert(std::make_pair("己", 5));
	int tempn = 6;

	for (int i = 0; i < tempn; i++) {
		for (int j = 0; j < tempn; j++) {
			this->cnMatrix[i][j] = INF;
		}
	}
#ifdef MDEBUG
	for (int i = 0; i < tempn; i++) {
		for (int j = 0; j < tempn; j++) {
			if (this->cnMatrix[i][j] == INF) std::cout << "max" << "\t";
			else std::cout << this->cnMatrix[i][j] << "\t";
		}
		std::cout << std::endl;
	}
#endif
	this->cnDij(0);
}

void CNModel::cnAddSite(std::string sitename)
{
	
}

bool CNModel::cnCheckName(std::string placename)
{
	if (cnMap.count(placename) == 0) return false;
	else return true;
}

void CNModel::cnAddEdge(std::string start, std::string end)
{
	//根据string函数调用 先行检查
}

void CNModel::debug1() {  //适用于邻接矩阵版本
	int tempn = DEBUGVEXNUM;
	// 先行储存100个地点的strig int值
	this->cnMap.clear();
	for (int i = 0; i < tempn; i++) {
		std::string keyString = debugGetName();
		this->cnMap.insert(make_pair(keyString, i));
#ifdef MDEBUG
		std::cout << "key => " << keyString << "   value =>" << i << std::endl;
#endif
	}
	//初始化矩阵
	for (int i = 0; i < tempn; i++) {
		for (int j = 0; j < tempn; j++) {
			this->cnMatrix[i][j] = INF;
		}
	}
	int tempe = DEBUGEDGENUM;
	for (int i = 0; i < tempe; i++) {
		int vexi = rand() % tempn;
		int vexj = rand() % tempn;
		this->cnMatrix[vexi][vexj] = rand() % 2000 + 1;
	}
#ifdef MDEBUG
	for (int i = 0; i < tempn; i++) {
		for (int j = 0; j < tempn; j++) {
			if (this->cnMatrix[i][j] == INF) std::cout << "max" << "\t";
			else std::cout << this->cnMatrix[i][j] << "\t";
		}
		std::cout << std::endl;
	}
#endif
	this->cnDij(0);
}

void CNModel::cnInitSite()
{
	this->debug1();
}

void CNModel::cnGetRoute(std::string start, std::string end)
{

}

CNModel::CNModel()
{
	int t = std::time(NULL);
	std::srand(t);
}


CNModel::~CNModel()
{
}
