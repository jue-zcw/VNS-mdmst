#pragma once
#ifndef VNS_SRC_METHODS_H_
#define VNS_SRC_METHODS_H_
#include"src/head.h"
class Problem;
class Solution;
class Methods
{
public:
	int Update_G(Problem& p, Solution& s);//����kruskal�㷨��ѡ�񵽵ıߣ�����arcused��vexused����
	int Kruskal(Problem& p, Solution& s);//ѡ��ͼ�з���Ҫ�����С�ߣ����ñߺ��䶥������
	int VNS(Problem& p, Solution& s);//VNS�㷨
	int VND(Problem& p, Solution& s, int i, int j);
	int Shaking(Problem& p, Solution& s);
	int Save_result(Problem& p, Solution& s);//VNS�㷨
private:
	int ti;
	int tj;
	int minarc;
	int maxarc;
	int bestsolution;
};
#endif