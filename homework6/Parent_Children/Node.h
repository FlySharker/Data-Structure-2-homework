#ifndef _NODE_H_
#define _NODE_H_

#include<cstddef>

template <class T>
struct Node
{
    T data;
    Node<T> *next;
    Node();
    Node(T item, Node<T> *link = NULL); /* data */
};

template <class T>
Node<T>::Node()
{
    next = NULL;
}

template <class T>
Node<T>::Node(T item, Node<T> *link)
{
    data = item;
    next = link;
}

#endif