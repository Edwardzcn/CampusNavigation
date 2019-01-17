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
	//IndexPoolNode* poolTail;
public:
	IndexPool(int size);
	void poolResize(int size);
	void poolDelete(int index);

	~IndexPool();
	//先不提供检错
	void poolPushIndex(int index);
	int poolPopIndex();
};


