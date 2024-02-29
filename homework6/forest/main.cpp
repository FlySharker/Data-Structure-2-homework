#include <iostream>
#include <stdlib.h>
#include <queue>
#include <algorithm>
using namespace std;
const int maxsize = 200;
char t[maxsize];   //������˳��洢 

class TreeNode  //Ҷ�ӽ���� 
{
public:
	int child = -1;    //���ӽ���������е���ţ�δ��ֵʱ��ĩβΪ-1 
	TreeNode *next = NULL;  //ָ����һ����� 
};
class TreeBox  //˫�ױ�ʾ�������� 
{ 
public:
	int parent;							 // ˫���±�
	char data;							 // ����
	TreeNode *firstchild = new TreeNode; // ָ���һ������
};
// ������
class Tree
{
public:
	Tree();
	void visit(int p);    //���ʽ�� 
	void PreOrder(int p);   //�ȸ����� 
	void PostOrder(int p);  //������� 
	int root; // ���ڵ�

	int Height(int r);    //�����ĸ߶� 
	int FirstChild(int cur) const;  //���ص�һ������ 
	int RightSibling(int cur) const;  //�������ֵ� 
	int GetRoot() const;   
	int Leaf();     //������Ҷ���� 
	int Binary_Height(int *h);  //����Ӧ�������ĸ߶� 
	int Binary_Leaf();   //����Ӧ������Ҷ���� 
	void Order(int tnum);  //ɭ��ת��Ϊ������ 
	int bh[maxsize];     // 
	Tree *next = NULL;   //ָ��ɭ���е���һ���� 
	TreeBox *nodes;     //˫�ױ�ʾ������

private:
	int r, n;    //���±꣬�ܽ����� 
};

