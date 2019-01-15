#include "CNModel.h"
#include "Site.h"
#include "Building.h"
#include <string>
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <unordered_map>
#include <iterator>
//调试生成英文单词函数


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
		std::cout << s << "到" << i << "最短路径值为：" << this->cnDis[i] << std::endl;
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

int CNModel::cnAddSite(int x, int y, std::string name, std::string info, bool edit)
{
	//重名返回-1  动态类型转换失败返回-2
	//链表里增加这一项
	//重名返回错误信息
	if (this->cnCheckName(name)) return -1;
	//从坐标池里获取id
	int id = this->placeIdPool->poolPopIndex;
	this->cnMap.insert(std::make_pair(name, id));

	//重写这个指针数组这个位置的信息
	if ((this->placeTable)[id] == NULL) {
		//如果从未利用过
		(this->placeTable)[id] = new Site(x, y, name, info, edit);

	}
	else {
		//如果之前利用过
		Site* tempSite = dynamic_cast<Site*> ((this->placeTable)[id]);
		if (tempSite == NULL) {
			//动态转换失败
			std::cout << "dynamic_cast turn failed" << std::endl;
			return -2;
		}
		//调用子类的重写方法
		tempSite->reset(x, y, name, info, edit);
	}
}

int CNModel::cnAddBuilding(int x, int y, std::string name, std::string info, std::string addr, std::string tel, bool edit)
{
	//重名返回-1  动态类型转换失败返回-2
	//链表里增加这一项
	//重名返回错误信息
	if (this->cnCheckName(name)) return -1;
	//从坐标池里获取id
	int id = this->placeIdPool->poolPopIndex;
	this->cnMap.insert(std::make_pair(name, id));

	//重写这个指针数组这个位置的信息
	if ((this->placeTable)[id] == NULL) {
		//如果从未利用过
		(this->placeTable)[id] = new Site(x, y, name, info, edit);

	}
	else {
		//如果之前利用过
		Site* tempSite = dynamic_cast<Site*> ((this->placeTable)[id]);
		if (tempSite == NULL) {
			//动态转换失败
			std::cout << "dynamic_cast turn failed" << std::endl;
			return -2;
		}
		//调用子类的重写方法
		tempSite->reset(x, y, name, info, edit);
	}
}

int CNModel::cnDeleSiteOrBuilding(std::string name)
{
	// -1 表示没有对应名字
	int id;
	if (!(this->cnCheckName(name))) return -1;
	return this->cnDeletePlaceWithId(id);
}

int CNModel::cnDeleSiteOrBuilding(int x, int y)
{
	int id = this->checkIdWithXY(x, y);
	if (id == -1) {
		//点击不在范围内
		return -1;
	}
	else return this->cnDeletePlaceWithId(id);
}

bool CNModel::cnCheckName(std::string placename)
{
	if (cnMap.count(placename) == 0) return false;
	else return true;
}
int CNModel::cnDeletePlaceWithId(int id)
{
	//直接根据id释放对应的指针数组位置管理的空间，然后修正一下所有路径Matrix
	// -3 返回删除出错，查找到这一步但是对应的空间为空
	// 
	return -3;
}
int CNModel::cnAddEdge(int u, int v, int w) {
	//更改储存结构的时候这里也要修改
	//添加双向边

	this->cnMatrix[u][v] = w;
	this->cnMatrix[v][u] = w;

}

int CNModel::cnAddEdge(std::string start, std::string end, int w)
{
	//根据string函数调用 先行检查
	int u, v;
	if (!(this->cnCheckName(start)) || !(this->cnCheckName(end)) || (u = cnMap[start]) == (v = cnMap[end])) {
		//不存在起点和终点  或者是自回路
		return -1;
	}
	if (w <= 0) {
		//边距离不为正数
		return -2;
	}
	this->cnAddEdge(u, v, w);
}

int CNModel::checkIdWithXY(int x, int y)
{
	//遍历哈希表
	std::unordered_map<std::string, int>::iterator iter;
	for (iter = this->cnMap.begin(); iter != this->cnMap.end(); iter++) {
		int compareId = iter->second;
		int compareX, compareY;
		//先判断是不是空的  delete过
		if (!((this->placeTable)[compareId])) continue;
		//赋值给对应的x和y
		(this->placeTable)[compareId]->getXY(&compareX, &compareY);
		if (this->inCircleR(compareX,compareY,x,y)) {
			return iter->second;
		}
	}
	return -1;
}

inline bool CNModel::inCircleR(int cx, int cy, int outx, int outy)
{
	double dis = sqrt((cx - outx)*(cx - outx) + (cy - outy)*(cy - outy));
	if (abs(dis - 1.0*VEX_RADIUS) < EPS) return true;
	else return false;
}

bool CNModel::inCircle2R(int cx1, int cy1, int cx2, int cy2)
{
	double dis = sqrt((cx1 - cx2)*(cx1 - cx2) + (cy1 - cy2)*(cy1 - cy2));
	if (abs(dis - 1.0*VEX_RADIUS) < EPS) return true;
	else return false;
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
	this->placeIdPool = new IndexPool(MAX_VEX_NUM);
	this->recordIdPool = new IndexPool(MAX_REC_NUM);
}


CNModel::~CNModel()
{
	delete this->recordIdPool;
	delete this->placeIdPool;
}