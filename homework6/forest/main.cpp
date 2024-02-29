#include <iostream>
#include <stdlib.h>
#include <queue>
#include <algorithm>
using namespace std;
const int maxsize = 200;
char t[maxsize];   //二叉树顺序存储 

class TreeNode  //叶子结点类 
{
public:
	int child = -1;    //孩子结点在数组中的序号，未赋值时或末尾为-1 
	TreeNode *next = NULL;  //指向下一个结点 
};
class TreeBox  //双亲表示法数组类 
{ 
public:
	int parent;							 // 双亲下标
	char data;							 // 数据
	TreeNode *firstchild = new TreeNode; // 指向第一个孩子
};
// 树本体
class Tree
{
public:
	Tree();
	void visit(int p);    //访问结点 
	void PreOrder(int p);   //先根遍历 
	void PostOrder(int p);  //后根遍历 
	int root; // 根节点

	int Height(int r);    //求树的高度 
	int FirstChild(int cur) const;  //返回第一个孩子 
	int RightSibling(int cur) const;  //返回右兄弟 
	int GetRoot() const;   
	int Leaf();     //求树的叶子数 
	int Binary_Height(int *h);  //求相应二叉树的高度 
	int Binary_Leaf();   //求相应二叉树叶子数 
	void Order(int tnum);  //森林转化为二叉树 
	int bh[maxsize];     // 
	Tree *next = NULL;   //指向森林中的下一棵树 
	TreeBox *nodes;     //双亲表示法数组

private:
	int r, n;    //根下标，总结点个数 
};

Tree::Tree()  //构造函数 
{
	char A;
	int p, num;
	TreeNode *newp = NULL;
	cout << "输入节点数：";
	cin >> num;
	nodes = new TreeBox[num];
	for (int i = 0; i < num; i++)
	{
		cout << "输入节点：";
		cin >> A;
		nodes[i].data = A;
		cout << "输入节点双亲位置下标：";
		cin >> p;
		nodes[i].parent = p;
		if (p == -1)
		{
			root = i;
			r = i;
		}
		if (p != i && p != -1)
		{
			newp = nodes[p].firstchild;
			while (newp->next != NULL && newp->child != -1)
				newp = newp->next;
			newp->next = new TreeNode;
			newp->child = i;
			newp->next->child = -1;
			newp->next->next = NULL;
		}
		// r = 0;
		n = num;
	}
}
void Tree::visit(int p)
{
	cout << nodes[p].data << " ";
}
// 单树先根遍历
void Tree::PreOrder(int p)
{
	if (p >= 0 && p < n)
	{			  // p范围合法
		visit(p); // 访问根结点
		for (int child = FirstChild(p); child != -1; child = RightSibling(child))
			PreOrder(child); // 依次先根序遍历每棵子树
	}
}
// 单树后根遍历
void Tree::PostOrder(int p)
{
	if (p >= 0 && p < n)
	{ // p范围合法
		for (int child = FirstChild(p); child != -1; child = RightSibling(child))
			PostOrder(child); // 依次后根序遍历每棵子树
		visit(p);			  // 访问根结点
	}
}

int Tree::Height(int r)
// 操作结果：返回以r为根的树的高
{
	int child, h, maxHeight = 0;
	if (r < 0 || r >= n)
		return 0;
	else
	{
		for (child = FirstChild(r); child != -1; child = RightSibling(child))
		{
			h = Height(child); // 求各子树的高
			maxHeight = (maxHeight < h) ? h : maxHeight;
			// 求各子树高的最大值
		}
		return maxHeight + 1; // 树高为各子树的最大值再加1
	}
}

int Tree::FirstChild(int cur) const
// 操作结果：如cur无孩子,则返回-1,否则返回树结点cur的第一个孩子,
{
	if (cur < 0 || cur >= n)
		return -1; // 结点cur不存在,返回-1表示无孩子

	if (nodes[cur].firstchild == NULL) // 无孩子
		return -1;
	else
		return nodes[cur].firstchild->child; // 取出第一个孩子
}

int Tree::RightSibling(int cur) const
// 操作结果：如果结点cur无右兄弟,则返回-1,否则返回cur的右兄弟
{
	if (cur < 0 || cur >= n)
		return -1; // 结点cur不存在,返回-1表示无孩子

	int pt = nodes[cur].parent; // cur的双亲
	TreeNode *p = nodes[pt].firstchild;
	while (p != NULL && p->child != cur)
		p = p->next;
	if (p == NULL || p->next == NULL)
		return -1; // 反回右兄弟
	else
		return p->next->child; // 表示无右兄弟
}

int Tree::GetRoot() const    
{
	return r;
}

int Tree::Leaf()    //求单树的叶子数 
{
	int cnt = 0;
	for (int i = 0; i < n; i++)
	{
		if (nodes[i].firstchild->child == -1)
			cnt++;
	}
	return cnt;
}

int Tree::Binary_Height(int *h)  //求相应二叉树高度 
{
	int maxx = 0;
	int j = 1;             
	for (int i = 0; i < n; i++)
	{
		TreeNode *p = nodes[i].firstchild;
		while (p != NULL && p->child != -1)    // 记录每个结点的高度 
		{
			h[p->child] = h[i] + j;
			j++;
			p = p->next;
		}
		j = 1;
	}
	for (int i = 0; i < n; i++)
	{
		maxx = max(maxx, h[i]);
	}
	return maxx;
}
 
