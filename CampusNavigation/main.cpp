#include "Header.h"

using namespace std;

int main(int argc, const char * argv[])
{
    Place p[6];
    string Name[6]={"甲","乙","丙","丁","戊","己"};
    for(int i=0;i<6;i++)
    {
        p[i].name=Name[i];
        p[i].number=i;
        p[i].introduction="这是"+p[i].name;
    }
    Dijkstra("甲", "己");
	system("pause");
	return 0;

}
