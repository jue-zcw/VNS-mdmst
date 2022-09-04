#include"src/methods.h"
#include"src/problem.h"
#include"src/solution.h"
#include"src/simulation.h"
int Methods::Shaking(Problem& p, Solution& s)//若没有找到合适的边，则从点数量较少的连通分量的点集合中选出合适的点，将其与另外一个点集合中合适的某点相连。
{
	s.Update_arc(ti, tj);
	s.Update_vex(ti);
	s.Update_vex(tj);
	int parti = 0;
	int partj = 0;
	int ci = -1;
	int cj = -1;
	minarc = 32767;
	for (int k = 0; k < p.Get_vexnum(); k++)
	{
		if (s.Get_parent(k) == ti) parti++;
		else if (s.Get_parent(k) == tj) partj++;
	}
	if (parti < partj)//若连通分量为ti的点的数量较小
	{
		for (int i = 0; i < p.Get_vexnum(); i++)
		{
			if (i != ti && s.Get_parent(i) == ti && s.Get_arc(i,ti) == 1)
			{
				for (int j = 0; j < p.Get_vexnum(); j++)
				{
					if (s.Get_vex(j) == p.Get_mindegree() - 1 && s.Get_parent(j) == tj && p.Get_dis(i, j) < minarc)
					{
						ci = i;
						cj = j;
						minarc = p.Get_dis(i,j);
					}
				}
			}
		}
		s.Reduce_arc(ci, ti);
		s.Reduce_vex(ti);
		cout << "删除边" << ci << "-" << ti << endl;
		cout << "添加边" << ci << "-" << cj << endl;
		s.Update_vex(cj);
		s.Update_arc(ci,cj);
		for (int j = 0; j < p.Get_vexnum(); j++)
		{
			s.Update_parent(j, cj);
		}
	}
	else//若连通分量为tj的点的数量较小
	{
		for (int i = 0; i < p.Get_vexnum(); i++)
		{
			if (i != tj && s.Get_parent(i) == tj && s.Get_arc(i,tj) == 1)
			{
				for (int j = 0; j < p.Get_vexnum(); j++)
				{
					if (s.Get_vex(j) == p.Get_mindegree() - 1 && s.Get_parent(j) == ti && p.Get_dis(i, j) < minarc)
					{
						ci = i;
						cj = j;
						minarc = p.Get_dis(i, j);
					}
				}
			}
		}
		s.Reduce_arc(ci, tj);
		s.Reduce_vex(tj);
		cout << "删除边" << ci << "-" << tj << endl;
		cout << "添加边" << ci << "-" << cj << endl;
		s.Update_vex(cj);
		s.Update_arc(ci,cj);
		for (int j = 0; j < p.Get_vexnum(); j++)
		{
			s.Update_parent(j, cj);
		}
	}
	return 0;
}
int Methods::VND(Problem& p, Solution& s, int ti, int tj)
{
	int change = 0;//用于检查是否选择到合适的边
	s.Reduce_arc(ti,tj);
	s.Reduce_vex(ti);
	s.Reduce_vex(tj);
	s.Update_parent(ti, ti);
	s.Update_parent(tj, tj);
	for (int i = 0; i < p.Get_vexnum(); i++)//分别将图中与ti或tj相连的边的连通分量置为ti或tj
	{
		for (int j = 0; j < p.Get_vexnum(); j++)
		{
			for (int k = 0; k < p.Get_vexnum(); k++)
			{
				if (s.Get_arc(j,k) == 1)
				{
					if (s.Get_parent(j) == ti || s.Get_parent(k) == ti)
					{
						s.Update_parent(j, ti);
						s.Update_parent(k, ti);
					}
					if (s.Get_parent(j) == tj || s.Get_parent(k) == tj)
					{
						s.Update_parent(j, tj);
						s.Update_parent(k, tj);
					}
				}
			}
		}
	}
	for (int i = 0; i < p.Get_vexnum(); i++)//分别在连通分量为ti、tj的点中选出合适的点
	{
		if (s.Get_vex(i) != p.Get_mindegree() && s.Get_vex(i) != 1 && s.Get_parent(i) == ti)
		{
			for (int j = 0; j < p.Get_vexnum(); j++)
			{
				if (s.Get_vex(j) != p.Get_mindegree() && s.Get_vex(j) != 1 && s.Get_parent(j) == tj && p.Get_dis(i, j) < minarc)
				{
					ti = i;
					tj = j;
					minarc = p.Get_dis(i, j);
					change = 1;
				}
			}
		}
	}
	if (change == 1)//有选择到的边，则将其添加到solution中
	{
		cout << "添加边" << ti << "-" << tj << endl;
		minarc = 32767;
		s.Update_arc(ti,tj);
		s.Update_vex(ti);
		s.Update_vex(tj);
		for (int j = 0; j < p.Get_vexnum(); j++)
			s.Update_parent(j, ti);
	}
	else
	{
		cout << "只剩两个邻域，撤销删除" << ti << "-" << tj << endl;
		Shaking(p, s);
	}
	return 0;
}
int Methods::VNS(Problem& p, Solution& s)//从初始解s中选出度数不合适的点，将与其相连的其中一条边删除，并调用VND选出新的边。
{
	maxarc = 0;
	ti = tj = -1;
	for (int i = 0; i < p.Get_vexnum(); i++)
	{
		if (s.Get_vex(i) != p.Get_mindegree() && s.Get_vex(i) != 1) //度数既不为d也不为1
		{
			for (int j = 0; j < p.Get_vexnum(); j++)
			{
				if (s.Get_arc(i,j) == 1 && p.Get_dis(i, j) > maxarc && s.Get_vex(j) != 1) //选出与该点相连最长的边
				{
					maxarc = p.Get_dis(i, j);
					ti = i;
					tj = j;
				}
			}
		}
	}
	cout << "删除边" << ti << "-" << tj << endl;
	VND(p, s, ti, tj);
	return 0;
}
int Methods::Kruskal(Problem& p, Solution& s) //生成初始解
{
	cout << "Kruskal生成初始解" << endl;
	Simulations si;
	ti = 0;
	tj = 0;
	maxarc = 0;
	minarc = 32767;
	bestsolution = 32767;
	s.Reset(p);
	int v1, v2, vs1, vs2;
	for (int i = 0; i < p.Get_arcnum(); i++)
	{
		v1 = p.Get_edge(i).head;
		v2 = p.Get_edge(i).tail;
		vs1 = s.Get_parent(v1);
		vs2 = s.Get_parent(v2);
		if (vs1 != vs2)
		{
			cout << p.Get_edge(i).head << "-" << p.Get_edge(i).tail << " distance= " << p.Get_edge(i).lowcost << endl;
			p.Update_edge(i);
			s.Update_arc(v1,v2);
			s.Update_vex(v1);
			s.Update_vex(v2);
			for (int j = 0; j < p.Get_vexnum(); j++)
				if (s.Get_parent(j) == vs2) s.Update_parent(j,vs1);
		}
	}
	int n = si.check(p, s);//检查图中节点度数是否符合要求，即所有节点的度数只能为d或1
	while (n != -1)
	{
		VNS(p, s);//使用VNS算法更新最优解
		n = si.check(p, s);
	}
	Save_result(p, s);//保存结果
	return 0;
}
int Methods::Save_result(Problem& p, Solution& s)
{
	bestsolution = 0;
	ofstream outfile(p.Get_ofile().c_str());
	outfile << p.Get_vexnum() << "	0	0	0	0" << "\n"; //输出节点信息
	outfile << p.Get_vexnum() << "	0	0	0	0" << "\n";
	for (int i = 0; i < p.Get_vexnum(); i++)
	{
		outfile << p.Get_vex(i).num << "	" << p.Get_vex(i).x << "	" << p.Get_vex(i).y << "	0	0" << "\n";
	}
	for (int j = 0; j < p.Get_vexnum(); j++)
	{
		for (int k = 0; k < p.Get_vexnum(); k++)
		{
			if (s.Get_arc(j,k) == 1)
			{
				outfile << p.Get_vex(j).x << "	" << p.Get_vex(j).y << "	" << p.Get_vex(k).x << "	" << p.Get_vex(k).y << "	" << p.Get_dis(j, k) << "\n";//输出边信息
				//outfile << j <<"	"<< k << "	0	0	0" << "\n";
				s.Reduce_arc(k,j);
				bestsolution += p.Get_dis(j, k);
			}
		}
	}
	outfile << bestsolution << "	0	0	0	0" << "\n";
	return 0;
}
