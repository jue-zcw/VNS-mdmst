#include"src/Problem.h"
NodeType Problem::Get_vex(int i)
{
	return G.vexs[i];
}
Edge Problem::Get_edge(int i)
{
	return edge[i];
}
int Problem::Set_file(const char* filename)
{
	const char* prefix = "MDMST_";
	file = filename;
	ofile = string(prefix) + string(file);
	return 0;
}
string Problem::Get_ofile()
{
	return ofile;
}
int Problem::Update_edge(int i)
{
	edge[i].used = 1;
	return 0;
}
int Problem::Get_vexnum()
{
	return G.vexnum;
}
int Problem::Get_arcnum()
{
	return arcnum;
}
int Problem::Get_mindegree()
{
	return d;
}
int Problem::Get_dis(int i,int j)
{
	if (i == j) return 32767;
	return G.arcs[i][j];
}
int Problem::Edge_exchange(int i, int j)//������
{
	int thead, ttail, tlowcost;
	thead = edge[i].head;
	ttail = edge[i].tail;
	tlowcost = edge[i].lowcost;
	edge[i].head = edge[j].head;
	edge[i].tail = edge[j].tail;
	edge[i].lowcost = edge[j].lowcost;
	edge[j].head = thead;
	edge[j].tail = ttail;
	edge[j].lowcost = tlowcost;
	return 0;
}
int Problem::Ini_edge()//��ʼ��edge���鲢���߰�Ȩֵ��С����
{
	arcnum = 0;
	for (int i = 0; i < G.vexnum; i++)
	{
		for (int j = i + 1; j < G.vexnum; j++)
		{
			edge[arcnum].head = i;
			edge[arcnum].tail = j;
			edge[arcnum].lowcost = G.arcs[i][j];
			edge[arcnum].used = 0;
			arcnum++;
		}
	}
	for (int i = 0; i <= arcnum; i++)
	{
		for (int j = i + 1; j <= arcnum - 1; j++)
		{
			if (edge[i].lowcost > edge[j].lowcost)
			{
				Edge_exchange(i, j);
			}

		}
	}
	return 0;
}
string Problem::Read_file(const char* filename, int line)/*��ȡ������txt�ļ���ĳ1�����ݵĺ���*/
{
	int i = 0;
	string temp;
	string tar;
	fstream file;
	file.open(filename, ios::in);
	if (line <= 0)
	{
		return "Error";
	}
	if (file.fail())
	{
		return "Error";
	}
	while (getline(file, temp) && i < line - 1)
	{
		i++;
	}
	file.close();
	return temp;
}
int Problem::Ini_gragh()//�����ڽӾ���
{
	int n = 0;
	G.vexnum = stoi(Read_file(file, 1)); //data.txt�ĵ�1��Ϊ�ڵ���
	for (int i = 0; i < G.vexnum; i++)
	{
		G.arcs[i][i] = 32767;
	}
	for (int k = 3; k < G.vexnum * 2 + 2; k++)//data.txt�ĵ�3����Ϊ�ڵ���Ϣ
	{
		G.vexs[n].num = n;
		G.vexs[n].x = stoi(Read_file(file, k));
		k++;
		G.vexs[n].y = stoi(Read_file(file, k));
		n++;
	}
	for (int i = 0; i < G.vexnum; i++)
	{
		for (int j = i + 1; j < G.vexnum; j++)
		{
			G.arcs[i][j] = G.arcs[j][i] = Distance(i, j);
		}
	}
	cout << "��������С����" << endl;
	cin >> d;
	return 0;
}
int Problem::Distance(int i, int j)//���㶥�㵽ͼ��������������ľ���
{
	double s = (G.vexs[i].x - G.vexs[j].x) * (G.vexs[i].x - G.vexs[j].x) + (G.vexs[i].y - G.vexs[j].y) * (G.vexs[i].y - G.vexs[j].y);
	s = sqrt(s);
	return int(s);
}
