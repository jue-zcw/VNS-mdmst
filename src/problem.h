#pragma once
#ifndef VNS_SRC_PROBLEM_H_
#define VNS_SRC_PROBLEM_H_
#include"src/head.h"
typedef struct NodeType //�ڽӾ���ڵ㣬������š�X�����Y����
{
	int num;
	int x;
	int y;
}NodeType;
typedef struct //��ʾͼ���ڽӾ���
{
	NodeType vexs[100];
	int arcs[100][100];
	int vexnum;
}AMGraph;
struct Edge//�����飬����kruskal�㷨������ʼ��
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
	int Ini_gragh();//��ȡdata.txt�����ݹ����ڽӾ���
	int Set_file(const char* file);
	string Read_file(const char* filenam, int line);
	string Get_ofile();
private:
	const char* file;
	string ofile;
	int line;
	int d; //��С��
	int arcnum;
	Edge edge[10000];
	AMGraph G; //�ڽӾ���
	int Edge_exchange(int i, int j);
	int Distance(int i, int j);//���㶥�㵽ͼ��������������ľ���
};
#endif