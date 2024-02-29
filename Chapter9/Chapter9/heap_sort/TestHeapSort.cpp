#include "Assistance.h"				// 辅助软件包
#include "HeapSort.h"				// 堆排序算法

int main(void)
{
	vector<int> b;
	vector<int> a;
	clock_t start2, finish2,start3,finish3;
	double total_time2,total_time3;
	for (int i = 0; i < 50000000; i++)
	{
		b.push_back(rand());
		a.push_back(rand());
	}
	int m = 50000000;
	//cout << "排序前:";
	//Display(b, m);
	start3 = clock();
	HeapSort_3(b, m);					// 堆排序
	finish3 = clock();
	total_time3 = (double)(finish3 - start3) / CLOCKS_PER_SEC;
	//cout << "排序后:";
	//Display(b, m);
	cout << endl;
	cout << "运行时间：" << total_time3 << endl;

	//cout << "排序前:";
	//Display(a, m);
	start2 = clock();
	HeapSort_2(a, m); // 堆排序
	finish2 = clock();
	total_time2 = (double)(finish2 - start2) / CLOCKS_PER_SEC;
	//cout << "排序后:";
	//Display(a, m);
	cout << endl;
	cout << "运行时间：" << total_time2 << endl;
	system("PAUSE");				
	return 0;						
}
