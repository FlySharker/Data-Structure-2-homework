#pragma once

#include "BTNode.h"
#include <stack>
using namespace std;

template <class T>
class BT
{
protected:
	BTNode<T> *root;

public:
	BT();
	BT(const T &e);
	virtual ~BT();
	BTNode<T> *GetRoot() const;
	bool IsEmpty() const;
	void InsertRightChild(BTNode<T> *p, const T &e);
	void InsertLeftChild(BTNode<T> *p, const T &e);
	void PreOrder(BTNode<T> *r) const;
	void InOrder(BTNode<T> *r) const;
	void PostOrder(BTNode<T> *r) const;
	void CreateBT(BTNode<T> *&p);
	void PrintTree(BTNode<T> *p, int i);
	void CountLeaf(BTNode<T> *p, int &e);
	void Revolut(BTNode<T> *p);
	void CountBreadth(BTNode<T> *p, int &depth, int width[], int &e);
	void NonRecurringInOrder(BTNode<T> *root);
};

template <class T>
BT<T>::BT()
{
}

template <class T>
BT<T>::BT(const T &e)
{
}

template <class T>
BT<T>::~BT()
{
	delete root;
}

template <class T>
BTNode<T> *BT<T>::GetRoot() const
{
	return root;
}

template <class T>
void BT<T>::InsertRightChild(BTNode<T> *p, const T &e)
{
	if (p == NULL)
		return;
	else
	{
		BTNode<T> *Child = new BTNode<T>(e);
		if (p->rc != NULL)
			Child->rc = p->rc;
		p->rc = Child;
	}
}

template <class T>
void BT<T>::InsertLeftChild(BTNode<T> *p, const T &e)
{
	if (p == NULL)
		return;
	else
	{
		BTNode<T> *Child = new BTNode<T>(e);
		if (p->lc != NULL)
			Child->lc = p->lc;
		p->lc = Child;
	}
}

template <class T>
void BT<T>::PreOrder(BTNode<T> *r) const
{
	if (r != NULL)
	{
		cout << r->data << " ";
		PreOrder(r->lc);
		PreOrder(r->rc);
	}
}

template <class T>
void BT<T>::InOrder(BTNode<T> *r) const
{
	if (r != NULL)
	{
		InOrder(r->lc);
		cout << r->data << " ";
		InOrder(r->rc);
	}
}

template <class T>
void BT<T>::PostOrder(BTNode<T> *r) const
{
	if (r != NULL)
	{
		PostOrder(r->lc);
		PostOrder(r->rc);
		cout << r->data << " ";
	}
}

template <class T>
void BT<T>::CreateBT(BTNode<T> *&p)
{
	char ch;
	cin >> ch;
	if (ch == '#')
		p = NULL;
	else
	{
		p = new BTNode<T>;
		p->data = ch;
		CreateBT(p->lc);
		CreateBT(p->rc);
	}
}

template <class T>
void BT<T>::PrintTree(BTNode<T> *p, int i)
{
	if (p != NULL)
	{
		PrintTree(p->rc, i + 1);
		for (int j = 0; j < i - 1; j++)
			cout << " ";
		cout << p->data << endl;
		PrintTree(p->lc, i + 1);
	}
}

template <class T>
void BT<T>::CountLeaf(BTNode<T> *p, int &e)
{
	if (p != NULL)
	{
		if (p->lc == NULL && p->rc == NULL)
			e++;
		CountLeaf(p->lc, e);
		CountLeaf(p->rc, e);
	}
}

template <class T>
void BT<T>::Revolut(BTNode<T> *p)
{
	if (p != NULL)
	{
		BTNode<T> *temp = p->lc;
		p->lc = p->rc;
		p->rc = temp;
		Revolut(p->lc);
		Revolut(p->rc);
	}
}

template <class T>
void BT<T>::CountBreadth(BTNode<T> *p, int &depth, int *width, int &e)
{
	depth++; // 每当进入一次时，深度加一
	if (p == NULL)
	{
		depth--;
		return;
	} // 如果节点为空，return并且深度减一
	else
	{
		width[depth]++; // 如果此节点有数据，该深度的节点个数加一
		sort(width, width + depth);
		e = width[depth];
		CountBreadth(p->lc, depth, width, e);
		CountBreadth(p->rc, depth, width, e);
		depth--; // 当左右节点都遍历完成后，会退回双亲结点，所以深度减一
	}
	return;
}

// 中序遍历
template <class T>
void BT<T>::NonRecurringInOrder(BTNode<T> *root)
{
	// 空树
	if (root == NULL)
		return;
	// 树非空
	BTNode<T> *p = root;
	stack<BTNode<T> *> s;
	while (!s.empty() || p)
	{
		// 一直遍历到左子树最下边，边遍历边保存根节点到栈中
		while (p)
		{
			s.push(p);
			p = p->lc;
		}
		// 当p为空时，说明已经到达左子树最下边，这时需要出栈了

		p = s.top();
		s.pop();
		cout << setw(4) << p->data;
		// 进入右子树，开始新的一轮左子树遍历(这是递归的自我实现)
		p = p->rc;
	}
}
