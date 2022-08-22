#pragma once
#ifndef VNS_SRC_METHODS_H_
#define VNS_SRC_METHODS_H_
#include"src/head.h"
class Problem;
class Solution;
class Methods
{
public:
	int Update_G(Problem& p, Solution& s);//根据kruskal算法中选择到的边，更新arcused和vexused数组
	int Kruskal(Problem& p, Solution& s);//选出图中符合要求的最小边，将该边和其顶点加入解
	int VNS(Problem& p, Solution& s);//VNS算法
	int VND(Problem& p, Solution& s, int i, int j);
	int Shaking(Problem& p, Solution& s);
	int Save_result(Problem& p, Solution& s);//VNS算法
private:
	int ti;
	int tj;
	int minarc;
	int maxarc;
	int bestsolution;
};
#endif