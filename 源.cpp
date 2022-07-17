#include<iostream>
#include<windows.h>
using namespace std;
#define MAX_VEX 10
#define MVNum 100
typedef struct ArcNode{
	int adjvex;
	struct ArcNode* nextarc;
}ArcNode;
typedef struct 
{
	int data;
	ArcNode* firstarc;
}VNode,AdjList[MVNum];
typedef struct
{
	AdjList g;
	int vexnum, arcnum;
}ALGraph;
void ini_gragh(ALGraph& G);
int getd(ALGraph G, int dnum[]);
int Kruskal(ALGraph G, int dnum[], int best_solution[]);
int VNS(ALGraph G, ArcNode* p, int dNode[], int used[], int count, int maxcount, int dNodenum,int best_solution[],int T[]);
int main()
{
	ALGraph G;
	int dnum[100];
	int best_solution[100];
	ini_gragh(G);
	getd(G, dnum);
	Kruskal(G, dnum, best_solution);
	system("pause");
	return 0;
}
int VNS(ALGraph G, ArcNode* p, int dNode[], int used[], int count, int maxcount, int dNodenum, int best_solution[], int T[]) {
	while (p != NULL)
	{
		for (int i=0;i<dNodenum;i++) {
			if (p->adjvex == dNode[i] && used[dNode[i]] == 0) { //防止重复选取同一节点
				used[dNode[i]] = 1;
				count++;
				T[count] = dNode[i];
				if (count > maxcount) { //若新的解T'更优，则将其选为best_solution。
					maxcount = count;
					for (int j = 0; j <= maxcount; j++) {
						best_solution[j] = T[j];
					}
				}
				VNS(G,G.g[dNode[i]].firstarc, dNode, used, count, maxcount, dNodenum, best_solution, T); //在节点附近相邻区域重复调用VNS.
				used[dNode[i]] = 0;
			}
		}
		p = p->nextarc;
	}
	return 0;
}
int Kruskal(ALGraph G, int dnum[], int best_solution[]) {
	int dNode[100];
	int used[100];
	int T[100];
	int dNodenum = 0;
	int maxcount = 1;
	int d;
	cout << "输入最小度" << endl;
	cin >> d;
	for (int i = 0; i < G.vexnum; i++)//选出度数不小于d的节点，加入dNode[]数组中
	{
		if (dnum[i] < d) continue;
		dNode[dNodenum] = i;
		dNodenum++;
	}
	for (int i = 0; i < G.vexnum; i++) {
		best_solution[i] = -1;
	}
	for (int j = 0; j < dNodenum; j++) { //依次将dnum[]中的节点作为表头，调用VNS()来寻找邻接节点，用maxcount来记录最小生成树。
		int count = 0;
		for (int i = 0; i < G.vexnum; i++) {
			used[i] = 0;
		}
		ArcNode* p;
		p = G.g[dNode[j]].firstarc;
		used[dNode[j]] = 1;
		T[0] = dNode[j];
		VNS(G,p, dNode, used,count,maxcount,dNodenum, best_solution,T);
	}
	cout << "度约束最小生成树中的内部节点：" << endl;
	for (int k = 0; k < dNodenum; k++) {
		cout << best_solution[k] << "-";
	}
	cout << endl;
	cout << "度约束最小生成树中的内部节点与叶子的边" << endl;
	for(int m=0;m<dNodenum;m++){
		ArcNode* r;
		r = G.g[best_solution[m]].firstarc;
		while (r != NULL) {
			if (dnum[r->adjvex] == 1) {
				cout << best_solution[m] << "-" << r->adjvex << endl;
			}
			r = r->nextarc;
		}
	}
	return 0;
}
int getd(ALGraph G,int dnum[]) { //计算所有节点的度数
	for (int i = 0; i < G.vexnum; i++)
	{
		ArcNode *p;
		p = G.g[i].firstarc;
		int n = 0;
		while (p!= NULL) {
			n++;
			p = p->nextarc;
		}
		dnum[i] = n;
	}
	return 0;
}
void ini_gragh(ALGraph& G) { //创建邻接表
	int i, j;
	ArcNode *p1,*p2;
	cout << "输入节点数和边数" << endl;
	cin >> G.vexnum >> G.arcnum;
	for (int i = 0; i < G.vexnum; i++) {
		G.g[i].data=i;
		G.g[i].firstarc = NULL;
	}
	cout << "输入各边的起点与终点" << endl;
	for (int k = 0; k < G.arcnum; k++){
		cin >> i >> j;
		p1 = new ArcNode;
		p1->adjvex = j;
		p1->nextarc = G.g[i].firstarc;
		G.g[i].firstarc = p1;
		p2 = new ArcNode;
		p2->adjvex = i;
		p2->nextarc = G.g[j].firstarc;
		G.g[j].firstarc = p2;
	}
}
/*
论文图1的测试用例：
10 9
0 2 
1 4
2 3
2 4
3 5
3 7
4 8
6 8
8 9
3
----------------------------
10 9
0 2
2 3
2 4
1 4
4 5
4 7
4 8
6 8
8 9
3
*/
