#pragma once
#include <cstdio>
#include <string>
#include <map>
#include <unordered_map>
using namespace std;
#define rep(i,a,n) for(int i=a;i<n;++i)
#define per(i,a,n) for(int i=n-1;i>=a;--i)
#define MAXSIZE 1000
#define INF 0x3f3f3f3f



class Place {
public:
	int number;
	int px;
	int py;
	std::string introduction;
	std::string name;
};

typedef struct node
{
	Place p;
	struct node* next;
} Node;

Node *addNode();


class CNModel
{

private:

	// 字符串整形映射关系
	unordered_map<string, int> cnMap;
	// 数组储存当前路径的访问点
	int cnVis[MAXSIZE];
	//数组储存当前最短路径大小;
	int cnDis[MAXSIZE];

	//vol1采用邻接表储存数据
	int cnMatrix[MAXSIZE][MAXSIZE];
	//vol2采用邻接矩阵储存数据

private:
	//------------后端自用主要方法--------------
	void cnDij(int s);
	void cnDfs();

public:
	//------------调试调用主要方法--------------
	void debug1();
	void debug2();
	//------------前端调用主要方法--------------

	//增添节点
	void cnAddSite(string sitename);

	//删除节点，参数传递节点名字
	void cnDeleteSite(string sitename);

	//第一次进入地图（查不到本地文件），进行构造
	void cnInitSite();

	//前端查询路径，进行查询并染色。
	void cnGetRoute(string start, string end);
	//前端调用上述函数后更新数据然后从新刷新地图

	CNModel();
	~CNModel();
};

