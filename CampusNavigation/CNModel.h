#pragma once
#include <cstdio>
#include <map>
#include <unordered_map>
#include "Place.h"
#include "Record.h"
#include "IndexPool.h"
#define rep(i,a,n) for(int i=a;i<n;++i)
#define per(i,a,n) for(int i=n-1;i>=a;--i)
#define MAX_VEX_NUM 500
#define MAX_REC_NUM 1000
#define INF 0x3f3f3f3f
#define DEBUGVEXNUM 10 //debug键值对数量（点数量）
#define DEBUGEDGENUM 39 //debug边数量
#define MDEBUG DEBUG
#define VEX_RADIUS 7 //圆半径 像素为单位 
#define EPS 1e-8
class CNModel
{

private:
	//当前点数量
	int cnVexNum;
	int cnEdgeNum;
	//二维坐标与数组角标映射关系
	std::unordered_map<std::pair<int,int>, int> cnXY2IndexMap;
	//std::unordered_map<int,
	//数组储存当前路径的访问点
	int cnVis[MAX_VEX_NUM];
	//数组储存当前最短路径大小;
	int cnDis[MAX_VEX_NUM];

	//vol1采用邻接表距离数据
	int cnMatrix[MAX_VEX_NUM][MAX_VEX_NUM];
	//vol2采用邻接矩阵储存数据
	Place * placeTable[MAX_VEX_NUM];
	Record* recordTable[MAX_REC_NUM];

	//vol3坐标池来动态分配表数据
	IndexPool* placeIdPool;
	IndexPool* recordIdPool;


	//------------后端调试主要方法--------------
	std::string debugGetName();
	std::string debugGetName(int len);
	//------------后端自用主要方法--------------
	void cnCacuDis();
	void cnDij(int s);
	void cnDfs();

	//判断点是否在圆内
	bool inCircleR(int cx, int cy, int outx, int outy);
	
	//判断两圆是否相交
	bool inCircle2R(int cx1, int cy1, int cx2, int cy2);
	
	//坐标匹配 绝对距离在半径为r的圆内即判断为是对应区域
	int checkIdWithXY(int x, int y);

	//先不实现名称id双射和选框录入
	//查看字典里是否已有同名串
	//bool cnCheckName(std::string placename);
	
	//根据Id增加删除对应结点以及其连接的边
	int cnAddSiteWithId(int x,int y,int id, std::string name, std::string info, bool edit);
	int cnAddBuildingWithId(int x,int y,int id, std::string name, std::string inf, std::string addr, std::string tel, bool edit);
	int cnDeletePlaceWithId(int id);
	
	//根据Id添加无向边
	int cnAddEdgeWithId(int startId, int endId, int w);
	
	

	// # ------------调试调用主要方法--------------
public:
	void debug1();
	void debug2();

	// # ------------前端调用主要方法--------------

	// ## 节点相关
	//添加节点（均是通过文本框输入添加） click add + 鼠标点击确定 x y + 文本框输入with选择添加类型（前端做选择/转换）
	// 添加景点
	int cnAddSite(int x, int y, std::string name, std::string info, bool edit);
	int cnAddBuilding(int x, int y, std::string name, std::string inf, std::string addr, std::string tel, bool edit);
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
	void cnGetRoute(int x1, int y1, int x2,int y2);
	//前端调用上述函数后更新数据然后从新刷新地图

	CNModel();
	~CNModel();
};

