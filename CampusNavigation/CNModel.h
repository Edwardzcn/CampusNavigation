#pragma once

#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <iterator>
#include "Place.h"
#include "Site.h"
#include "Building.h"
#include "Normal.h"
#include "IndexPool.h"
#define rep(i,a,n) for(int i=a;i<n;++i)
#define per(i,a,n) for(int i=n-1;i>=a;--i)
#define MAX_VEX_NUM 500
#define MAX_REC_NUM 1000

#define INF 0x3f3f3f3f
#define DEBUGVEXNUM 10 //debug键值对数量（点数量）
#define DEBUGEDGENUM 39 //debug边数量
#define MDEBUG DEBUG
//#define MDEBUG_RECORD MDEBUG_RECORD
#define VEX_RADIUS 7 //圆半径 像素为单位 
#define EPS 1e-8
struct node {
	int x;
	int y;
	int color;
	bool exist_or_not;
};

class CNModel
{

public:
	//传递给前端的数据


private:
	//当前点数量
	int cnVexNum;
	int cnEdgeNum;


	//二维坐标与数组角标双射关系
	std::map<std::pair<int, int>, int> cnXY2IndexMap;
	std::map<int, std::pair<int, int>  >cnIndex2XYMap;
	//特殊点名称与数组角标的双射关系
	std::map<std::string, int> cnName2IndexMap;
	std::map<int, std::string> cnIndex2NameMap;


	//int cnPrintVexData[MAX_VEX_NUM]; //绘图用
	int cnPrintEdgeData[MAX_VEX_NUM][MAX_VEX_NUM]; //绘图用

	//std::map<int,
	//数组储存当前路径的访问点
	int cnVis[MAX_VEX_NUM];
	//数组储存当前最短路径大小;
	int cnDis[MAX_VEX_NUM];
	//数组储存前驱结点
	int cnPre[MAX_VEX_NUM];

	//vol1采用邻接表距离数据
	int cnMatrix[MAX_VEX_NUM][MAX_VEX_NUM];
	//vol2采用邻接矩阵储存数据
	Place * placeTable[MAX_VEX_NUM];
	Record* recordTable[MAX_REC_NUM];

	//vol3坐标池来动态分配表数据
	IndexPool* placeIdPool;
	IndexPool* recordIdPool;


	//------------后端调试主要方法--------------
	std::string debugGetName(int len);
	std::string debugGetName();
	int debugMakeXY(int range);
	int debugMakeXY();


	//------------后端自用主要方法--------------
	//清空操作
	//清空id对应位置的位置信息，归还资源
	void clearHash();
	void clearPlaceWithId(int id);
	void clearEdge();
	void clearEdgeWithId(int id1, int id2);


	void cnDij(int s);
	//判断点是否在圆内
	bool inCircleR(int cx, int cy, int outx, int outy);

	//判断两圆是否相交
	bool inCircle2R(int cx1, int cy1, int cx2, int cy2);

	//坐标匹配 绝对距离在半径为r的圆内即判断为是对应区域
	int checkIdWithXY(int x, int y);

	//判断是否和所有已有点都不相交
	bool checkXYInter(int x, int y);

	//先不实现名称id双射和选框录入
	//查看字典里是否已有同名串
	bool checkNameExist(std::string placename);

	//根据Id增加删除对应结点以及其连接的边
	int cnAddSiteWithId(int x, int y, int id, std::string name, std::string info, bool edit);
	int cnAddBuildingWithId(int x, int y, int id, std::string name, std::string inf, std::string addr, std::string tel, bool edit);
	int cnDeletePlaceWithId(int id);

	//根据Id添加无向边
	int cnAddEdgeWithId(int startId, int endId);







public:


	// # ------------前端调用主要方法--------------

	// ## 绘图相关
	void getPrintData(struct node vexdata[MAX_VEX_NUM], int edgedata[MAX_VEX_NUM][MAX_VEX_NUM]);


	// ## 节点相关
	//添加节点（均是通过文本框输入添加） click add + 鼠标点击确定 x y + 文本框输入with选择添加类型（前端做选择/转换）
	// 添加景点
	int cnAddSite(int x, int y, std::string name, std::string info, bool edit = true);
	int cnAddBuilding(int x, int y, std::string name, std::string inf, std::string addr, std::string tel, bool edit = true);
	//删除节点（）   click  delete + 二级选择（鼠标点击/文本框输入）
	//先不实现名称id双射和选框录入
	//int cnDeletePlace(std::string name);
	int cnDeletePlace(int x, int y);


	// ## 路径相关
	//添加路径
	//绘制方式直接实现
	int cnAddEdge(int x1, int y1, int x2, int y2);
	//删除无相边 输入框实现 / 画点实现
	//先不实现名称id双射和选框录入
	//int cnDeleEdge(std::string start, std::string end);
	int cnDeleEdge(int x1, int y1, int x2, int y2);




	//第一次进入地图（查不到本地文件），进行构造
	void cnInitSite();

	//前端查询路径，进行查询并染色。
	//先不实现名称id双射和选框录入
	//void cnGetRoute(std::string start, std::string end);

	int cnGetRoute(int x1, int y1, int x2, int y2);
	//前端调用上述函数后更新数据然后从新刷新地图
	//返回值不同表示不同状态


	//--------文件读写相关----------
	//从文件中读取信息储存在model数据结构中
	int cnLoadRecord(std::string fileName);
	//将model数据结构中的数据储存在文件中
	int cnSaveRecord(std::string fileName);

	CNModel();
	~CNModel();
};

