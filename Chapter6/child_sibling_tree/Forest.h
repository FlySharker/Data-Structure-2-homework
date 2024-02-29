#ifndef _FOREST_H_
#define _FOREST_H_

#include"ChildSiblingTree.h"

template<class T>
class Forest
{
protected:
    ChildSiblingTree<T> *Trees;
public:
    Forest();
    ~Forest();
};

template<class T>
Forest<T>::Forest()
{
    Trees = NULL;
}

template<class T>
Forest<T>::~Forest()
{
    delete[] Trees;
}

#endif