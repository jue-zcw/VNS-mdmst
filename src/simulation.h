#pragma once
#ifndef VNS_SRC_SIMULATION_H_
#define VNS_SRC_SIMULATION_H_
#include"src/head.h"
class Problem;
class Solution;
class Simulations
{
public:
	int check(Problem& p, Solution& s);//检验生成的Solution中，所有节点的度数是否只为1或d
};
#endif