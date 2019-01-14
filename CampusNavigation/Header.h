#ifndef Header_h
#define Header_h
#include <iostream>
#include <string>
using namespace std;

class Place {
public:
    string name;
    int number;
    string introduction;
    int px;
    int py;
};

typedef struct node
{
    Place p;
    struct node* next;
} Node;

Node * addNode()
{
    Node *cur = (Node*)malloc(sizeof(Node));
    if(cur == NULL)
    {
        printf("malloc failed!\n");
        exit(0);
    }
    return cur;
}

Node* route(Place p1,Place p2){
    Node *head = new Node;
    head->p=p1;
    head->next=NULL;
	Node *tail = new Node;
    tail->p=p2;
	free(head);
	free(tail);
    return head;
}

int net[6][6]=
{
    {0,2,7,4,6,100},
    {2,0,5,3,100,8},
    {7,5,0,3,100,6},
    {4,3,3,0,2,100},
    {6,100,100,2,0,100},
    {100,8,6,100,100,0}
};

void D(int x,int y)
{
    int ik;
    int min;
    const int vexnum=6;
    int u = 0;
    int dis[vexnum];
    int mark[vexnum];
    for(int i=0; i<vexnum; i++)
    {
        mark[i] = 0;
        dis[i] = net[x][i];
    }
    mark[x]=1;
    for(int k=0; k<vexnum; k++)
    {
        min = 1000;
        for(int i=0; i<vexnum; i++)
        {
            if(mark[i]==0&&min>dis[i])
            {
                min = dis[i];
                u=i;
            }
        }
         mark[u]=1;
        for(int i=0;i<vexnum;i++)
        {
            if(!mark[i]&&dis[i]>dis[u]+net[u][i])
            {
                dis[i] = dis[u] + net[u][i];
            }
        }
    }
     printf("最短路径值为：%d\n",dis[y]);
}

void Dijkstra(string X,string Y)
{
    string Name[6]={"甲","乙","丙","丁","戊","己"};
    int x = 0,y = 0;
    int vexnum=6;
    for(int i=0;i<vexnum;i++)
    {
        if(X == Name[i])
        {
            x=i;
        }
        if(Y == Name[i])
        {
            y=i;
        }
    }
    D(x,y);
}

#endif
