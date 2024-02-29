#ifndef _PARENT_CHILDREN_NODE_H_
#define _PARENT_CHILDREN_NODE_H_

#include "Node.h"
#include <cstddef>

template <class T>
struct ParentChildrenNode
{
    T data;
    int parent;
    Node<int> *children_linklist;
    ParentChildrenNode();
    ParentChildrenNode(T item, int Parent = -1, Node<int> *Children_Linklist = NULL);
};

template <class T>
ParentChildrenNode<T>::ParentChildrenNode()
{
    parent = -1;
    children_linklist = NULL;
}

template <class T>
ParentChildrenNode<T>::ParentChildrenNode(T item, int Parent, Node<int> *Children_Linklist)
{
    data = item;
    parent = Parent;
    children_linklist = Children_Linklist;
}

#endif
