#include"src/Simulation.h"
#include"src/Problem.h"
#include"src/Solution.h"
int Simulations::check(Problem& p, Solution& s)
{
	for (int i = 0; i < p.Get_vexnum(); i++)
	{
		if (s.Get_vex(i) != 1 && s.Get_vex(i) != p.Get_mindegree())//���ͼ�нڵ�����Ƿ����Ҫ�󣬼����нڵ�Ķ���ֻ��Ϊd��1
		{
			cout << i << "�Ķ���Ϊ" << s.Get_vex(i) << endl;
			return i;
		}
	}
	cout << "ok" << endl;
	return -1;
}