#ifndef _PARENT_CHILDREN_H_
#define _PARENT_CHILDREN_H_

#include "Parent_Children_Node.h"
#include <queue>
#include <iostream>

template <class T>
class ParentChildrenTree
{
protected:
    ParentChildrenNode<T> *nodes;
    int maxsize = 10;
    int root, num;

public:
    ParentChildrenTree(T items[], int parents[], int r, int n);
    void LevelOrder();
    int FirstChild(int cur);
    int RightSibling(int cur);
    void Write(int cur);
    void LevelOrder_binary();
};

template <class T>
ParentChildrenTree<T>::ParentChildrenTree(T items[], int parents[], int r, int n)
{
    nodes = new ParentChildrenNode<T>[maxsize];
    for (int i = 0; i < n; i++)
    {
        nodes[i].data = items[i];
        nodes[i].parent = parents[i];
        if (nodes[i].parent != -1)
        {
            Node<int> *p, *newnode;
            newnode = new Node<int>(i, NULL);
            if (nodes[parents[i]].children_linklist == NULL)
                nodes[parents[i]].children_linklist = newnode;
            else
            {
                p = nodes[parents[i]].children_linklist;
                while (p->next != NULL)
                {
                    p = p->next;
                }
                p->next = newnode;
            }
        }
    }
    root = r;
    num = n;
}

template <class T>
int ParentChildrenTree<T>::FirstChild(int cur)
{
    if (cur < 0 || cur >= num)
        return -1;
    if (nodes[cur].children_linklist == NULL)
        return -1;
    return nodes[cur].children_linklist->data;
}

template <class T>
int ParentChildrenTree<T>::RightSibling(int cur)
{
    if (cur < 0 || cur >= num)
        return -1;
    int pt = nodes[cur].parent;
    Node<int> *p = nodes[pt].children_linklist;
    while (p != NULL && p->data != cur)
        p = p->next;
    if (p == NULL || p->next == NULL)
        return -1;
    else
        return p->next->data;
}

template <class T>
void ParentChildrenTree<T>::LevelOrder()
{
    std::queue<int> q;
    int cur = root;
    if (cur >= 0 || cur < num)
        q.push(cur);
    while (!q.empty())
    {
        cur = q.front();
        Write(cur);
        q.pop();
        for (int child = FirstChild(cur); child != -1; child = RightSibling(child))
        {
            q.push(child);
        }
    }
}

template <class T>
void ParentChildrenTree<T>::Write(int cur)
{
    std::cout << nodes[cur].data << " ";
}

template <class T>
void ParentChildrenTree<T>::LevelOrder_binary()
{
    std::queue<int> q;
    int cur = root;
    if (cur >= 0 || cur < num)
        q.push(cur);
    while (!q.empty())
    {
        cur = q.front();
        Write(cur);
        q.pop();
        if (cur == root)
        {
            q.push(FirstChild(cur));
        }
        else
        {
            int child = FirstChild(cur);
            int sibling = RightSibling(cur);
            if (child != -1)
                q.push(child);
            if (sibling != -1)
                q.push(sibling);
        }
    }
}

#endif
