#pragma once
#ifndef VNS_SRC_PROBLEM_H_
#define VNS_SRC_PROBLEM_H_
#include"src/head.h"
typedef struct NodeType //邻接矩阵节点，包括序号、X坐标和Y坐标
{
	int num;
	int x;
	int y;
}NodeType;
typedef struct //表示图的邻接矩阵
{
	NodeType vexs[100];
	int arcs[100][100];
	int vexnum;
}AMGraph;
struct Edge//边数组，用于kruskal算法创建初始解
{
	int head;
	int tail;
	int lowcost;
	int used;
};
class Problem
{
public:
	NodeType Get_vex(int i);
	Edge Get_edge(int i);
	int Update_edge(int i);
	int Get_vexnum();
	int Get_arcnum();
	int Get_mindegree();
	int Get_dis(int i,int j);
	int Get_vex_x(int i);
	int Get_vex_y(int i);
	int Get_vex_num(int i);
	int Ini_edge();
	int Ini_gragh();//读取data.txt的内容构造邻接矩阵
	int Set_file(const char* file);
	string Read_file(const char* filenam, int line);
	string Get_ofile();
private:
	const char* file;
	string ofile;
	int line;
	int d; //最小度
	int arcnum;
	Edge edge[10000];
	AMGraph G; //邻接矩阵
	int Edge_exchange(int i, int j);
	int Distance(int i, int j);//计算顶点到图中所有其他顶点的距离
};
#endif