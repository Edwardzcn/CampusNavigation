#include "CNModel.h"

//清空操作
//清空id对应位置的信息
void CNModel::clearPlaceWithId(int id)
{
	Place* tempPlace = this->placeTable[id];
	if (tempPlace == NULL) return;
	delete tempPlace; //虚函数调用应该是子类的析构函数
}

void CNModel::clearHash() {
	this->cnXY2IndexMap.clear();
	this->cnIndex2XYMap.clear();
	this->cnName2IndexMap.clear();
	this->cnIndex2NameMap.clear();
}

void CNModel::clearEdge() {
	for (int i = 0; i < MAX_VEX_NUM; i++) {
		for (int j = 0; j < MAX_VEX_NUM; j++) {
			this->cnPrintEdgeData[i][j] = this->cnPrintEdgeData[j][i] = 0;
		}
	}
}

void CNModel::clearEdgeWithId(int id1, int id2) {
	//id1<id2
	//if (id1 > id2) {
		//std::swap(id1, id2);
	//}

	this->cnPrintEdgeData[id1][id2] = 0;
	this->cnPrintEdgeData[id2][id1] = 0;
}

int CNModel::checkIdWithXY(int x, int y)
{
	//未找到 返回-1
	//找到则返回对应哈希id

	//遍历哈希表
	std::map< std::pair<int, int>, int>::iterator iter;
	for (iter = this->cnXY2IndexMap.begin(); iter != this->cnXY2IndexMap.end(); iter++) {
		int compareX = iter->first.first, compareY = iter->first.second;
		//不可能为空  为空的话已经删除了对应点
		//赋值给对应的x和y
		if (this->inCircleR(compareX, compareY, x, y)) {
			return iter->second;
		}
	}
	return -1;
}

//判断是否和所有已有点都不相交
bool  CNModel::checkXYInter(int x, int y) {
	std::map< std::pair<int, int>, int>::iterator iter;
	for (iter = this->cnXY2IndexMap.begin(); iter != this->cnXY2IndexMap.end(); iter++) {
		int compareX = iter->first.first, compareY = iter->first.second;
		//不可能为空  为空的话已经删除了对应点
		//赋值给对应的x和y
		if (this->inCircle2R(compareX, compareY, x, y)) {
			return true;
		}
	}
	return false;
}

bool CNModel::checkNameExist(std::string placename)
{
	if (this->cnName2IndexMap.count(placename) == 0) return false;
	else return true;
}

bool CNModel::inCircleR(int cx, int cy, int outx, int outy)
{
	double dis = sqrt((cx - outx)*(cx - outx) + (cy - outy)*(cy - outy));
	if (dis <=1.0*VEX_RADIUS+ EPS) return true;
	else return false;
}

bool CNModel::inCircle2R(int cx1, int cy1, int cx2, int cy2)
{
	double dis = sqrt((cx1 - cx2)*(cx1 - cx2) + (cy1 - cy2)*(cy1 - cy2));
	if (dis <=2.0*VEX_RADIUS + EPS) return true;
	else return false;
}

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

int CNModel::debugMakeXY(int range) {
	if (range == -1) range = 200;
	return rand() % range;

}

int CNModel::debugMakeXY() {
	return this->debugMakeXY(-1);
}





// 路径代码区域

