#pragma once
#include <bits/stdc++.h>
using namespace std;

template <class T>
struct BTNode
{
	T data;
	BTNode<T> *lc;
	BTNode<T> *rc;
	BTNode();
	BTNode(const T &d, BTNode<T> *LeftChild = NULL, BTNode<T> *RightChild = NULL);
};

template <class T>
BTNode<T>::BTNode()
{
	lc = rc = NULL;
}

template <class T>
BTNode<T>::BTNode(const T &d, BTNode<T> *LeftChild, BTNode<T> *RightChild)
{
	data = d;
	lc = LeftChild;
	rc = RightChild;
}
