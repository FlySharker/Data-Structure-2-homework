#ifndef __ADJ_MATRIX_UNDIR_GRAPH_H__
#define __ADJ_MATRIX_UNDIR_GRAPH_H__

#include"LinkStack.h"

// 无向图的邻接矩阵类
template <class ElemType, class WeightType>
class AdjMatrixUndirGraph
{
protected:
	// 邻接矩阵的数据成员:
	int vexNum, vexMaxNum, arcNum; // 顶点数目、允许的顶点最大数目和边数
	WeightType **arcs;			   // 存放边信息邻接矩阵
	ElemType *vertexes;			   // 存放顶点信息的数组
	mutable Status *tag;		   // 标志数组
	WeightType infinity;

public:
	// 邻接矩阵类型的方法声明:
	AdjMatrixUndirGraph(ElemType es[], int vertexNum, int vertexMaxNum = DEFAULT_SIZE, WeightType infit = DEFAULT_INFINITY);
	// 以数组es[]为顶点,顶点个数为vertexNum,允许的顶点最大数目为vertexMaxNum,边数为0的无向图
	AdjMatrixUndirGraph(int vertexMaxNum = DEFAULT_SIZE);
	// 构造允许的顶点最大数目为vertexMaxNum,边数为0的无向图
	~AdjMatrixUndirGraph();													 // 析构函数
	void Clear();															 // 清空图
	bool IsEmpty();															 // 判断无向图是否为空
	int GetOrder(ElemType &d) const;										 // 求顶点的序号
	Status GetElem(int v, ElemType &d) const;								 // 求顶点的元素值
	Status SetElem(int v, const ElemType &d);								 // 设置顶点的元素值
	WeightType GetInfinity() const;											 // 取无穷大的值
	int GetVexNum() const;													 // 返回顶点个数
	int GetArcNum() const;													 // 返回边数
	WeightType GetWeight(int v1, int v2) const;
	int FirstAdjVex(int v) const;											 // 返回顶点v的第一个邻接点
	int NextAdjVex(int v1, int v2) const;									 // 返回顶点v1的相对于v2的下一个邻接点
	void InsertVex(const ElemType &d);										 // 插入元素值为d的顶点
	void InsertArc(ElemType v1, ElemType v2, WeightType w);					 // 插入顶点为v1和v2的边
	void DeleteVex(const ElemType &d);										 // 删除元素值为d的顶点
	void DeleteArc(int v1, int v2);											 // 删除顶点为v1和v2的边
	Status GetTag(int v) const;												 // 返回顶点v的标志
	void SetTag(int v, Status val) const;									 // 设置顶点v的标志为val
	AdjMatrixUndirGraph(const AdjMatrixUndirGraph<ElemType, WeightType> &g); // 复制构造函数
	AdjMatrixUndirGraph<ElemType, WeightType> &operator=(const AdjMatrixUndirGraph<ElemType, WeightType> &g);
	// 赋值语句重载
	void Display(); // 显示邻接矩阵无向图
	void CountDegree(ElemType v, int &d);
};

// 无向图的邻接矩阵类的实现部分
template <class ElemType, class WeightType>
AdjMatrixUndirGraph<ElemType, WeightType>::AdjMatrixUndirGraph(ElemType es[], int vertexNum, int vertexMaxNum, WeightType infit)
// 操作结果：构造数据元素为es[],顶点个数为vertexNum,允许的顶点最大数目为vertexMaxNum,边数为0的无向图