void CNModel::cnDij(int endId)
{
	//逆向
	//迪杰斯特拉算法 
	int min;
	int vexnum = (int)this->cnXY2IndexMap.size();
	// debug 模式下应该会显示
#ifdef MDEBUG
	std::cout << "目前结点数为" << vexnum << std::endl;
#endif

	int u = 0;

	for (int i = 0; i < vexnum; i++)
	{
		this->cnVis[i] = 0;
		this->cnDis[i] = this->cnMatrix[endId][i];  //初始赋值为endId点可达点的路径
		if (this->cnDis[i] != INF) this->cnPre[i] = endId;  //可联通的点Pre初始化
		else this->cnPre[i] = -1;  //不可连通的点Pre初始化为-1
	}
	this->cnVis[endId] = 1;
	this->cnPre[endId] = -1;//首位置的前驱结点定义为-1
	for (int k = 0; k < vexnum; k++)
	{
		min = INF;
		for (int i = 0; i < vexnum; i++)
		{
			if (this->cnVis[i] == 0 && min > this->cnDis[i])
			{
				min = this->cnDis[i];
				u = i;
			}
		}
		//假定一定能找到
		this->cnVis[u] = 1;
		//访问该点

		//更新cnDis和cnPre
		for (int i = 0; i < vexnum; i++)
		{
			if (!this->cnVis[i] && this->cnDis[i] > this->cnDis[u] + this->cnMatrix[u][i])
			{
				this->cnDis[i] = this->cnDis[u] + this->cnMatrix[u][i];
				this->cnPre[i] = u;
			}
		}
	}
#ifdef MDEBUG
	for (int i = 0; i < vexnum; i++)
		std::cout << endId << "到" << i << "最短路径值为：" << this->cnDis[i] << std::endl;
#endif
}


int CNModel::cnGetRoute(int x1, int y1, int x2, int y2) {
	//-1表示点不合法
	//-2表示点击的为相同路径
	//-3表示无法抵达终点
	//获取最短路径 调用Dij
	int startId, endId;
	startId = this->checkIdWithXY(x1, y1);
	endId = this->checkIdWithXY(x2, y2);
	if (startId == -1 || endId == -1) return -1;
	else if (startId == endId) return -2;
	//调用逆向dij计算最短路，包含了记录前驱路径
	this->cnDij(endId);

	//Debug需要注意
	int pId = startId;
	int nextId = this->cnPre[startId];
	if (this->cnPre[startId] == -1) return -3; //如果没有访问到那么就是不可达
	while (nextId != -1) {
		//路径染色
		this->cnPrintEdgeData[pId][nextId] = 2;
		this->cnPrintEdgeData[nextId][pId] = 2;

		pId = nextId;
		nextId = this->cnPre[nextId];
	}
}


//绘图相关代码
void CNModel::getPrintData(struct node vexdata[MAX_VEX_NUM], int edgedata[MAX_VEX_NUM][MAX_VEX_NUM]) {
	std::map<std::pair<int, int>, int >::iterator iter;
	int tempX, tempY, tempColor;
	//全部初始化
	for (int i = 0; i < MAX_VEX_NUM; i++) {
		vexdata[i].x = vexdata[i].y = vexdata[i].color = -1;
		vexdata[i].exist_or_not = false;
	}
	for (iter = this->cnXY2IndexMap.begin(); iter != this->cnXY2IndexMap.end(); iter++) {
		int tempX = iter->first.first;
		int tempY = iter->first.second;
		int id = iter->second;
		vexdata[id].x = tempX;
		vexdata[id].y = tempY;
		vexdata[id].exist_or_not = true;
		//进行染色
		Place * tempPlace = this->placeTable[id];
		if ((dynamic_cast<Normal*>(tempPlace)) != NULL) {
			vexdata[id].color = 1;
		}
		else if ((dynamic_cast<Site*>(tempPlace)) != NULL) {
			vexdata[id].color = 2;

		}
		else if ((dynamic_cast<Building*>(tempPlace)) != NULL) {
			vexdata[id].color = 3;
		}
	}
	for (int i = 0; i < MAX_VEX_NUM; i++) {
		for (int j = 0; j < MAX_VEX_NUM; j++) {
			edgedata[i][j] = cnPrintEdgeData[i][j];
		}
	}
}

int CNModel::cnAddSiteWithId(int x, int y, int id, std::string name, std::string info, bool edit)
{
	//动态类型转换错误返回 -3
	//成功返回 id
	//修改map键值对以及对应的点数量
	this->cnXY2IndexMap.insert(std::make_pair(std::make_pair(x, y), id));
	this->cnIndex2XYMap.insert(std::make_pair(id, std::make_pair(x, y)));
	this->cnName2IndexMap.insert(std::make_pair(name, id));
	this->cnIndex2NameMap.insert(std::make_pair(id, name));
	this->cnVexNum++;

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
			return -3;
		}
		//调用子类的重写方法
		tempSite->reset(x, y, name, info, edit);
	}
	return id;

}

