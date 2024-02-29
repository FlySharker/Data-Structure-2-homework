#ifndef __HEAP_SORT_H__
#define __HEAP_SORT_H__

#include "Assistance.h"

template <class ElemType>
void FilterDown_3(vector<ElemType> &elem, int low, int high)
// 操作结果:将以low为根的子树调整成为一个最大堆
{
	int f = low, i = 3 * low + 1;
	ElemType e = elem[low];
	while (i <= high)
	{ // f为被调整结点,i为f的最大孩子
		if (i < high)
			if (i + 1 == high)
			{
				if (elem[i + 1] > elem[i])
				{
					i++;
				}
			}
			else
			{
				if (elem[i + 1] > elem[i + 2] && elem[i + 1] > elem[i])
				{
					i++;
				}
				else if (elem[i + 2] > elem[i] && elem[i + 2] > elem[i + 1])
				{
					i += 2;
				}
			}

		if (e < elem[i])
		{ // 孩子的值大于其双亲，则进行向下调整
			elem[f] = elem[i];
			f = i;
			i = 3 * f + 1;
		}
		else
			break;
	}
	elem[f] = e;
}

template <class ElemType>
void FilterUp_3(vector<ElemType> &elem,int end)
{
	int j = end, i;
	ElemType temp = elem[j];
	i = (j - 1) / 3;
	while(j>0)
	{
		if(elem[i]>=temp)
		{
			break;
		}
		else
		{
			elem[j] = elem[i];
			j = i;
			i = (j - 1) / 3;
		}
		elem[j] = temp;
	}
}

template <class ElemType>
void HeapSort_3(vector<ElemType> &elem, int n)
// 操作结果:对数组elem进行堆排序
{
	int i;
	for (i = (n - 2) / 3; i >= 0; --i) // 初始建堆，将elem[0 .. n - 1]调整成最大堆
		FilterDown_3(elem, i, n - 1);
	//cout << "初始堆：";
	//Display(elem, n); // 显示初始堆

	for (i = n - 1; i > 0; --i)
	{ // 第i趟堆排序
		Swap(elem[0], elem[i]);
		// 将堆顶元素和当前未经排序的子序列elem[0 .. i]中最后一个元素交换
		FilterDown_3(elem, 0, i - 1); // 将elem[0 .. i - 1]重新调整为最大堆
		//cout << "第" << n - i << "趟堆排序结果：";
		//Display(elem, n); // 显示中间结果
	}
}

template <class ElemType>
void FilterDown_2(vector<ElemType> &elem, int low, int high)
// 操作结果:将以low为根的子树调整成为一个最大堆
{
	int f = low, i = 2 * low + 1;
	ElemType e = elem[low];
	while (i <= high)
	{ // f为被调整结点,i为f的最大孩子
		if (i < high && elem[i] < elem[i + 1])
		{
			i++;
		}
		if (e < elem[i])
		{ // 孩子的值大于其双亲，则进行向下调整
			elem[f] = elem[i];
			f = i;
			i = 2 * f + 1;
		}
		else
			break;
	}
	elem[f] = e;
}

template <class ElemType>
void HeapSort_2(vector<ElemType> &elem, int n)
// 操作结果:对数组elem进行堆排序
{
	int i;
	for (i = (n - 2) / 2; i >= 0; --i) // 初始建堆，将elem[0 .. n - 1]调整成最大堆
		FilterDown_2(elem, i, n - 1);
	//cout << "初始堆：";
	//Display(elem, n); // 显示初始堆

	for (i = n - 1; i > 0; --i)
	{ // 第i趟堆排序
		Swap(elem[0], elem[i]);
		// 将堆顶元素和当前未经排序的子序列elem[0 .. i]中最后一个元素交换
		FilterDown_2(elem, 0, i - 1); // 将elem[0 .. i - 1]重新调整为最大堆
		//cout << "第" << n - i << "趟堆排序结果：";
		//Display(elem, n); // 显示中间结果
	}
}
#endif
