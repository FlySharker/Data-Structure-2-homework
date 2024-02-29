#pragma once

#include <bits/stdc++.h>
using namespace std;

template <class T>
class MinHeap
{
private:
    T *heapArr;
    int CurrentSize;
    int maxSize;
    void FilterDown(int Start);
    void FilterUp(int End);
    void FilterDown_Max(int Start);

public:
    MinHeap(int MaxSize);
    MinHeap(T a[], int MaxSize, int n);
    ~MinHeap() { delete[] heapArr; }
    void MaxHeap(T a[], int MaxSize, int n);
    void PrintheapArr();
    int Insert(const T &e);
};

template <class T>
MinHeap<T>::MinHeap(int MaxSize)
{
    if (MaxSize <= 0)
        return;
    maxSize = MaxSize;
    heapArr = new T[maxSize];
    CurrentSize = 0;
}

template <class T>
void MinHeap<T>::FilterDown(int Start)
{
    int i = Start, j = 2 * i + 1;
    T temp = heapArr[i];
    while (j <= CurrentSize - 1)
    {
        if (j <= CurrentSize - 1 && heapArr[j] > heapArr[j + 1])
        {
            j++;
        }
        if (temp <= heapArr[j])
        {
            break;
        }
        else
        {
            heapArr[i] = heapArr[j];
            i = j;
            j = 2 * j + 1;
        }
    }
    heapArr[i] = temp;
}

template <class T>
MinHeap<T>::MinHeap(T a[], int MaxSize, int n)
{
    if (n <= 0)
    {
        return;
    }
    maxSize = MaxSize;
    heapArr = new T[maxSize];
    for (int i = 0; i < n; i++)
    {
        heapArr[i] = a[i];
    }
    CurrentSize = n;
    int i = (CurrentSize - 2) / 2;
    while (i >= 0)
    {
        FilterDown(i);
        i--;
    }
}

template <class T>
void MinHeap<T>::FilterDown_Max(int Start)
{
    int i = Start, j = 2 * i + 1;
    T temp = heapArr[i];
    while (j <= CurrentSize - 1)
    {
        if (j <= CurrentSize - 1 && heapArr[j] < heapArr[j + 1])
        {
            j++;
        }
        if (temp >= heapArr[j])
        {
            break;
        }
        else
        {
            heapArr[i] = heapArr[j];
            i = j;
            j = 2 * j + 1;
        }
    }
    heapArr[i] = temp;
}

template <class T>
void MinHeap<T>::MaxHeap(T a[], int MaxSize, int n)
{
    if (n <= 0)
    {
        return;
    }
    maxSize = MaxSize;
    heapArr = new T[maxSize];
    for (int i = 0; i < n; i++)
    {
        heapArr[i] = a[i];
    }
    CurrentSize = n;
    int i = (CurrentSize - 2) / 2;
    while (i >= 0)
    {
        FilterDown_Max(i);
        i--;
    }
}

template <class T>
void MinHeap<T>::PrintheapArr()
{
    for (int i = 0; i < CurrentSize; i++)
    {
        cout << heapArr[i] << " ";
    }
}

template <class T>
void MinHeap<T>::FilterUp(int End)
{
    int j = End, i = (j - 1) / 2;
    T temp = heapArr[j];
    while (j > 0)
    {
        if (heapArr[i] <= temp)
            break;
        else
        {
            heapArr[j] = heapArr[i];
            j = i;
            i = (j - 1) / 2;
        }
        heapArr[j] = temp;
    }
}

template <class T>
int MinHeap<T>::Insert(const T &e)
{
    if (CurrentSize == maxSize)
        return 0;
    heapArr[CurrentSize] = e;
    FilterUp(CurrentSize);
    CurrentSize++;
    return 1;
}