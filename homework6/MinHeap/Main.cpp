#include <bits/stdc++.h>
#include "MinHeap.h"
using namespace std;
int main()
{
    int x[] = {80, 57, 99, 29, 23, 11, 74, 35, 62, 16};
    cout << "��ʼ�ѣ�";
    for (int i = 0; i < 10; i++)
        cout << x[i] << " ";
    MinHeap<int> mp(x, 100, 10);
    cout << endl;
    cout << "��С�ѣ�";
    mp.PrintheapArr();
    mp.MaxHeap(x, 100, 10);
    cout << endl;
    cout << "���ѣ�";
    mp.PrintheapArr();
    cout << endl;
    cout << "���β��빹����С��" << endl;
    cout << "��С�ѣ�";
    MinHeap<int> mmp(100);
    for (int i = 0; i < 10; i++)
    {
        mmp.Insert(x[i]);
    }
    mmp.PrintheapArr();
    return 0;
}