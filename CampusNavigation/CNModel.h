#pragma once
#include <cstdio>
#include <map>
#include <unordered_map>
#include "Place.h"
#include "Record.h"
#define rep(i,a,n) for(int i=a;i<n;++i)
#define per(i,a,n) for(int i=n-1;i>=a;--i)
#define MAX_VEX_NUM 500
#define MAX_REC_NUM 1000
#define INF 0x3f3f3f3f

class CNModel
{

private:
	//当前点数量
	int cnVexNum;
	int cnEdgeNum;
	//字符串整形映射关系
	std::unordered_map<std::string, int> cnMap;
	//数组储存当前路径的访问点
	int cnVis[MAX_VEX_NUM];
	//数组储存当前最短路径大小;
	int cnDis[MAX_VEX_NUM];

	//vol1采用邻接表距离数据
	int cnMatrix[MAX_VEX_NUM][MAX_VEX_NUM];
	//vol2采用邻接矩阵储存数据
	Place * placeTable[MAX_VEX_NUM];
	Record* recordTable[MAX_REC_NUM];


	//------------后端调试主要方法--------------
	std::string debugGetName();
	std::string debugGetName(int len);
	//------------后端自用主要方法--------------
	void cnDij(int s);
	void cnDfs();

public:
	//------------调试调用主要方法--------------
	void debug1();
	void debug2();
	void clearEdge(int u,int v);
	void clearNode(int verindex);
	//------------前端调用主要方法--------------

	//增添节点
	void cnAddSite(std::string sitename);
	void cnAddBuilding(std::string buildingname);
	bool cnCheckName(std::string placename);
	//添加路径
	void cnAddEdge(std::string start,std::string end);
	void cnAddEdge(int u, int v);
	//删除节点，参数传递节点名字
	void cnDeleteSite(std::string start,std::string end);
	void cnDeleteSite(int u, int v);

	//第一次进入地图（查不到本地文件），进行构造
	void cnInitSite();

	//前端查询路径，进行查询并染色。
	void cnGetRoute(std::string start, std::string end);
	//前端调用上述函数后更新数据然后从新刷新地图

	CNModel();
	~CNModel();
};