int CNModel::cnAddBuildingWithId(int x, int y, int id, std::string name, std::string info, std::string addr, std::string tel, bool edit) {
	//动态类型转换错误返回 -3
	//成功返回 id
	//修改map键值对以及对应的点数量
	this->cnXY2IndexMap.insert(std::make_pair(std::make_pair(x, y), id));
	this->cnIndex2XYMap.insert(std::make_pair(id, std::make_pair(x, y)));
	this->cnName2IndexMap.insert(std::make_pair(name, id));
	this->cnIndex2NameMap.insert(std::make_pair(id, name));
	this->cnVexNum++;

	//重写这个指针数组这个位置的信息
	if ((this->placeTable)[id] == NULL) {
		//如果从未利用过
		(this->placeTable)[id] = new Building(x, y, name, info, addr, tel, edit);

	}
	else {
		//如果之前利用过
		Building* tempBuilding = dynamic_cast<Building*> ((this->placeTable)[id]);
		if (tempBuilding == NULL) {
			//动态转换失败
			std::cout << "dynamic_cast turn failed" << std::endl;
			return -3;
		}
		//调用子类的重写方法
		tempBuilding->reset(x, y, name, info, addr, tel, edit);
	}
	return id;
}

int CNModel::cnAddEdgeWithId(int startId, int endId) {
	//数量只记录一半
	this->cnEdgeNum += 1;

	//更改储存结构的时候这里也要修改
	//邻接矩阵添加双向边
	this->cnPrintEdgeData[startId][endId] = 1;
	this->cnPrintEdgeData[endId][startId] = 1;
	return 1; //返回影响的边数
}

int CNModel::cnDeletePlaceWithId(int id)
{
	//直接根据id释放对应的指针数组位置管理的空间，然后修正一下所有路径Matrix
	// -3 返回删除出错，查找到这一步但是对应的空间为空
	Place *temp = (this->placeTable)[id];
	if (temp == NULL) return -3;



	//遍历变情况非零删除同时减去边数
	for (int i = 0; i < MAX_VEX_NUM; i++) {
		if (this->cnPrintEdgeData[id][i] != 0 || this->cnPrintEdgeData[i][id] != 0) {
			this->clearEdgeWithId(id, i);
			this->cnEdgeNum--;  //边数量记录-1
		}

	}

	//字典和常量
	//临时变量
	int vx, vy;
	std::string name;
	//字典记录删除
	(this->placeTable)[id]->getXY(&vx, &vy);
	this->cnXY2IndexMap.erase(std::make_pair(vx, vy));
	this->cnIndex2XYMap.erase(id);

	if (this->cnIndex2NameMap.count(id)) {
		name = this->cnIndex2NameMap[id];
		this->cnName2IndexMap.erase(name);
		this->cnIndex2NameMap.erase(id);
	}

	this->clearPlaceWithId(id);


	this->cnVexNum--; //点数量记录-1
	return id;

}

int CNModel::cnAddSite(int x, int y, std::string name, std::string info, bool edit)
{
	//重名返回-1  
	//坐标重叠返回-2
	//动态类型转换失败返回-3 成功返回id
	//链表里增加这一项


	if (this->checkNameExist(name)) return -1;
	
	if (this->checkXYInter(x, y)) return -2;
	
	//从坐标池里获取id
	int id = this->placeIdPool->poolPopIndex();


	return this->cnAddSiteWithId(x, y, id, name, info, edit);
}