int Tree::Binary_Leaf()   //求二叉树叶子数 
{
	int leaf = 0;
	for (int i = 0; i < n; i++)
	{
		if (i == root)
		{
			if (nodes[i].firstchild == NULL)
			{
				leaf++;
			}
		}
		else
		{
			int rs = RightSibling(i);
			if (nodes[i].firstchild->child == -1 && rs == -1)
			{
				leaf++;
			}
		}
	}
	return leaf;
}

void Tree::Order(int tnum)   //转化为二叉树 
{
	t[tnum] = nodes[root].data;
	bh[root] = tnum;      //记录结点位置 
	for (int i = 0; i < n; i++)
	{
		if (nodes[i].firstchild->child != -1)
		{
			tnum = bh[i];
			t[2 * tnum + 1] = nodes[nodes[i].firstchild->child].data;  //孩子结点接入左子树 
			bh[nodes[i].firstchild->child] = 2 * tnum + 1;
			int nex = 2 * tnum + 1;
			TreeNode *p = nodes[i].firstchild->next;    
			while (p->child != -1 && p != NULL)    //兄弟结点接入右子树 
			{
				t[2 * nex + 2] = nodes[p->child].data;
				bh[p->child] = 2 * nex + 2;
				nex = 2 * nex + 2;
				p = p->next;
			}
		}
	}
}

void HG(int index)   //后根遍历输出 
{
	if (t[index] == '0')
	{
		return;
	}
	// 左递归
	if ((index * 2 + 1) < maxsize)
	{
		HG(index * 2 + 1);
	}
	// 右递归
	if ((index * 2 + 2) < maxsize)
	{
		HG(index * 2 + 2);
	}
	// 输出结点
	cout << t[index] << " ";
}

//////////////////////////////////////////////////////////////////////////////////
// 选择功能
int choose()
{
	int i;
	cout << "1:输入树以创建森林\n"
		 << "2:求森林规模\n"
		 << "3:求森林高度\n"
		 << "4:求森林叶子数\n"
		 << "5:求相应二叉树高度\n"
		 << "6:求相应二叉树叶子数\n"
		 << "7:先根遍历\n"
		 << "8:中根遍历\n"
		 << "9:后根遍历\n"
		 << "0:退出\n"
		 << "选择功能：";
	std::cin >> i;
	return i;
}

int main()
{
	Tree *Forest = NULL;
	int count_tree = 0;
	int h[maxsize];
	int MaxHeight = 0;
	int k = 1;
	int l = 0;
	int pos = 0;   
	for (int i = 0; i < maxsize; i++)
	{
		t[i] = '0';
	}
	while (1)
	{
		Tree *head_temp = Forest;
		int i = choose();
		// 创建树（多次循环实现创建森林） 
		if (i == 1)
		{
			if (Forest == NULL)
			{
				Forest = new Tree;
			}
			else
			{
				while (head_temp->next != NULL)
					head_temp = head_temp->next;
				head_temp->next = new Tree;
				head_temp->next->next = NULL;
				cout << head_temp->root << "	root\n";
			}

			cout << "创建树完成\n\n";
		}
		// 森林规模
		else if (i == 2)
		{
			int count = 0;
			while (head_temp != NULL)
			{
				count++;
				head_temp = head_temp->next;
			}
			cout << "森林规模为 " << count << "\n";
		}
		// 森林高度
		else if (i == 3)
		{
			int height = 0;
			int height_temp;
			while (head_temp != NULL)
			{
				height_temp = head_temp->Height(head_temp->root);
				if (height_temp >= height)
					height = height_temp;
				head_temp = head_temp->next;
			}
			cout << "森林高度为 " << height << "\n";
		}
		// 森林叶子数
		else if (i == 4)
		{
			int leaf = 0;
			while (head_temp != NULL)
			{
				leaf += head_temp->Leaf();
				head_temp = head_temp->next;
			}
			cout << "森林叶子数为：" << leaf << "\n";
		}
		// 二叉树高度
		else if (i == 5)
		{
			while (head_temp != NULL)
			{
				for (int i = 0; i < 10; i++)
				{
					h[i] = k;
				}
				MaxHeight = max(MaxHeight, head_temp->Binary_Height(h));
				k++;
				head_temp = head_temp->next;
			}
			cout << "对应二叉树的高度为：" << MaxHeight << "\n";
		}
		// 二叉树叶子
		else if (i == 6)
		{
			while (head_temp != NULL)
			{
				l += head_temp->Binary_Leaf();
				head_temp = head_temp->next;
			}
			cout << "对应二叉树的叶子数为：" << l << "\n";
		}
		// 先根
		else if (i == 7)
		{
			while (head_temp != NULL)
			{
				head_temp->PreOrder(head_temp->root);
				head_temp = head_temp->next;
			}
		}
		// 中根遍历
		else if (i == 8)
		{
			while (head_temp != NULL)
			{
				head_temp->PostOrder(head_temp->root);
				head_temp = head_temp->next;
			}
		}
		// 后根遍历 
		else if (i == 9)
		{
			while (head_temp != NULL)
			{
				head_temp->Order(pos);
				pos = 2 * pos + 2;   //每棵树的根转化为二叉树右孩子下标 
				head_temp = head_temp->next;
			}
			HG(0);    //递归输出 
		}
		else if (i == 0)
			break;
		cout << "--------------------------------------------------------------\n";
	}

	return 0;
}
