#include <bits/stdc++.h>
#include "Parent_Children.h"
using namespace std;
int main()
{
    char items[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};
    int parents[] = {-1, 0, 0, 0, 1, 1, 3, 3, 2};
    int r = 0, n = 9;
    ParentChildrenTree<char> t(items, parents, r, n);
    printf("���Ĳ�α�����:");
    t.LevelOrder();
    printf("\n");
    printf("��Ӧ�������Ĳ�α����ǣ�");
    t.LevelOrder_binary();
    system("pause");
    return 0;
}