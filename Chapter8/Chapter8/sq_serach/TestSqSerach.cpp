#include "Assistance.h"		// 辅助软件包
#include "SqSerach.h"		// 顺序查找头文件

int main(void)
{
	int elem[] = {8, 11, 23, 34, 46, 57, 61, 72, 98};
	int n =9;
	int k = 57;
	int p = SqSerach(elem, n, k);
	if (p >= 0)	// 查找成功
		cout << "查找成功,元素" << k << "的位置为:" << p << endl;
	else		// 查找失败
		cout << "查找失败!" << endl;

	system("PAUSE");
	return 0;
}
