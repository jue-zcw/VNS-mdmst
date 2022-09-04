#include"src/Simulation.h"
#include"src/Problem.h"
#include"src/Solution.h"
int Simulations::check(Problem& p, Solution& s)
{
	for (int i = 0; i < p.Get_vexnum(); i++)
	{
		if (s.Get_vex(i) != 1 && s.Get_vex(i) != p.Get_mindegree())//检查图中节点度数是否符合要求，即所有节点的度数只能为d或1
		{
			cout << i << "的度数为" << s.Get_vex(i) << endl;
			return i;
		}
	}
	cout << "ok" << endl;
	return -1;
}