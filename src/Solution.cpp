#include"src/methods.h"
#include"src/problem.h"
#include"src/solution.h"
#include"src/simulation.h"
int Solution::Get_vex(int i)
{
	return vexused[i];
}
int Solution::Get_arc(int i, int j)
{
	return arcused[i][j];
}
int Solution::Get_parent(int i)
{
	return parent[i];
}
int Solution::Update_vex(int i)
{
	vexused[i]++;
	return 0;
}
int Solution::Reduce_vex(int i)
{
	vexused[i]--;
	return 0;
}
int Solution::Update_arc(int i, int j)
{
	arcused[i][j] = 1;
	arcused[j][i] = 1;
	return 0;
}
int Solution::Reduce_arc(int i, int j)
{
	arcused[i][j] = 0;
	arcused[j][i] = 0;
	return 0;
}
int Solution::Update_parent(int i, int temp)
{
	parent[i] = temp;
	return 0;
}
int Solution::Reset(Problem& p)//÷ÿ÷√Ω‚
{
	for (int k = 0; k < p.Get_vexnum(); k++)
	{
		vexused[k] = 0;
		parent[k] = k;
	}
	for (int k = 0; k < p.Get_vexnum(); k++)
	{
		for (int i = 0; i < p.Get_vexnum(); i++)
		{
			arcused[k][i] = 0;
		}
	}
	return 0;
}