#ifndef __ADJ_MATRIX_UNDIR_GRAPH_H__
#define __ADJ_MATRIX_UNDIR_GRAPH_H__

#include"LinkStack.h"

// ����ͼ���ڽӾ�����
template <class ElemType, class WeightType>
class AdjMatrixUndirGraph
{
protected:
	// �ڽӾ�������ݳ�Ա:
	int vexNum, vexMaxNum, arcNum; // ������Ŀ������Ķ��������Ŀ�ͱ���
	WeightType **arcs;			   // ��ű���Ϣ�ڽӾ���
	ElemType *vertexes;			   // ��Ŷ�����Ϣ������
	mutable Status *tag;		   // ��־����
	WeightType infinity;

public:
	// �ڽӾ������͵ķ�������:
	AdjMatrixUndirGraph(ElemType es[], int vertexNum, int vertexMaxNum = DEFAULT_SIZE, WeightType infit = DEFAULT_INFINITY);
	// ������es[]Ϊ����,�������ΪvertexNum,����Ķ��������ĿΪvertexMaxNum,����Ϊ0������ͼ
	AdjMatrixUndirGraph(int vertexMaxNum = DEFAULT_SIZE);
	// ��������Ķ��������ĿΪvertexMaxNum,����Ϊ0������ͼ
	~AdjMatrixUndirGraph();													 // ��������
	void Clear();															 // ���ͼ
	bool IsEmpty();															 // �ж�����ͼ�Ƿ�Ϊ��
	int GetOrder(ElemType &d) const;										 // �󶥵�����
	Status GetElem(int v, ElemType &d) const;								 // �󶥵��Ԫ��ֵ
	Status SetElem(int v, const ElemType &d);								 // ���ö����Ԫ��ֵ
	WeightType GetInfinity() const;											 // ȡ������ֵ
	int GetVexNum() const;													 // ���ض������
	int GetArcNum() const;													 // ���ر���
	WeightType GetWeight(int v1, int v2) const;
	int FirstAdjVex(int v) const;											 // ���ض���v�ĵ�һ���ڽӵ�
	int NextAdjVex(int v1, int v2) const;									 // ���ض���v1�������v2����һ���ڽӵ�
	void InsertVex(const ElemType &d);										 // ����Ԫ��ֵΪd�Ķ���
	void InsertArc(ElemType v1, ElemType v2, WeightType w);					 // ���붥��Ϊv1��v2�ı�
	void DeleteVex(const ElemType &d);										 // ɾ��Ԫ��ֵΪd�Ķ���
	void DeleteArc(int v1, int v2);											 // ɾ������Ϊv1��v2�ı�
	Status GetTag(int v) const;												 // ���ض���v�ı�־
	void SetTag(int v, Status val) const;									 // ���ö���v�ı�־Ϊval
	AdjMatrixUndirGraph(const AdjMatrixUndirGraph<ElemType, WeightType> &g); // ���ƹ��캯��
	AdjMatrixUndirGraph<ElemType, WeightType> &operator=(const AdjMatrixUndirGraph<ElemType, WeightType> &g);
	// ��ֵ�������
	void Display(); // ��ʾ�ڽӾ�������ͼ
	void CountDegree(ElemType v, int &d);
};

// ����ͼ���ڽӾ������ʵ�ֲ���
template <class ElemType, class WeightType>
AdjMatrixUndirGraph<ElemType, WeightType>::AdjMatrixUndirGraph(ElemType es[], int vertexNum, int vertexMaxNum, WeightType infit)
// �����������������Ԫ��Ϊes[],�������ΪvertexNum,����Ķ��������ĿΪvertexMaxNum,����Ϊ0������ͼ

{
	if (vertexMaxNum < 0)
		throw Error("����Ķ��������Ŀ����Ϊ��!"); // �׳��쳣

	if (vertexMaxNum < vertexNum)
		throw Error("������Ŀ���ܴ�������Ķ��������Ŀ!"); // �׳��쳣

	vexNum = vertexNum;
	vexMaxNum = vertexMaxNum;
	arcNum = 0;
	infinity = infit;
	vertexes = new ElemType[vexMaxNum];				   // �������ɶ�����Ϣ����
	tag = new Status[vexMaxNum];					   // ���ɱ�־����
	arcs = (WeightType **)new WeightType *[vexMaxNum]; // �����ڽӾ���
	for (int v = 0; v < vexMaxNum; v++)
		arcs[v] = new WeightType[vexMaxNum];

	for (int v = 0; v < vexNum; v++)
	{
		vertexes[v] = es[v];
		tag[v] = UNVISITED;
		for (int u = 0; u < vexNum; u++)
			arcs[v][u] = infinity;
	}
}

