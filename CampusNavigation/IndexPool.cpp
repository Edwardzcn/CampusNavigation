#include "IndexPool.h"
#include <iostream>
IndexPool::IndexPool(int size)
{
	this->poolMaxSize = size;
	IndexPoolNode* pre = NULL, *now = NULL;
	this->poolHead = new IndexPoolNode;
	//this->poolTail = this->poolHead;
	//initial
	pre = now = poolHead;
	pre->id = -1;
	pre->nextid = NULL;
	for (int i = 0; i < size; i++) {
		now = new IndexPoolNode;
		now->id = i;
		now->nextid = NULL;
		pre->nextid = now;
		pre = pre->nextid;
	}
	this->poolNowSize = size;
	
}

IndexPool::~IndexPool()
{
	//清理坐标池
	IndexPoolNode* now = this->poolHead,*pre;
	while (now != NULL) {
		pre = now;
		now = now->nextid;
		delete pre;
	}
}

void IndexPool::poolPushIndex(int index)
{
	//添加id到池中，链表位置。
	IndexPoolNode *p = new IndexPoolNode;
	p->id = index;
	p->nextid = this->poolHead->nextid;
	this->poolHead->nextid = p;
	this->poolNowSize++;
}

int IndexPool::poolPopIndex()
{
	//判断如果为空则返回-1
	if (this->poolNowSize == 0) return -1;
	IndexPoolNode *p = this->poolHead->nextid;
	int tempid = p->id;
	this->poolHead->nextid = p->nextid;
	delete p;
	this->poolNowSize--;
	return tempid;
}

void IndexPool::poolResize(int size) {
	IndexPoolNode *p = this->poolHead, *q;
	while (p != NULL) {
		q = p;
		p = p->nextid;
		delete q;
	}
	this->poolMaxSize = size;
	IndexPoolNode* pre = NULL, *now = NULL;
	this->poolHead = new IndexPoolNode;
	//this->poolTail = this->poolHead;
	//initial
	pre = now = poolHead;
	pre->id = -1;
	pre->nextid = NULL;
	for (int i = 0; i < size; i++) {
		now = new IndexPoolNode;
		now->id = i;
		now->nextid = NULL;
		pre->nextid = now;
		pre = pre->nextid;
	}
	this->poolNowSize = size;
}

void IndexPool::poolDelete(int index) {
	IndexPoolNode* pre = NULL, *now = NULL;
	pre = poolHead;
	now = poolHead->nextid;
	while (now!=NULL) {
		if (now->id == index) {
			//执行删除操作
			pre->nextid = now->nextid;
			delete now;
			return;
		}
		pre = now;
		now = now->nextid;
		
	}
}