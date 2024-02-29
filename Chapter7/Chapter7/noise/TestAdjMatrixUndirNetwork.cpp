#include "Assistance.h"			 // 辅助软件包
#include "AdjMatrixUndirNetwork.h" // 邻接矩阵无向图

int main()
{
	ifstream infile("noise_in.txt", ios::in);
	int infity = DEFAULT_INFINITY;
	int n1, m1, k1;
	int a, b, w1;
	int **dist;
	infile >> n1 >> m1 >> k1;
	int vv[100];
	for (int i = 0; i < 10; i++)
		vv[i] = i;
	AdjMatrixUndirGraph<int, int> g1(vv, n1, 100);
	for (int i = 0; i < m1; i++)
	{
		
		infile >> a >> b >> w1;
		g1.InsertArc(a-1, b-1, w1);
	}
	dist = new int *[g1.GetVexNum()];
	for (int i = 0; i < g1.GetVexNum(); i++)
	{
		dist[i] = new int[g1.GetVexNum()];
	}
	ofstream outfile("noise_out.txt", ios::out);
	ShortestPathFloyd(g1, dist); // 用Floyd算法求最短路径
	for (int i = 0; i < k1;i++){
		infile >> a >> b;
		if (dist[a-1][b-1] == infity)
			outfile << "no path" << endl;
		else
			outfile << dist[a-1][b-1] << endl;
	}
	infile.close();
	outfile.close();
	system("PAUSE"); // 调用库函数system()
	return 0;		 // 返回值0, 返回操作系统
}