template <class ElemType, class WeightType>
AdjMatrixUndirGraph<ElemType, WeightType>::AdjMatrixUndirGraph(int vertexMaxNum)
// �������������������������ĿΪvertexMaxNum�Ŀ�����ͼ
{
	if (vertexMaxNum < 0)
		throw Error("����Ķ��������Ŀ����Ϊ��!"); // �׳��쳣

	vexNum = 0;
	vexMaxNum = vertexMaxNum;
	arcNum = 0;

	vertexes = new ElemType[vexMaxNum];				   // �������ɶ�����Ϣ����
	tag = new Status[vexMaxNum];					   // ���ɱ�־����
	arcs = (WeightType **)new WeightType *[vexMaxNum]; // �����ڽӾ���
	for (int v = 0; v < vexMaxNum; v++)
		arcs[v] = new WeightType[vexMaxNum];
}

template <class ElemType, class WeightType>
void AdjMatrixUndirGraph<ElemType, WeightType>::Clear()
// ���������������ͼ�Ķ������ͱ�������Ϊ0.
{
	vexNum = 0;
	arcNum = 0;
}

template <class ElemType, class WeightType>
bool AdjMatrixUndirGraph<ElemType, WeightType>::IsEmpty()
// ����������������ͼΪ�շ���true,���򷵻�false.
{
	return vexNum == 0;
}

template <class ElemType, class WeightType>
AdjMatrixUndirGraph<ElemType, WeightType>::~AdjMatrixUndirGraph()
// ����������ͷŶ�����ռ�õĿռ�
{
	delete[] vertexes; // �ͷŶ�������
	delete[] tag;	   // �ͷű�־

	for (int v = 0; v < vexMaxNum; v++) // �ͷ��ڽӾ������
		delete[] arcs[v];
	delete[] arcs; // �ͷ��ڽӾ���
}

template <class ElemType, class WeightType>
int AdjMatrixUndirGraph<ElemType, WeightType>::GetOrder(ElemType &d) const
// ����������󶥵�d�����.�������Ŵ�0��ʼ��ͼ�в����ڶ���dʱ������-1.
{
	for (int v = 0; v < vexNum; v++)
		if (vertexes[v] == d)
			return v; // ����d����,�����������
	return -1;		  // ����d������,����-1
}

template <class ElemType, class WeightType>
Status AdjMatrixUndirGraph<ElemType, WeightType>::GetElem(int v, ElemType &d) const
// ��������������Ϊv�Ķ���ֵ, v��ȡֵ��ΧΪ0 �� v �� vexNum, v�Ϸ�ʱ����
// ͨ��dȡ�ö���ֵ��������ENTRY_FOUND������������NOT_PRESENT
{
	if (v < 0 || v >= vexNum)
		return NOT_PRESENT; // v��Χ��,����Ԫ�ز�����
	else
	{
		d = vertexes[v];	// ������v��Ԫ��ֵ����d
		return ENTRY_FOUND; // ����Ԫ�ش���
	}
}

template <class ElemType, class WeightType>
Status AdjMatrixUndirGraph<ElemType, WeightType>::SetElem(int v, const ElemType &d)
// ������������ö����Ԫ��ֵv��ȡֵ��ΧΪ0 �� v �� vexNum, v�Ϸ�ʱ��������
//	SUCCESS, ����������RANGE_ERROR
{
	if (v < 0 || v >= vexNum)
		return RANGE_ERROR; // v��Χ��,����λ�ô�
	else
	{
		vertexes[v] = d; // ������Ԫ�ص�ֵ��Ϊd
		return SUCCESS;	 // �����޸ĳɹ�
	}
}

template <class ElemType, class WeightType>
int AdjMatrixUndirGraph<ElemType, WeightType>::GetVexNum() const
// ������������ض������
{
	return vexNum;
}

template <class ElemType, class WeightType>
int AdjMatrixUndirGraph<ElemType, WeightType>::GetArcNum() const
// ������������ر���
{
	return arcNum;
}

