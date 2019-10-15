#pragma once

#include <iostream>
#include <vector>
//无向图 邻接矩阵实现

//struct V_Empty
//{
//	int a;
//};
//typedef V_Empty Vertex;
//
//struct E_Empty
//{
//	int a;
//};
//typedef E_Empty Edge;

using namespace std;


//便携函数
template<typename t>
ostream& operator<<(ostream& os,const std::vector<t> &v)
{
	os << "[ ";
	int i,size=v.size();
	if(size!=0)
		os << v[0];
	for (i=1;i<size;i++)
	{
		os <<", \n"<< v[i];
	}
	os << " ]\n";
	return os;
}


typedef vector<int> PathVector;



constexpr double INF = 0;

//无向图
template<typename Vertex, typename Edge>
class Graph
{
	//基本声明
public:
	struct EdgeInfo 
	{
		int first{0};//第一个顶点
		int second{0};//第二个顶点
		Edge edge{};//边属性
	};

	struct Unit
	{
		double weight{INF};//权重,权重为INF则表示不连接
		Edge edge;
		friend ostream& operator<<(ostream& os, const Unit& u)
		{
			os << u.weight<<' '<<u.edge;
			return os;
		}

		//转换为double
		operator double()const
		{
			return weight;
		}
	};

	using EdgeVector = vector<EdgeInfo>;
	using UnitVector = vector <Unit>;
	using Matrix = vector<UnitVector>;
	using VertexVector = vector<Vertex>;


	using IntVector = vector<int>;
	using DoubleVector = vector<double>;
	using Matrix_path = vector<IntVector>;//路径矩阵
	using Matrix_dist = vector<DoubleVector>;//距离矩阵
	
private:
	VertexVector vertexes;//顶点定义
	Matrix matrix;//邻接矩阵(二维表,每个元素都是pair)
	Matrix_path matrix_path;//路径矩阵
	Matrix_dist matrix_dist;//距离矩阵
public:
	//构造函数(指定顶点和边)
	Graph(const vector<Vertex> &_vertexes,const EdgeVector&edges)
		:vertexes(_vertexes)
	{
		initFromEdgeVector(edges);//导入边
	}

	bool isConnected(const int &v0,const int &v1)
	{
		return matrix[v0][v1].weight != 0;
	}

	//floyd算法
	bool floyd()
	{
		int i, j, k, num_v = vertexes.size();
		
		double temp;
		
		//开空间
		IntVector row_int;
		DoubleVector row_double;
		row_int.assign(num_v, 0);
		row_double.assign(num_v, 0.0);
		matrix_path.assign(num_v, row_int);
		matrix_dist.assign(num_v, row_double);
		
		for (i=0;i< num_v;i++)
			for (j = 0; j < num_v; j++)
			{
				matrix_dist[i][j] = matrix[i][j];//初始化距离矩阵
				matrix_path[i][j] = i;//初始化路径矩阵
			}

		//三重循环
		for (k = 0; k < num_v; k++)
			for (i = 0; i < num_v; i++)
				for (j = 0; j < num_v; j++)
					if(matrix_dist[i][k]!=INF&& matrix_dist[k][j]!=INF)
					if ((temp = matrix_dist[i][k] + matrix_dist[k][j]) < matrix_dist[i][j]|| matrix_dist[i][j]==INF)
					{
						//更新距离和路径
						matrix_dist[i][j] = temp;
						matrix_path[i][j] = matrix_path[k][j];
					}
						

		return true;
	}

	PathVector getPath(const int &v0,const int &v1)
	{
		int k;
		k = v1;
		PathVector res;
		if (matrix_dist[v0][v1] == INF)
			return res;
		while (k != v0)
		{
			res.push_back(k);
			k = matrix_path[v0][k];
		}
		res.push_back(k);
		std::reverse(res.begin(), res.end());
		return res;
	}


	//输出
	friend ostream& operator<<(ostream& os,const Graph&g)
	{
		os << g.vertexes << g.matrix;
		os << g.matrix_path;
		return os;
	}

private:
	void initFromEdgeVector(const EdgeVector& edges)
	{
		int num_v = vertexes.size();//获取顶点数
		int i,j;
		int num_edge = edges.size();

		vector<Unit> row_empty;
		Unit u_t;
		row_empty.assign(num_v,u_t);
		//矩阵开空间
		matrix.assign(num_v,row_empty);

		for (i=0;i<num_edge;i++)
		{
			u_t.weight = edges[i].edge;
			u_t.edge = edges[i].edge;
			//先行后列
			matrix[edges[i].first][edges[i].second] = u_t;
			matrix[edges[i].second][edges[i].first] = u_t;
		}

	}


};








