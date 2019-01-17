#include "CNModel.h"
#include "CNView.h"
#include <iostream>
int main()
{
	CNModel* cnmodel1 = new CNModel();
	cnmodel1->cnLoadRecord(std::string("testReadData.txt"));
	cnmodel1->cnSaveRecord(std::string("testSaveData.txt"));
	int x1=9, y1=16;  //模拟第一个数 9 16
	int x2=36, y2=194; //模拟偏离第二个数 36 195
	int x3 = 0, y3 = 0; //模拟可添加
	std::string testAddName="测试添加的";
	std::string testAddInfo="测试信息infolsiadufhds不辣不辣比bualaidufasioaijsasda假如假如测试测试";
	std::string testAddAddr="中国湖南长沙岳麓区左家long男子职业学院";
	std::string testAddTel="123654789";
	cout << cnmodel1->cnAddBuilding(x3, y3, testAddName, testAddInfo, testAddAddr,testAddTel);
	cout << cnmodel1->cnDeletePlace(x2, y2);
	
	cnmodel1->cnSaveRecord(std::string("testSaveData.txt"));
	system("pause");
}