template <class ElemType, class WeightType>
WeightType AdjMatrixUndirGraph<ElemType, WeightType>::GetWeight(int v1, int v2) const
{
	return arcs[v1][v2];
}

template <class ElemType, class WeightType>
int AdjMatrixUndirGraph<ElemType, WeightType>::FirstAdjVex(int v) const
// ������������ض���v�ĵ�1���ڽӵ�����
{
	if (v < 0 || v >= vexNum)
		throw Error("v���Ϸ�!"); // �׳��쳣

	for (int u = 0; u < vexNum; u++)
		if (arcs[v][u] != 0)
			return u;

	return -1; // ����-1��ʾ���ڽӵ�
}

template <class ElemType, class WeightType>
int AdjMatrixUndirGraph<ElemType, WeightType>::NextAdjVex(int v1, int v2) const
// ������������ض���v1�������v2����һ���ڽӵ�
{
	if (v1 < 0 || v1 >= vexNum)
		throw Error("v1���Ϸ�!"); // �׳��쳣
	if (v2 < 0 || v2 >= vexNum)
		throw Error("v2���Ϸ�!"); // �׳��쳣
	if (v1 == v2)
		throw Error("v1���ܵ���v2!"); // �׳��쳣

	for (int u = v2 + 1; u < vexNum; u++)
		if (arcs[v1][u] != 0)
			return u;

	return -1; // ����-1��ʾ����һ���ڽӵ�
}

template <class ElemType, class WeightType>
void AdjMatrixUndirGraph<ElemType, WeightType>::InsertVex(const ElemType &d)
// ������������붥��d
{
	if (vexNum == vexMaxNum)
		throw Error("ͼ�Ķ��������ܳ�������������!"); // �׳��쳣

	vertexes[vexNum] = d;
	tag[vexNum] = UNVISITED;
	for (int v = 0; v <= vexNum; v++)
	{
		arcs[vexNum][v] = 0;
		arcs[v][vexNum] = 0;
	}
	vexNum++;
}

template <class ElemType, class WeightType>
void AdjMatrixUndirGraph<ElemType, WeightType>::InsertArc(ElemType v1, ElemType v2, WeightType w)
// ���������������������v1��v2�ı�
{
	int vv1 = v1 - 65,vv2=v2-65;
	if (vv1 < 0 || vv1 >= vexNum)
		throw Error("v1���Ϸ�!"); // �׳��쳣
	if (vv2 < 0 || vv2 >= vexNum)
		throw Error("v2���Ϸ�!"); // �׳��쳣
	if (vv1 == vv2)
		throw Error("v1���ܵ���v2!"); // �׳��쳣

	if (arcs[vv1][vv2] == infinity)
	{ // ԭ����ͼ��û�б�(v1, v2)
		arcNum++;
		arcs[vv1][vv2] = w;
		arcs[vv2][vv1] = w;
	}
}

template <class ElemType, class WeightType>
void AdjMatrixUndirGraph<ElemType, WeightType>::DeleteVex(const ElemType &d)
// ���������ɾ��Ԫ��Ϊd�Ķ���
{
	int v;
	for (v = 0; v < vexNum; v++)
		if (vertexes[v] == d)
			break;
	if (v == vexNum)
		throw Error("ͼ�в�����Ҫɾ���Ķ���!"); // �׳��쳣

	for (int u = 0; u < vexNum; u++) // ɾ���붥��d������ı�
		if (arcs[v][u] == 1)
		{
			arcNum--;
			arcs[v][u] = 0;
			arcs[u][v] = 0;
		}

	vexNum--;
	if (v < vexNum)
	{
		vertexes[v] = vertexes[vexNum];
		tag[v] = tag[vexNum];
		for (int u = 0; u <= vexNum; u++)
			arcs[v][u] = arcs[vexNum][u];
		for (int u = 0; u <= vexNum; u++)
			arcs[u][v] = arcs[u][vexNum];
	}
}

