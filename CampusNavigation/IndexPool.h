#pragma once
class IndexPoolNode {
public:
	int id;
	IndexPoolNode* nextid;
};
class IndexPool
{
	int poolMaxSize;
	int poolNowSize;
	IndexPoolNode* poolHead;
	IndexPoolNode* poolTail;
public:
	IndexPool(int size);
	~IndexPool();
	//先不提供检错
	void poolPushIndex(int index);
	int poolPopIndex();
};