Tree::Tree()  //���캯�� 
{
	char A;
	int p, num;
	TreeNode *newp = NULL;
	cout << "����ڵ�����";
	cin >> num;
	nodes = new TreeBox[num];
	for (int i = 0; i < num; i++)
	{
		cout << "����ڵ㣺";
		cin >> A;
		nodes[i].data = A;
		cout << "����ڵ�˫��λ���±꣺";
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
// �����ȸ�����
void Tree::PreOrder(int p)
{
	if (p >= 0 && p < n)
	{			  // p��Χ�Ϸ�
		visit(p); // ���ʸ����
		for (int child = FirstChild(p); child != -1; child = RightSibling(child))
			PreOrder(child); // �����ȸ������ÿ������
	}
}
// �����������
void Tree::PostOrder(int p)
{
	if (p >= 0 && p < n)
	{ // p��Χ�Ϸ�
		for (int child = FirstChild(p); child != -1; child = RightSibling(child))
			PostOrder(child); // ���κ�������ÿ������
		visit(p);			  // ���ʸ����
	}
}

int Tree::Height(int r)
// ���������������rΪ�������ĸ�
{
	int child, h, maxHeight = 0;
	if (r < 0 || r >= n)
		return 0;
	else
	{
		for (child = FirstChild(r); child != -1; child = RightSibling(child))
		{
			h = Height(child); // ��������ĸ�
			maxHeight = (maxHeight < h) ? h : maxHeight;
			// ��������ߵ����ֵ
		}
		return maxHeight + 1; // ����Ϊ�����������ֵ�ټ�1
	}
}

int Tree::FirstChild(int cur) const
// �����������cur�޺���,�򷵻�-1,���򷵻������cur�ĵ�һ������,
{
	if (cur < 0 || cur >= n)
		return -1; // ���cur������,����-1��ʾ�޺���

	if (nodes[cur].firstchild == NULL) // �޺���
		return -1;
	else
		return nodes[cur].firstchild->child; // ȡ����һ������
}

int Tree::RightSibling(int cur) const
// ���������������cur�����ֵ�,�򷵻�-1,���򷵻�cur�����ֵ�
{
	if (cur < 0 || cur >= n)
		return -1; // ���cur������,����-1��ʾ�޺���

	int pt = nodes[cur].parent; // cur��˫��
	TreeNode *p = nodes[pt].firstchild;
	while (p != NULL && p->child != cur)
		p = p->next;
	if (p == NULL || p->next == NULL)
		return -1; // �������ֵ�
	else
		return p->next->child; // ��ʾ�����ֵ�
}

int Tree::GetRoot() const    
{
	return r;
}

int Tree::Leaf()    //������Ҷ���� 
{
	int cnt = 0;
	for (int i = 0; i < n; i++)
	{
		if (nodes[i].firstchild->child == -1)
			cnt++;
	}
	return cnt;
}

int Tree::Binary_Height(int *h)  //����Ӧ�������߶� 
{
	int maxx = 0;
	int j = 1;             
	for (int i = 0; i < n; i++)
	{
		TreeNode *p = nodes[i].firstchild;
		while (p != NULL && p->child != -1)    // ��¼ÿ�����ĸ߶� 
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
 
int Tree::Binary_Leaf()   //�������Ҷ���� 
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

void Tree::Order(int tnum)   //ת��Ϊ������ 
{
	t[tnum] = nodes[root].data;
	bh[root] = tnum;      //��¼���λ�� 
	for (int i = 0; i < n; i++)
	{
		if (nodes[i].firstchild->child != -1)
		{
			tnum = bh[i];
			t[2 * tnum + 1] = nodes[nodes[i].firstchild->child].data;  //���ӽ����������� 
			bh[nodes[i].firstchild->child] = 2 * tnum + 1;
			int nex = 2 * tnum + 1;
			TreeNode *p = nodes[i].firstchild->next;    
			while (p->child != -1 && p != NULL)    //�ֵܽ����������� 
			{
				t[2 * nex + 2] = nodes[p->child].data;
				bh[p->child] = 2 * nex + 2;
				nex = 2 * nex + 2;
				p = p->next;
			}
		}
	}
}

void HG(int index)   //���������� 
{
	if (t[index] == '0')
	{
		return;
	}
	// ��ݹ�
	if ((index * 2 + 1) < maxsize)
	{
		HG(index * 2 + 1);
	}
	// �ҵݹ�
	if ((index * 2 + 2) < maxsize)
	{
		HG(index * 2 + 2);
	}
	// ������
	cout << t[index] << " ";
}

//////////////////////////////////////////////////////////////////////////////////
// ѡ����
int choose()
{
	int i;
	cout << "1:�������Դ���ɭ��\n"
		 << "2:��ɭ�ֹ�ģ\n"
		 << "3:��ɭ�ָ߶�\n"
		 << "4:��ɭ��Ҷ����\n"
		 << "5:����Ӧ�������߶�\n"
		 << "6:����Ӧ������Ҷ����\n"
		 << "7:�ȸ�����\n"
		 << "8:�и�����\n"
		 << "9:�������\n"
		 << "0:�˳�\n"
		 << "ѡ���ܣ�";
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
		// �����������ѭ��ʵ�ִ���ɭ�֣� 
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

			cout << "���������\n\n";
		}
		// ɭ�ֹ�ģ
		else if (i == 2)
		{
			int count = 0;
			while (head_temp != NULL)
			{
				count++;
				head_temp = head_temp->next;
			}
			cout << "ɭ�ֹ�ģΪ " << count << "\n";
		}
		// ɭ�ָ߶�
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
			cout << "ɭ�ָ߶�Ϊ " << height << "\n";
		}
		// ɭ��Ҷ����
		else if (i == 4)
		{
			int leaf = 0;
			while (head_temp != NULL)
			{
				leaf += head_temp->Leaf();
				head_temp = head_temp->next;
			}
			cout << "ɭ��Ҷ����Ϊ��" << leaf << "\n";
		}
		// �������߶�
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
			cout << "��Ӧ�������ĸ߶�Ϊ��" << MaxHeight << "\n";
		}
		// ������Ҷ��
		else if (i == 6)
		{
			while (head_temp != NULL)
			{
				l += head_temp->Binary_Leaf();
				head_temp = head_temp->next;
			}
			cout << "��Ӧ��������Ҷ����Ϊ��" << l << "\n";
		}
		// �ȸ�
		else if (i == 7)
		{
			while (head_temp != NULL)
			{
				head_temp->PreOrder(head_temp->root);
				head_temp = head_temp->next;
			}
		}
		// �и�����
		else if (i == 8)
		{
			while (head_temp != NULL)
			{
				head_temp->PostOrder(head_temp->root);
				head_temp = head_temp->next;
			}
		}
		// ������� 
		else if (i == 9)
		{
			while (head_temp != NULL)
			{
				head_temp->Order(pos);
				pos = 2 * pos + 2;   //ÿ�����ĸ�ת��Ϊ�������Һ����±� 
				head_temp = head_temp->next;
			}
			HG(0);    //�ݹ���� 
		}
		else if (i == 0)
			break;
		cout << "--------------------------------------------------------------\n";
	}

	return 0;
}