template <class ElemType, class WeightType>
void AdjMatrixUndirGraph<ElemType, WeightType>::DeleteArc(int v1, int v2)
// ���������ɾ����������v1��v2�ı�
{
	if (v1 < 0 || v1 >= vexNum)
		throw Error("v1���Ϸ�!"); // �׳��쳣
	if (v2 < 0 || v2 >= vexNum)
		throw Error("v2���Ϸ�!"); // �׳��쳣
	if (v1 == v2)
		throw Error("v1���ܵ���v2!"); // �׳��쳣

	if (arcs[v1][v2] != 0)
	{ // ԭ����ͼ���ڱ�(v1, v2)
		arcNum--;
		arcs[v1][v2] = 0;
		arcs[v2][v1] = 0;
	}
}

template <class ElemType, class WeightType>
Status AdjMatrixUndirGraph<ElemType, WeightType>::GetTag(int v) const
// ������������ض���v�ı�־
{
	if (v < 0 || v >= vexNum)
		throw Error("v���Ϸ�!"); // �׳��쳣

	return tag[v];
}

template <class ElemType, class WeightType>
void AdjMatrixUndirGraph<ElemType, WeightType>::SetTag(int v, Status val) const
// ������������ö���v�ı�־Ϊval
{
	if (v < 0 || v >= vexNum)
		throw Error("v���Ϸ�!"); // �׳��쳣

	tag[v] = val;
}

template <class ElemType, class WeightType>
AdjMatrixUndirGraph<ElemType, WeightType>::AdjMatrixUndirGraph(const AdjMatrixUndirGraph<ElemType, WeightType> &g)
// ���������������ͼ���ڽӾ���g����������ͼ���ڽӾ���g�������ƹ��캯��
{
	vexNum = g.vexNum;
	vexMaxNum = g.vexMaxNum;
	arcNum = g.arcNum;

	vertexes = new ElemType[vexMaxNum];				   // ���ɶ�����������
	tag = new Status[vexMaxNum];					   // ���ɱ�־����
	arcs = (WeightType **)new WeightType *[vexMaxNum]; // �����ڽӾ���
	for (int v = 0; v < vexMaxNum; v++)
		arcs[v] = new WeightType[vexMaxNum];

	for (int v = 0; v < vexNum; v++)
	{ // ���ƶ�����������
		vertexes[v] = g.vertexes[v];
		tag[v] = g.tag[v];
		for (int u = 0; u < vexNum; u++)
			arcs[v][u] = g.arcs[v][u];
	}
}

template <class ElemType, class WeightType>
AdjMatrixUndirGraph<ElemType, WeightType> &AdjMatrixUndirGraph<ElemType, WeightType>::operator=(const AdjMatrixUndirGraph<ElemType, WeightType> &g)
// ���������������ͼ���ڽӾ���g��ֵ����ǰ����ͼ���ڽӾ��󡪡���ֵ�������
{
	if (&g != this)
	{
		delete[] vertexes; // �ͷŶ�������
		delete[] tag;	   // �ͷű�־

		for (int v = 0; v < vexMaxNum; v++) // �ͷ��ڽӾ������
			delete[] arcs[v];
		delete[] arcs; // �ͷ��ڽӾ���
		vexNum = g.vexNum;
		vexMaxNum = g.vexMaxNum;
		arcNum = g.arcNum;

		vertexes = new ElemType[vexMaxNum];	 // ���ɶ�����������
		tag = new Status[vexMaxNum];		 // ���ɱ�־����
		arcs = (int **)new int *[vexMaxNum]; // �����ڽӾ���
		for (int v = 0; v < vexMaxNum; v++)
			arcs[v] = new int[vexMaxNum];

		for (int v = 0; v < vexNum; v++)
		{ // ���ƶ�����������
			vertexes[v] = g.vertexes[v];
			tag[v] = g.tag[v];
			for (int u = 0; u < vexNum; u++)
				arcs[v][u] = g.arcs[v][u];
		}
	}
	return *this;
}

template <class ElemType, class WeightType>
void AdjMatrixUndirGraph<ElemType, WeightType>::Display()
// �������: ��ʾ�ڽӾ�������ͼ
{

	for (int v = 0; v < vexNum; v++)
		cout << "\t" << vertexes[v];
	cout << endl;

	for (int v = 0; v < vexNum; v++)
	{
		cout << vertexes[v];
		for (int u = 0; u < vexNum; u++)
			cout << "\t" << arcs[v][u];
		cout << endl;
	}
}

template <class ElemType, class WeightType>
void AdjMatrixUndirGraph<ElemType, WeightType>::CountDegree(ElemType v, int &d)
{
	int vv = GetOrder(v);
	for (int i = 0; i < vexNum; i++)
	{
		if (arcs[vv][i] != 0)
			d++;
	}
}