int CNModel::cnAddBuilding(int x, int y, std::string name, std::string info, std::string addr, std::string tel, bool edit)
{
	//重名返回-1  动态类型转换失败返回-3 成功返回id
	//坐标重叠返回-2
	//链表里增加这一项
	//重名返回错误信息
	
	if (this->checkNameExist(name)) return -1;

	if (this->checkXYInter(x, y)) return -2;


	//从坐标池里获取id
	int id = this->placeIdPool->poolPopIndex();

	return this->cnAddBuildingWithId(x, y, id, name, info, addr, tel, edit);
}

////先不实现名称id双射和选框录入
//int CNModel::cnDeletePlace(std::string name)
//{
//	// -1 表示没有对应名字
//	int id;
//	if (!(this->checkNameExist(name))) return -1;
//	id = 
//	return this->cnDeletePlaceWithId(id);
//}

int CNModel::cnDeletePlace(int x, int y)
{
	int id = this->checkIdWithXY(x, y);
	if (id == -1) {
		//点击不在范围内
		return -1;
	}
	else return this->cnDeletePlaceWithId(id);
}

////先不实现名称id双射和选框录入
//int CNModel::cnAddEdge(std::string start, std::string end, int w)
//{
//	//根据string函数调用 先行检查
//	int u, v;
//	if (!(this->checkNameExist(start)) || !(this->checkNameExist(end)) || (u = cnXY2IndexMap[start]) == (v = cnXY2IndexMap[end])) {
//		//不存在起点和终点  或者是自回路
//		return -1;
//	}
//	if (w <= 0) {
//		//边距离不为正数
//		return -2;
//	}
//	this->cnAddEdge(u, v, w);
//}

int CNModel::cnAddEdge(int x1, int y1, int x2, int y2) {
	//-1表示位置不合法
	//-2表示相同点
	//-3表示已经有边
	//成功添加返回1

	int startId = this->checkIdWithXY(x1, y1);
	int endId = this->checkIdWithXY(x2, y2);
	if (startId == -1 || endId == -1) {
		return -1;
	}
	else if (startId == endId) {
		return -2;
	}
	else if (this->cnPrintEdgeData[startId][endId] != 0 || this->cnPrintEdgeData[endId][startId] != 0) {
		return -3;
	}
	this->cnPrintEdgeData[startId][endId] = this->cnPrintEdgeData[endId][startId] = 1;  //染普通色
	this->cnEdgeNum++;
	return 1;

	//
}

////先不实现名称id双射和选框录入
//int CNModel::cnDeleEdge(std::string start, std::string end)
//{
//	//返回-1 表示有其中之一找不到对应点
//	//返回-2 表示两者
//	int startId, endId;
//	if (!(this->checkNameExist(start)) || !(this->checkNameExist(end))) return -1;
//	startId = (this->cnXY2IndexMap)[start];
//	endId = (this->cnXY2IndexMap)[end];
//	if (startId == endId) return -2;
//	return this->delet;
//}

int CNModel::cnDeleEdge(int x1, int y1, int x2, int y2) {
	//-1表示位置不合法
	//-2表示相同点
	//-3表示已经无边
	//成功删除返回1

	int startId = this->checkIdWithXY(x1, y1);
	int endId = this->checkIdWithXY(x2, y2);
	if (startId == -1 || endId == -1) {
		return -1;
	}
	else if (startId == endId) {
		return -2;
	}
	else if (this->cnPrintEdgeData[startId][endId] == 0 && this->cnPrintEdgeData[endId][startId] == 0) {
		return -3;
	}
	this->cnPrintEdgeData[startId][endId] = this->cnPrintEdgeData[endId][startId] = 0;  //染普通色
	this->cnEdgeNum--;
	return 1;
}











void CNModel::cnInitSite()
{
#ifdef MDEBUG

#endif
}

////字符串形式查询路径
//void CNModel::cnGetRoute(std::string start, std::string end)
//{
//
//}


