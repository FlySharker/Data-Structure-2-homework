#ifndef __HEAP_SORT_H__
#define __HEAP_SORT_H__

#include "Assistance.h"

template <class ElemType>
void FilterDown_3(vector<ElemType> &elem, int low, int high)
// �������:����lowΪ��������������Ϊһ������
{
	int f = low, i = 3 * low + 1;
	ElemType e = elem[low];
	while (i <= high)
	{ // fΪ���������,iΪf�������
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
		{ // ���ӵ�ֵ������˫�ף���������µ���
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
// �������:������elem���ж�����
{
	int i;
	for (i = (n - 2) / 3; i >= 0; --i) // ��ʼ���ѣ���elem[0 .. n - 1]����������
		FilterDown_3(elem, i, n - 1);
	//cout << "��ʼ�ѣ�";
	//Display(elem, n); // ��ʾ��ʼ��

	for (i = n - 1; i > 0; --i)
	{ // ��i�˶�����
		Swap(elem[0], elem[i]);
		// ���Ѷ�Ԫ�غ͵�ǰδ�������������elem[0 .. i]�����һ��Ԫ�ؽ���
		FilterDown_3(elem, 0, i - 1); // ��elem[0 .. i - 1]���µ���Ϊ����
		//cout << "��" << n - i << "�˶���������";
		//Display(elem, n); // ��ʾ�м���
	}
}

template <class ElemType>
void FilterDown_2(vector<ElemType> &elem, int low, int high)
// �������:����lowΪ��������������Ϊһ������
{
	int f = low, i = 2 * low + 1;
	ElemType e = elem[low];
	while (i <= high)
	{ // fΪ���������,iΪf�������
		if (i < high && elem[i] < elem[i + 1])
		{
			i++;
		}
		if (e < elem[i])
		{ // ���ӵ�ֵ������˫�ף���������µ���
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
// �������:������elem���ж�����
{
	int i;
	for (i = (n - 2) / 2; i >= 0; --i) // ��ʼ���ѣ���elem[0 .. n - 1]����������
		FilterDown_2(elem, i, n - 1);
	//cout << "��ʼ�ѣ�";
	//Display(elem, n); // ��ʾ��ʼ��

	for (i = n - 1; i > 0; --i)
	{ // ��i�˶�����
		Swap(elem[0], elem[i]);
		// ���Ѷ�Ԫ�غ͵�ǰδ�������������elem[0 .. i]�����һ��Ԫ�ؽ���
		FilterDown_2(elem, 0, i - 1); // ��elem[0 .. i - 1]���µ���Ϊ����
		//cout << "��" << n - i << "�˶���������";
		//Display(elem, n); // ��ʾ�м���
	}
}
#endif