template <class ElemType, class WeightType>
void DFSTraverse(const AdjMatrixUndirGraph<ElemType, WeightType> &g, void (*Visit)(const ElemType &), int &d)
// ��ʼ����������ͼg
// ���������������ͼg����������ȱ���
{
	int v;
	for (v = 0; v < g.GetVexNum(); v++)
		g.SetTag(v, UNVISITED); // ��ÿ����������δ���ʱ�־

	for (v = 0; v < g.GetVexNum(); v++)

		if (g.GetTag(v) == UNVISITED)
		{
			d++;
			DFS(g, v, Visit); // ����δ���ʵĶ���v��ʼ���������������
		}
}

template <class ElemType, class WeightType>
void DFS(const AdjMatrixUndirGraph<ElemType, WeightType> &g, int v, void (*Visit)(const ElemType &))
// ��ʼ����������ͼg
// ����������Ӷ���v�������������������
{
	ElemType e;
	g.SetTag(v, VISITED); // ���ö���v�ѷ��ʱ�־
	g.GetElem(v, e);	  // ȡ����v������Ԫ��ֵ
	// Visit(e);			  // ���ʶ���v
	for (int w = g.FirstAdjVex(v); w != -1; w = g.NextAdjVex(v, w))
		if (g.GetTag(w) == UNVISITED)
			DFS(g, w, Visit); // ��v����δ���ʹ����ڽӶ���w��ʼ���������������
}

template <class ElemType, class WeightType>
void ShortestPathFloyd(const AdjMatrixUndirGraph<ElemType, WeightType> &g, int **path,
					   WeightType **dist)
// �������: ��Floyd�㷨��������g�и��Զ���u��v֮������·��path[u][v]��·������
//	dist[u][v],path[u][v]�洢��u��v�����·�������˶����ǰһ����Ķ����,dist[u][v]
//	�洢��u��v�����·���ĳ���
{
	for (int u = 0; u < g.GetVexNum(); u++)
		for (int v = 0; v < g.GetVexNum(); v++)
		{ // ��ʼ��path��dist
			dist[u][v] = (u != v) ? g.GetWeight(u, v) : 0;
			if (u != v && dist[u][v] < g.GetInfinity())
				path[u][v] = u; // ���ڱ�<u,v>
			else
				path[u][v] = -1; // �����ڱ�<u,v>
			
		}

	for (int k = 0; k < g.GetVexNum(); k++)
		for (int i = 0; i < g.GetVexNum(); i++)
			for (int j = 0; j < g.GetVexNum(); j++)
				if (dist[i][k] + dist[k][j] < dist[i][j])
				{
					// ��i��k�ٵ�j��·�����ȸ���
					dist[i][j] = dist[i][k] + dist[k][j];
					path[i][j] = path[k][j];
				}
				
}

template <class ElemType, class WeightType>
WeightType AdjMatrixUndirGraph<ElemType, WeightType>::GetInfinity() const
// �������������������ֵ
{
	return infinity;
}

template <class ElemType, class WeightType>
void DisplayPathAndDist(const AdjMatrixUndirGraph<ElemType, WeightType> &g, int **path, WeightType **dist,ElemType e1,ElemType e2)
{
	int v1 = e1 - 65, v2 = e2 - 65;
	cout << endl;
	if (dist[v1][v2] < g.GetInfinity())
	{ // ���ڴ�v1��v2���·��
	cout << "�� " << e1 << " �� " << e2 << ":";
	cout << " ·������ = " << dist[v1][v2];
	cout << " ·����";
	LinkStack<int> s; // �洢·�ϵĶ���
		int v = v2;
		while (v != v1)
		{
			s.Push(v);		 // vΪ·���ϵĶ���
			v = path[v1][v]; // ȡ��·���ϵ�ǰһ������
		}
		s.Push(v1); // v��·������ʼ��
		while (!s.IsEmpty())
		{ // ���·�ϵĶ���
			s.Pop(v);
			g.GetElem(v, e1);
			cout << e1 << " ";
		}
	}
	else
	{ // ��v1��v2��·��
		cout << "from " << e1 << " to " << e2 << ":";
		cout << " dist = ��";
	}
	cout << endl;
}

#endif
