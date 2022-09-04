#include"src/methods.h"
#include"src/problem.h"
#include"src/solution.h"
#include"src/simulation.h"
int main()
{
	Problem P;
	Solution S;
	Methods M;
	P.Set_file("crd501.txt");
	P.Ini_gragh();
	P.Ini_edge();
	M.Kruskal(P, S);
	system("pause");
	return 0;
}