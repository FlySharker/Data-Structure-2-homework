#include <bits/stdc++.h>
#include "MinHeap.h"
using namespace std;
int main()
{
    int x[] = {80, 57, 99, 29, 23, 11, 74, 35, 62, 16};
    cout << "初始堆：";
    for (int i = 0; i < 10; i++)
        cout << x[i] << " ";
    MinHeap<int> mp(x, 100, 10);
    cout << endl;
    cout << "最小堆：";
    mp.PrintheapArr();
    mp.MaxHeap(x, 100, 10);
    cout << endl;
    cout << "最大堆：";
    mp.PrintheapArr();
    cout << endl;
    cout << "依次插入构建最小堆" << endl;
    cout << "最小堆：";
    MinHeap<int> mmp(100);
    for (int i = 0; i < 10; i++)
    {
        mmp.Insert(x[i]);
    }
    mmp.PrintheapArr();
    return 0;
}