//-------文件读写相关---------
int CNModel::cnLoadRecord(std::string fileName)
{
	//从文件里读取数据
	//-1 表示文件不存在 打开失败
	//

	//打开文件
	std::ifstream infile;
	infile.open(fileName);

	//定义临时变量储存信息
	std::string tempT;
	if (!infile.is_open())
	{
		std::cout << "tempT文件打开失败" << std::endl;
		return -1;
	}

	//重置坐标池
	this->placeIdPool->poolResize(MAX_VEX_NUM);


	//从文件中读取点的数量
	std::getline(infile, tempT);
	std::stringstream streamN(tempT);
	streamN >> this->cnVexNum; //赋值给当前的点数量

	std::cout << "n=" << this->cnVexNum << std::endl;

	//建立临时对象
	std::string type;
	int id;
	int x, y, u, v;
	std::string buName;
	std::string buInfo;
	std::string buAddress;
	std::string buTel;
	std::string siName;
	std::string siInfo;

	//清理哈希表
	this->clearHash();
	//清理边的邻接矩阵
	this->clearEdge();
	//清理点的指针数组
	for (int i = 0; i < MAX_VEX_NUM; i++)
		this->clearPlaceWithId(i);

	for (int i = 0; i < this->cnVexNum; i++) {
		std::getline(infile, tempT);
		//infile.std::getline(tempT,100);
		std::stringstream streamVexData(tempT); //创建结点信息的流
		streamVexData >> id >> type >> x >> y;
		std::cout << "id=" << id << "   type=" << type << "   x=" << x << "   y=" << y;

		//坐标池删除对应id
		this->placeIdPool->poolDelete(id);

		//位置哈希表添加记录 双向
		this->cnIndex2XYMap.insert(std::make_pair(id, std::make_pair(x, y)));
		this->cnXY2IndexMap.insert(std::make_pair(std::make_pair(x, y), id));

		if (type[0] == 'N') {
			//是普通对象
			this->placeTable[id] = new Normal(x, y, true);
			std::cout << "    create Normal" << std::endl;
			//不添加特殊哈希表双射
		}
		else if (type[0] == 'S') {
			//是景点对象
			streamVexData >> siName >> siInfo;
			this->placeTable[id] = new Site(x, y, siName, siInfo, true);
			std::cout << "    create Site" << std::endl;
			//添加特殊哈希表双射
			this->cnIndex2NameMap.insert(std::make_pair(id, siName));
			this->cnName2IndexMap.insert(std::make_pair(siName, id));
		}
		else if (type[0] == 'B') {
			// 是建筑对象
			streamVexData >> buName >> buInfo >> buAddress >> buAddress;
			this->placeTable[id] = new Building(x, y, buName, buInfo, buAddress, buTel, true);
			std::cout << "    create Building" << std::endl;
			//添加特殊哈希表双射
			this->cnIndex2NameMap.insert(std::make_pair(id, buName));
			this->cnName2IndexMap.insert(std::make_pair(buName, id));
		}
		//std::cout << std::endl;
	}

	//从文件中读取边的数量
	std::getline(infile, tempT);
	std::stringstream streamE(tempT);
	streamE >> this->cnEdgeNum; //赋值给当前的边数量

	std::cout << "edegenum e=" << this->cnEdgeNum << std::endl;
	for (int i = 0; i < this->cnEdgeNum; i++) {
		std::getline(infile, tempT);
		std::stringstream streamEdgeData(tempT); //创建边信息的流
		streamEdgeData >> u >> v;
		this->cnPrintEdgeData[u][v] = 1;
		this->cnPrintEdgeData[v][u] = 1;
		std::cout << "u=" << u << "  v=" << v << std::endl;
	}

	infile.close();
}

