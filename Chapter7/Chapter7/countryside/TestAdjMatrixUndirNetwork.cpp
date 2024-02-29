#include "Assistance.h"			 // 辅助软件包
#include "AdjMatrixUndirNetwork.h" // 邻接矩阵无向图

int main()
{
	try // 用try封装可能出现异常的代码
	{
		int N,M,pa;
		char na, name[100], a, b;
		cin >> N;
		for (int i = 0; i < N;i++){
			cin >> na;
			name[i] = na;
		}
		AdjMatrixUndirGraph<char, int> g(name, N, 20);
		cin >> M;
		for (int i = 0; i < M;i++){
			cin >> a >> b >> pa;
			g.InsertArc(a, b, pa);
		}
		int **dist, **path;
		// 分配存储空间
		dist = new int *[g.GetVexNum()], path = new int *[g.GetVexNum()];
		for (int i = 0; i < g.GetVexNum(); i++)
		{
			dist[i] = new int[g.GetVexNum()];
			path[i] = new int[g.GetVexNum()];
		}
		ShortestPathFloyd(g, path,dist);
		int sum = 0, sum1 = 10000;
		int pos[100], k = 0;
		for (int i = 0; i < 100; i++)
		{
			pos[i] = -1;
		}
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					sum += dist[i][j];
				}
				if (sum1 >= sum)
				{
					if (sum1 == sum)
					{
						pos[k] = i;
						k++;
					}
					else
					{
						pos[k] = i;
					}
					sum1 = sum;
				}
				sum = 0;
			}
			k = 0;
			while (pos[k] != -1)
			{
				char c = pos[k] + 'A';
				cout << "医院应该建在" << c << "村庄" << endl;
				k++;
			}
			int flag = 1;
			char u, v;
			while(flag){
				cout << "请输入始末村庄：";
				cin >> u >> v;
				DisplayPathAndDist(g, path, dist,u,v);
				cout << endl;
				cout << "是否继续询问：";
				cin >> flag;
			}
			
	}
			catch (Error err) // 捕捉并处理异常
			{
				err.Show(); // 显示异常信息
			}

			system("PAUSE"); // 调用库函数system()
			return 0;		 // 返回值0, 返回操作系统
		}
