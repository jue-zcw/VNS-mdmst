#pragma once
#ifndef VNS_SRC_SOLUTION_H_
#define VNS_SRC_SOLUTION_H_
class Solution
{
public:
	int Get_vex(int i);
	int Get_arc(int i, int j);
	int Get_parent(int i);
	int Update_vex(int i);
	int Reduce_vex(int i);
	int Update_arc(int i, int j);
	int Reduce_arc(int i, int j);
	int Update_parent(int i, int temp);
	int Reset(Problem& p);//重置解，开始新一轮的kruskal
private:
	int vexused[100]; //记录当前选中节点的数组
	int arcused[100][100];//记录当前选中边的数组
	int parent[100]; //记录节点之前是否连通的数组，当两个节点互相连通时，由节点小的节点作为这两个节点的parent[]中的值。
};
#endif