{
	if (vertexMaxNum < 0)
		throw Error("允许的顶点最大数目不能为负!"); // 抛出异常

	if (vertexMaxNum < vertexNum)
		throw Error("顶点数目不能大于允许的顶点最大数目!"); // 抛出异常

	vexNum = vertexNum;
	vexMaxNum = vertexMaxNum;
	arcNum = 0;
	infinity = infit;
	vertexes = new ElemType[vexMaxNum];				   // 生成生成顶点信息数组
	tag = new Status[vexMaxNum];					   // 生成标志数组
	arcs = (WeightType **)new WeightType *[vexMaxNum]; // 生成邻接矩阵
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
// 操作结果：构造允许顶点的最大数目为vertexMaxNum的空无向图
{
	if (vertexMaxNum < 0)
		throw Error("允许的顶点最大数目不能为负!"); // 抛出异常

	vexNum = 0;
	vexMaxNum = vertexMaxNum;
	arcNum = 0;

	vertexes = new ElemType[vexMaxNum];				   // 生成生成顶点信息数组
	tag = new Status[vexMaxNum];					   // 生成标志数组
	arcs = (WeightType **)new WeightType *[vexMaxNum]; // 生成邻接矩阵
	for (int v = 0; v < vexMaxNum; v++)
		arcs[v] = new WeightType[vexMaxNum];
}

template <class ElemType, class WeightType>
void AdjMatrixUndirGraph<ElemType, WeightType>::Clear()
// 操作结果：把无向图的顶点数和边数设置为0.
{
	vexNum = 0;
	arcNum = 0;
}

template <class ElemType, class WeightType>
bool AdjMatrixUndirGraph<ElemType, WeightType>::IsEmpty()
// 操作结果：如果无向图为空返回true,否则返回false.
{
	return vexNum == 0;
}

template <class ElemType, class WeightType>
AdjMatrixUndirGraph<ElemType, WeightType>::~AdjMatrixUndirGraph()
// 操作结果：释放对象所占用的空间
{
	delete[] vertexes; // 释放顶点数据
	delete[] tag;	   // 释放标志

	for (int v = 0; v < vexMaxNum; v++) // 释放邻接矩阵的行
		delete[] arcs[v];
	delete[] arcs; // 释放邻接矩阵
}

template <class ElemType, class WeightType>
int AdjMatrixUndirGraph<ElemType, WeightType>::GetOrder(ElemType &d) const
// 操作结果：求顶点d的序号.顶点的序号从0开始，图中不存在顶点d时，返回-1.
{
	for (int v = 0; v < vexNum; v++)
		if (vertexes[v] == d)
			return v; // 顶点d存在,返回它的序号
	return -1;		  // 顶点d不存在,返回-1
}

template <class ElemType, class WeightType>
Status AdjMatrixUndirGraph<ElemType, WeightType>::GetElem(int v, ElemType &d) const
// 操作结果：求序号为v的顶点值, v的取值范围为0 ≤ v ＜ vexNum, v合法时函数
// 通过d取得顶点值，并返回ENTRY_FOUND；否则函数返回NOT_PRESENT
{
	if (v < 0 || v >= vexNum)
		return NOT_PRESENT; // v范围错,返回元素不存在
	else
	{
		d = vertexes[v];	// 将顶点v的元素值赋给d
		return ENTRY_FOUND; // 返回元素存在
	}
}

template <class ElemType, class WeightType>
Status AdjMatrixUndirGraph<ElemType, WeightType>::SetElem(int v, const ElemType &d)
// 操作结果：设置顶点的元素值v的取值范围为0 ≤ v ＜ vexNum, v合法时函数返回
//	SUCCESS, 否则函数返回RANGE_ERROR
{
	if (v < 0 || v >= vexNum)
		return RANGE_ERROR; // v范围错,返回位置错
	else
	{
		vertexes[v] = d; // 将顶点元素的值改为d
		return SUCCESS;	 // 返回修改成功
	}
}

template <class ElemType, class WeightType>
int AdjMatrixUndirGraph<ElemType, WeightType>::GetVexNum() const
// 操作结果：返回顶点个数
{
	return vexNum;
}

template <class ElemType, class WeightType>
int AdjMatrixUndirGraph<ElemType, WeightType>::GetArcNum() const
// 操作结果：返回边数
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
// 操作结果：返回顶点v的第1个邻接点的序号
{
	if (v < 0 || v >= vexNum)
		throw Error("v不合法!"); // 抛出异常

	for (int u = 0; u < vexNum; u++)
		if (arcs[v][u] != 0)
			return u;

	return -1; // 返回-1表示无邻接点
}

template <class ElemType, class WeightType>
int AdjMatrixUndirGraph<ElemType, WeightType>::NextAdjVex(int v1, int v2) const
// 操作结果：返回顶点v1的相对于v2的下一个邻接点
{
	if (v1 < 0 || v1 >= vexNum)
		throw Error("v1不合法!"); // 抛出异常
	if (v2 < 0 || v2 >= vexNum)
		throw Error("v2不合法!"); // 抛出异常
	if (v1 == v2)
		throw Error("v1不能等于v2!"); // 抛出异常

	for (int u = v2 + 1; u < vexNum; u++)
		if (arcs[v1][u] != 0)
			return u;

	return -1; // 返回-1表示无下一个邻接点
}

template <class ElemType, class WeightType>
void AdjMatrixUndirGraph<ElemType, WeightType>::InsertVex(const ElemType &d)
// 操作结果：插入顶点d
{
	if (vexNum == vexMaxNum)
		throw Error("图的顶点数不能超过允许的最大数!"); // 抛出异常

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
// 操作结果：插入依附顶点v1和v2的边
{
	int vv1 = v1 - 65,vv2=v2-65;
	if (vv1 < 0 || vv1 >= vexNum)
		throw Error("v1不合法!"); // 抛出异常
	if (vv2 < 0 || vv2 >= vexNum)
		throw Error("v2不合法!"); // 抛出异常
	if (vv1 == vv2)
		throw Error("v1不能等于v2!"); // 抛出异常

	if (arcs[vv1][vv2] == infinity)
	{ // 原无向图中没有边(v1, v2)
		arcNum++;
		arcs[vv1][vv2] = w;
		arcs[vv2][vv1] = w;
	}
}

template <class ElemType, class WeightType>
void AdjMatrixUndirGraph<ElemType, WeightType>::DeleteVex(const ElemType &d)
// 操作结果：删除元素为d的顶点
{
	int v;
	for (v = 0; v < vexNum; v++)
		if (vertexes[v] == d)
			break;
	if (v == vexNum)
		throw Error("图中不存在要删除的顶点!"); // 抛出异常

	for (int u = 0; u < vexNum; u++) // 删除与顶点d相关联的边
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
// 操作结果：删除依附顶点v1和v2的边
{
	if (v1 < 0 || v1 >= vexNum)
		throw Error("v1不合法!"); // 抛出异常
	if (v2 < 0 || v2 >= vexNum)
		throw Error("v2不合法!"); // 抛出异常
	if (v1 == v2)
		throw Error("v1不能等于v2!"); // 抛出异常

	if (arcs[v1][v2] != 0)
	{ // 原无向图存在边(v1, v2)
		arcNum--;
		arcs[v1][v2] = 0;
		arcs[v2][v1] = 0;
	}
}

template <class ElemType, class WeightType>
Status AdjMatrixUndirGraph<ElemType, WeightType>::GetTag(int v) const
// 操作结果：返回顶点v的标志
{
	if (v < 0 || v >= vexNum)
		throw Error("v不合法!"); // 抛出异常

	return tag[v];
}

template <class ElemType, class WeightType>
void AdjMatrixUndirGraph<ElemType, WeightType>::SetTag(int v, Status val) const
// 操作结果：设置顶点v的标志为val
{
	if (v < 0 || v >= vexNum)
		throw Error("v不合法!"); // 抛出异常

	tag[v] = val;
}

template <class ElemType, class WeightType>
AdjMatrixUndirGraph<ElemType, WeightType>::AdjMatrixUndirGraph(const AdjMatrixUndirGraph<ElemType, WeightType> &g)
// 操作结果：由无向图的邻接矩阵g构造新无向图的邻接矩阵g——复制构造函数
{
	vexNum = g.vexNum;
	vexMaxNum = g.vexMaxNum;
	arcNum = g.arcNum;

	vertexes = new ElemType[vexMaxNum];				   // 生成顶点数据数组
	tag = new Status[vexMaxNum];					   // 生成标志数组
	arcs = (WeightType **)new WeightType *[vexMaxNum]; // 生成邻接矩阵
	for (int v = 0; v < vexMaxNum; v++)
		arcs[v] = new WeightType[vexMaxNum];

	for (int v = 0; v < vexNum; v++)
	{ // 复制顶点数据数组
		vertexes[v] = g.vertexes[v];
		tag[v] = g.tag[v];
		for (int u = 0; u < vexNum; u++)
			arcs[v][u] = g.arcs[v][u];
	}
}

template <class ElemType, class WeightType>
AdjMatrixUndirGraph<ElemType, WeightType> &AdjMatrixUndirGraph<ElemType, WeightType>::operator=(const AdjMatrixUndirGraph<ElemType, WeightType> &g)
// 操作结果：将无向图的邻接矩阵g赋值给当前无向图的邻接矩阵——赋值语句重载
{
	if (&g != this)
	{
		delete[] vertexes; // 释放顶点数据
		delete[] tag;	   // 释放标志

		for (int v = 0; v < vexMaxNum; v++) // 释放邻接矩阵的行
			delete[] arcs[v];
		delete[] arcs; // 释放邻接矩阵
		vexNum = g.vexNum;
		vexMaxNum = g.vexMaxNum;
		arcNum = g.arcNum;

		vertexes = new ElemType[vexMaxNum];	 // 生成顶点数据数组
		tag = new Status[vexMaxNum];		 // 生成标志数组
		arcs = (int **)new int *[vexMaxNum]; // 生成邻接矩阵
		for (int v = 0; v < vexMaxNum; v++)
			arcs[v] = new int[vexMaxNum];

		for (int v = 0; v < vexNum; v++)
		{ // 复制顶点数据数组
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
// 操作结果: 显示邻接矩阵无向图
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
// 初始条件：存在图g
// 操作结果：对无向图g进行深度优先遍历
{
	int v;
	for (v = 0; v < g.GetVexNum(); v++)
		g.SetTag(v, UNVISITED); // 对每个顶点设置未访问标志

	for (v = 0; v < g.GetVexNum(); v++)

		if (g.GetTag(v) == UNVISITED)
		{
			d++;
			DFS(g, v, Visit); // 从尚未访问的顶点v开始进行深度优先搜索
		}
}

template <class ElemType, class WeightType>
void DFS(const AdjMatrixUndirGraph<ElemType, WeightType> &g, int v, void (*Visit)(const ElemType &))
// 初始条件：存在图g
// 操作结果：从顶点v出发进行深度优先搜索
{
	ElemType e;
	g.SetTag(v, VISITED); // 设置顶点v已访问标志
	g.GetElem(v, e);	  // 取顶点v的数据元素值
	// Visit(e);			  // 访问顶点v
	for (int w = g.FirstAdjVex(v); w != -1; w = g.NextAdjVex(v, w))
		if (g.GetTag(w) == UNVISITED)
			DFS(g, w, Visit); // 从v的尚未访问过的邻接顶点w开始进行深度优先搜索
}

template <class ElemType, class WeightType>
void ShortestPathFloyd(const AdjMatrixUndirGraph<ElemType, WeightType> &g, int **path,
					   WeightType **dist)
// 操作结果: 用Floyd算法求有向网g中各对顶点u和v之间的最短路径path[u][v]和路径长度
//	dist[u][v],path[u][v]存储从u到v的最短路径上至此顶点的前一顶点的顶点号,dist[u][v]
//	存储从u到v的最短路径的长度
{
	for (int u = 0; u < g.GetVexNum(); u++)
		for (int v = 0; v < g.GetVexNum(); v++)
		{ // 初始化path和dist
			dist[u][v] = (u != v) ? g.GetWeight(u, v) : 0;
			if (u != v && dist[u][v] < g.GetInfinity())
				path[u][v] = u; // 存在边<u,v>
			else
				path[u][v] = -1; // 不存在边<u,v>
			
		}

	for (int k = 0; k < g.GetVexNum(); k++)
		for (int i = 0; i < g.GetVexNum(); i++)
			for (int j = 0; j < g.GetVexNum(); j++)
				if (dist[i][k] + dist[k][j] < dist[i][j])
				{
					// 从i到k再到j的路径长度更短
					dist[i][j] = dist[i][k] + dist[k][j];
					path[i][j] = path[k][j];
				}
				
}

template <class ElemType, class WeightType>
WeightType AdjMatrixUndirGraph<ElemType, WeightType>::GetInfinity() const
// 操作结果：返回无穷大的值
{
	return infinity;
}

template <class ElemType, class WeightType>
void DisplayPathAndDist(const AdjMatrixUndirGraph<ElemType, WeightType> &g, int **path, WeightType **dist,ElemType e1,ElemType e2)
{
	int v1 = e1 - 65, v2 = e2 - 65;
	cout << endl;
	if (dist[v1][v2] < g.GetInfinity())
	{ // 存在从v1到v2最短路径
	cout << "从 " << e1 << " 到 " << e2 << ":";
	cout << " 路径长度 = " << dist[v1][v2];
	cout << " 路径：";
	LinkStack<int> s; // 存储路上的顶点
		int v = v2;
		while (v != v1)
		{
			s.Push(v);		 // v为路径上的顶点
			v = path[v1][v]; // 取上路径上的前一个顶点
		}
		s.Push(v1); // v是路径上起始点
		while (!s.IsEmpty())
		{ // 输出路上的顶点
			s.Pop(v);
			g.GetElem(v, e1);
			cout << e1 << " ";
		}
	}
	else
	{ // 从v1到v2无路径
		cout << "from " << e1 << " to " << e2 << ":";
		cout << " dist = ∞";
	}
	cout << endl;
}

#endif
