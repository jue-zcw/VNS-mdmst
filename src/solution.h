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
	int Reset(Problem& p);//���ý⣬��ʼ��һ�ֵ�kruskal
private:
	int vexused[100]; //��¼��ǰѡ�нڵ������
	int arcused[100][100];//��¼��ǰѡ�бߵ�����
	int parent[100]; //��¼�ڵ�֮ǰ�Ƿ���ͨ�����飬�������ڵ㻥����ͨʱ���ɽڵ�С�Ľڵ���Ϊ�������ڵ��parent[]�е�ֵ��
};
#endif