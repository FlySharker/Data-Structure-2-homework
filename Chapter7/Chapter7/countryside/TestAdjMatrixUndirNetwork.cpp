#include "Assistance.h"			 // ���������
#include "AdjMatrixUndirNetwork.h" // �ڽӾ�������ͼ

int main()
{
	try // ��try��װ���ܳ����쳣�Ĵ���
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
		// ����洢�ռ�
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
				cout << "ҽԺӦ�ý���" << c << "��ׯ" << endl;
				k++;
			}
			int flag = 1;
			char u, v;
			while(flag){
				cout << "������ʼĩ��ׯ��";
				cin >> u >> v;
				DisplayPathAndDist(g, path, dist,u,v);
				cout << endl;
				cout << "�Ƿ����ѯ�ʣ�";
				cin >> flag;
			}
			
	}
			catch (Error err) // ��׽�������쳣
			{
				err.Show(); // ��ʾ�쳣��Ϣ
			}

			system("PAUSE"); // ���ÿ⺯��system()
			return 0;		 // ����ֵ0, ���ز���ϵͳ
		}
