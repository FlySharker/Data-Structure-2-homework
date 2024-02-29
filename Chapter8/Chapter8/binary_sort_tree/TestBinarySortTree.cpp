#include "Assistance.h"		// ���������
#include "BinarySortTree.h" // ������������

int main(void)
{
	BinarySortTree<int> bt;
	int elem[] = {39, 68, 11, 23, 46, 34, 75, 86, 8, 71, 50};
	BinarySortTree<int> bt2;
	int elem2[] = {39, 68, 11, 46, 50, 49, 53, 52, 56, 8, 75};
	BinarySortTree<int> bt3;
	int elem3[] = {39, 58, 11, 23, 46, 34, 75, 86, 8, 71, 50, 65, 69, 63, 61};
	int n = 11;
	int n2=11;
	int n3=15;
	int m;

	for (int i = 0; i < n; i++)
		bt.Insert(elem[i]); // ����elem�����е�Ԫ�ع������������

	for (int i = 0; i < n2; i++)
		bt2.Insert(elem2[i]); // ����elem�����е�Ԫ�ع������������

	for (int i = 0; i < n3; i++)
		bt3.Insert(elem3[i]); // ����elem�����е�Ԫ�ع������������

	cout << "ԭ����������:" << endl;
	DisplayBTWithTreeShape(bt);
	cout << endl;
	system("PAUSE");

	char c = 'x';
	int x;

	while (c != '0')
	{
		cout << endl
			 << "1. ����Ԫ��.";
		cout << endl
			 << "2. ����Ԫ��.";
		cout << endl
			 << "3. ɾ��Ԫ��.";
		cout << endl
			 << "4. �������.";
		cout << endl
			 << "5. �������.";
		cout << endl
			 << "6. �������.";
		cout << endl
			 << "7. ��ʾ����������.";
		cout << endl
			 << "0. �˳�";
		cout << endl
			 << "ѡ����(0~7):";
		cin >> c;
		switch (c)
		{
		case '1':
			cout << endl
				 << "�������Ԫ�ص�ֵ:";
			cin >> x;
			bt.Insert(x);
			break;
		case '2':
			cout << endl
				 << "�������Ԫ�ص�ֵ:";
			cin >> x;
			if (bt.Find(x) == NULL)
				cout << endl
					 << "Ԫ�ز�����.";
			else
				cout << endl
					 << "Ԫ�ش���.";
			break;
		case '3':
			cout << endl
				 <<"�ֶԵ�һ��������ɾ��"
				 <<endl
				 << "����ɾ��Ԫ�ص�ֵ:";
			cin >> x;
			cout << "��ѡ����ҷ�ʽ(1,2,3):";
			cin >> m;
			if (m == 1)
				bt.Delete(x);
			else if (m == 2)
				bt.Delete2(x);
			else if (m == 3)
				bt.Delete3(x);

			cout << endl
				 << "�ֶԵڶ���������ɾ��"
				 << endl
				 << "����ɾ��Ԫ�ص�ֵ:";
			cin >> x;
			cout << "��ѡ����ҷ�ʽ(1,2,3):";
			cin >> m;
			if (m == 1)
				bt2.Delete(x);
			else if (m == 2)
				bt2.Delete2(x);
			else if (m == 3)
				bt2.Delete3(x);

			cout << endl
				 << "�ֶԵ�����������ɾ��"
				 << endl
				 << "����ɾ��Ԫ�ص�ֵ:";
			cin >> x;
			cout << "��ѡ����ҷ�ʽ(1,2,3):";
			cin >> m;
			if (m == 1)
				bt3.Delete(x);
			else if (m == 2)
				bt3.Delete2(x);
			else if (m == 3)
				bt3.Delete3(x);
			break;
		case '4':
			cout << endl;
			bt.PreOrder(Write<int>);
			break;
		case '5':
			cout << endl;
			bt.InOrder(Write<int>);
			break;
		case '6':
			cout << endl;
			bt.PostOrder(Write<int>);
			break;
		case '7':
			cout << endl;
			DisplayBTWithTreeShape(bt);
			cout << endl;
			cout << endl;
			cout << endl;
			DisplayBTWithTreeShape(bt2);
			cout << endl;
			cout << endl;
			cout << endl;
			DisplayBTWithTreeShape(bt3);
			break;
		}
	}

	system("PAUSE");
	return 0;
}
