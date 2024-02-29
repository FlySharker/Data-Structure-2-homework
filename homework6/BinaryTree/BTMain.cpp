#include <bits/stdc++.h>
#include "BT.h"
using namespace std;
int main()
{

	int k = 0, deep = 0, w[100] = {0}, m;
	BT<char> a;
	BTNode<char> *tree;
	cout << "���������д�����չ��������";
	a.CreateBT(tree);
	cout << "�������������";
	a.PreOrder(tree);
	cout << endl;
	cout << "�������������";
	a.InOrder(tree);
	cout << endl;
	cout << "�������������";
	a.PostOrder(tree);
	cout << endl;
	cout << "��״��ӡ��������" << endl;
	a.PrintTree(tree, 1);
	cout << endl;
	a.CountLeaf(tree, k);
	cout << "Ҷ�ӽ����ĿΪ��" << k << endl;
	cout << endl;
	cout << "������������" << endl;
	a.Revolut(tree);
	cout << "��״��ӡ��������" << endl;
	a.PrintTree(tree, 1);
	cout << endl;
	cout << "�����������ȣ�";
	a.CountBreadth(tree, deep, w, m);
	cout << m << endl;
	cout << "�ǵݹ����������������";
	a.Revolut(tree);
	a.NonRecurringInOrder(tree);
	return 0;
}