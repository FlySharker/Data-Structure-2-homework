#include "SqBinaryTree.h" // 顺序存储二叉树类

int main()
{
	int p;
	char c = 'a', e;
	int x, y, z;

	char pre[] = {'A', 'B', 'D', 'E', 'G', 'H', 'C', 'F', 'I'}; // 先序序列
	char in[] = {'D', 'B', 'G', 'E', 'H', 'A', 'C', 'F', 'I'};	// 中序序列
	int n = 9, size = 15;										// 结点个数
	SqBinaryTree<char> bt;
	bt = CreateBinaryTree(pre, in, n, size); // 构造二叉树

	cout << "由先序：A,B,D,E,G,H,C,F,I和中序：D,B,G,E,H,A,C,F,I构造的二叉树:" << endl;
	DisplayBTWithTreeShape<char>(bt);
	cout << endl;

	system("PAUSE");

	while (c != '0')
	{
		cout << endl
			 << "1. 插入左孩子.";
		cout << endl
			 << "2. 删除右子树.";
		cout << endl
			 << "3. 层次遍历";
		cout << endl
			 << "4. 先序遍历.";
		cout << endl
			 << "5. 中序遍历.";
		cout << endl
			 << "6. 后序遍历.";
		cout << endl
			 << "7. 求二叉树的结点数.";
		cout << endl
			 << "8. 求二叉树的高度.";
		cout << endl
			 << "9. 显示二叉排序树.";
		cout << endl
			 << "b. 求离两个节点最近的共同祖先.";
		cout << endl
			 << "0. 退出";
		cout << endl
			 << "选择功能(0~7):";
		cin >> c;
		switch (c)
		{
		case '1':
			cout << endl
				 << "输入被插入元素的值:";
			cin >> e;
			p = bt.Find(e);
			if (p == -1)
				cout << "该结点不存在！" << endl;
			else
			{
				cout << endl
					 << "输入插入元素的值:";
				cin >> e;
				bt.InsertLeftChild(p, e); // 插入左孩子
			}
			break;
		case '2':
			cout << endl
				 << "输入删除子树双亲元素的值:";
			cin >> e;
			p = bt.Find(e);
			if (p == -1)
				cout << "该结点不存在！" << endl;
			else
				bt.DeleteRightChild(p);
			break;
		case '3':
			cout << endl;
			bt.LevelOrder(Write<char>);
			break;
		case '4':
			cout << endl;
			bt.PreOrder(Write<char>);
			break;
		case '5':
			cout << endl;
			bt.InOrder(Write<char>);
			break;
		case '6':
			cout << endl;
			bt.PostOrder(Write<char>);
			break;
		case '7':
			cout << endl;
			cout << "二叉树的结点数为：" << bt.NodeCount() << endl;
			break;
		case '8':
			cout << endl;
			cout << "二叉树的高度为：" << bt.Height() << endl;
			break;
		case '9':
			cout << endl;
			DisplayBTWithTreeShape(bt);
			break;
		case 'b':
			cout << endl;
			cout << "输入两个结点的位置";
			cin >> x >> y;
			z = bt.NearSameParent(x, y);
			if (bt.GetElem(z, e) == FAIL)
				cout << "无";
			else
				cout << "最近的共同祖先为：" << e;
			break;
		}
	}

	system("PAUSE");
	return 0;
}
