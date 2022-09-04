#include"src/methods.h"
#include"src/problem.h"
#include"src/solution.h"
#include"src/simulation.h"
int Methods::Shaking(Problem& p, Solution& s)//��û���ҵ����ʵıߣ���ӵ��������ٵ���ͨ�����ĵ㼯����ѡ�����ʵĵ㣬����������һ���㼯���к��ʵ�ĳ��������
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
	if (parti < partj)//����ͨ����Ϊti�ĵ��������С
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
		cout << "ɾ����" << ci << "-" << ti << endl;
		cout << "��ӱ�" << ci << "-" << cj << endl;
		s.Update_vex(cj);
		s.Update_arc(ci,cj);
		for (int j = 0; j < p.Get_vexnum(); j++)
		{
			s.Update_parent(j, cj);
		}
	}
	else//����ͨ����Ϊtj�ĵ��������С
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
		cout << "ɾ����" << ci << "-" << tj << endl;
		cout << "��ӱ�" << ci << "-" << cj << endl;
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
	int change = 0;//���ڼ���Ƿ�ѡ�񵽺��ʵı�
	s.Reduce_arc(ti,tj);
	s.Reduce_vex(ti);
	s.Reduce_vex(tj);
	s.Update_parent(ti, ti);
	s.Update_parent(tj, tj);
	for (int i = 0; i < p.Get_vexnum(); i++)//�ֱ�ͼ����ti��tj�����ıߵ���ͨ������Ϊti��tj
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
	for (int i = 0; i < p.Get_vexnum(); i++)//�ֱ�����ͨ����Ϊti��tj�ĵ���ѡ�����ʵĵ�
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
	if (change == 1)//��ѡ�񵽵ıߣ�������ӵ�solution��
	{
		cout << "��ӱ�" << ti << "-" << tj << endl;
		minarc = 32767;
		s.Update_arc(ti,tj);
		s.Update_vex(ti);
		s.Update_vex(tj);
		for (int j = 0; j < p.Get_vexnum(); j++)
			s.Update_parent(j, ti);
	}
	else
	{
		cout << "ֻʣ�������򣬳���ɾ��" << ti << "-" << tj << endl;
		Shaking(p, s);
	}
	return 0;
}
int Methods::VNS(Problem& p, Solution& s)//�ӳ�ʼ��s��ѡ�����������ʵĵ㣬����������������һ����ɾ����������VNDѡ���µıߡ�
{
	maxarc = 0;
	ti = tj = -1;
	for (int i = 0; i < p.Get_vexnum(); i++)
	{
		if (s.Get_vex(i) != p.Get_mindegree() && s.Get_vex(i) != 1) //�����Ȳ�ΪdҲ��Ϊ1
		{
			for (int j = 0; j < p.Get_vexnum(); j++)
			{
				if (s.Get_arc(i,j) == 1 && p.Get_dis(i, j) > maxarc && s.Get_vex(j) != 1) //ѡ����õ�������ı�
				{
					maxarc = p.Get_dis(i, j);
					ti = i;
					tj = j;
				}
			}
		}
	}
	cout << "ɾ����" << ti << "-" << tj << endl;
	VND(p, s, ti, tj);
	return 0;
}
int Methods::Kruskal(Problem& p, Solution& s) //���ɳ�ʼ��
{
	cout << "Kruskal���ɳ�ʼ��" << endl;
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
	int n = si.check(p, s);//���ͼ�нڵ�����Ƿ����Ҫ�󣬼����нڵ�Ķ���ֻ��Ϊd��1
	while (n != -1)
	{
		VNS(p, s);//ʹ��VNS�㷨�������Ž�
		n = si.check(p, s);
	}
	Save_result(p, s);//������
	return 0;
}
int Methods::Save_result(Problem& p, Solution& s)
{
	bestsolution = 0;
	ofstream outfile(p.Get_ofile().c_str());
	outfile << p.Get_vexnum() << "	0	0	0	0" << "\n"; //����ڵ���Ϣ
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
				outfile << p.Get_vex(j).x << "	" << p.Get_vex(j).y << "	" << p.Get_vex(k).x << "	" << p.Get_vex(k).y << "	" << p.Get_dis(j, k) << "\n";//�������Ϣ
				//outfile << j <<"	"<< k << "	0	0	0" << "\n";
				s.Reduce_arc(k,j);
				bestsolution += p.Get_dis(j, k);
			}
		}
	}
	outfile << bestsolution << "	0	0	0	0" << "\n";
	return 0;
}
