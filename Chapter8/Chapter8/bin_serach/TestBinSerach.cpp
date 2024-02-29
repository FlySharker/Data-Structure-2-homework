#include "Assistance.h"					// 辅助软件包
#include "BinSerach.h"					// 顺序查找头文件

int main(void)
{
	int elem[] = {8, 11, 23, 34, 39, 46, 68, 71, 86};
	int n =9;
	int k = 71;
	int p = BinSerach(elem, n, k);		// 迭代的折半查找 
	if (p >= 0)	// 查找成功
		cout << "查找成功,元素" << k << "的位置为:" << p << endl;
	else	// 查找失败
		cout << "查找失败!" << endl;
  
    int low = 0, high = n-1;
    k = 23;
	p = BinSerach(elem, low, high, k);	// 递归的折半查找 
	if (p >= 0)	// 查找成功
		cout << "查找成功,元素" << k << "的位置为:" << p << endl;
	else	// 查找失败
		cout << "查找失败!" << endl;
    
	system("PAUSE");
	return 0;

}