int CNModel::cnSaveRecord(std::string fileName) {

	//向文件里覆盖写数据
	//-1 表示文件不存在 打开失败
	//

	std::ofstream outfile(fileName, std::ios::ate);   //打开文件，设置写入方式为覆盖写入
	if (!outfile.is_open())
	{
		std::cout << "文件打开失败" << std::endl;
		return -1;
	}

#ifdef MDEBUG_RECORD
	//debug数据构造数据模块
	int tempn = DEBUGVEXNUM;
	int tempe = DEBUGEDGENUM;
	outfile << tempn << std::endl;
	//构造点数据 

	std::string placeKind[3] = { "Normal","Site","Building" };
	int edgeData[MAX_VEX_NUM][MAX_VEX_NUM];
	for (int i = 0; i < tempn; i++) {
		int kind = rand() % 3;
		outfile << i << "  " << placeKind[kind];
		if (kind == 0) {
			outfile << "  " << this->debugMakeXY(-1) << "  " << debugMakeXY(-1) << std::endl;
		}
		else if (kind == 1) {
			outfile << "  " << this->debugMakeXY(-1) << "  " << debugMakeXY(-1) << "  哇" << debugGetName(-1) << "哈哈  " << debugGetName(-1) << endl;
		}
		else if (kind == 2) {
			outfile << "  " << debugMakeXY(-1) << "  " << debugMakeXY(-1) << "  哇" << debugGetName(-1) << "哈哈  " << debugGetName(-1) << "哈哈  " << debugGetName(-1) << "哈哈  " << debugGetName(-1) << endl;
		}

	}
	//构造边数据
	memset(edgeData, 0, sizeof(edgeData));
	outfile << tempe << std::endl;
	int cnt = 0;
	while (cnt < tempe) {
		int u = rand() % tempn;
		int v = rand() % tempn;
		if (u >= v || edgeData[u][v] == 1) continue;
		outfile << u << "  " << v << endl;
		cnt++; //计数器增加

	}


	std::cout << "写入txt文件示例." << std::endl;
	std::cout << "成功写入.\n" << std::endl;
	outfile.close();
	return 1;
#endif

	//建立临时对象
	std::string type;
	int id;
	int x, y;
	std::string buName;
	std::string buInfo;
	std::string buAddress;
	std::string buTel;
	std::string siName;
	std::string siInfo;
	Place* tempPlace;
	Normal* tempNormal;
	Site* tempSite;
	Building* tempBuilding;

	//先输出点数量
	outfile << this->cnVexNum << std::endl;

	//写点数量的详细信息，注意区分类别
	std::map<int, std::pair<int, int> >::iterator iter;
	for (iter = this->cnIndex2XYMap.begin(); iter != this->cnIndex2XYMap.end(); iter++) {
		id = iter->first;
		tempPlace = this->placeTable[id];
		//测试转型
		if ((dynamic_cast<Normal*>(tempPlace)) != NULL) {
			tempNormal = dynamic_cast<Normal*>(tempPlace);
			type = "Normal";
			outfile << id << "   " << type << "  " << tempNormal->x << "   " << tempNormal->y << std::endl;
		}
		else if ((dynamic_cast<Site*>(tempPlace)) != NULL) {
			tempSite = dynamic_cast<Site*>(tempPlace);
			type = "Site";
			outfile << id << "   " << type << "  " << tempSite->x << "   " << tempSite->y << "   " << tempSite->siName << "   " << tempSite->siInfo << std::endl;
		}
		else if ((dynamic_cast<Building*>(tempPlace)) != NULL) {
			tempBuilding = dynamic_cast<Building*>(tempPlace);
			type = "Building";
			outfile << id << "   " << type << "  " << tempBuilding->x << "   " << tempBuilding->y << "   " << tempBuilding->buName << "   " << tempBuilding->buInfo << "   " << tempBuilding->buAddress << "   " << tempBuilding->buTel << std::endl;
		}
	}

	//遍历二维数组写入边数据，按照前小后大写入
	//先输出边的数量
	outfile << this->cnEdgeNum << std::endl;

	//只打印一半有记录的边
	for (int i = 0; i < MAX_VEX_NUM; i++) {
		for (int j = i; j < MAX_VEX_NUM; j++) {
			if (this->cnPrintEdgeData[i][j] != 0) {
				outfile << i << "   " << j << std::endl;
			}
		}
	}


	outfile.close();
}

CNModel::CNModel()
{
	//随机数种子
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