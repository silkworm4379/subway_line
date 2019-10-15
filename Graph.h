#pragma once

#include <iostream>
#include <vector>
//����ͼ �ڽӾ���ʵ��

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


//��Я����
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

//����ͼ
template<typename Vertex, typename Edge>
class Graph
{
	//��������
public:
	struct EdgeInfo 
	{
		int first{0};//��һ������
		int second{0};//�ڶ�������
		Edge edge{};//������
	};

	struct Unit
	{
		double weight{INF};//Ȩ��,Ȩ��ΪINF���ʾ������
		Edge edge;
		friend ostream& operator<<(ostream& os, const Unit& u)
		{
			os << u.weight<<' '<<u.edge;
			return os;
		}

		//ת��Ϊdouble
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
	using Matrix_path = vector<IntVector>;//·������
	using Matrix_dist = vector<DoubleVector>;//�������
	
private:
	VertexVector vertexes;//���㶨��
	Matrix matrix;//�ڽӾ���(��ά��,ÿ��Ԫ�ض���pair)
	Matrix_path matrix_path;//·������
	Matrix_dist matrix_dist;//�������
public:
	//���캯��(ָ������ͱ�)
	Graph(const vector<Vertex> &_vertexes,const EdgeVector&edges)
		:vertexes(_vertexes)
	{
		initFromEdgeVector(edges);//�����
	}

	bool isConnected(const int &v0,const int &v1)
	{
		return matrix[v0][v1].weight != 0;
	}

	//floyd�㷨
	bool floyd()
	{
		int i, j, k, num_v = vertexes.size();
		
		double temp;
		
		//���ռ�
		IntVector row_int;
		DoubleVector row_double;
		row_int.assign(num_v, 0);
		row_double.assign(num_v, 0.0);
		matrix_path.assign(num_v, row_int);
		matrix_dist.assign(num_v, row_double);
		
		for (i=0;i< num_v;i++)
			for (j = 0; j < num_v; j++)
			{
				matrix_dist[i][j] = matrix[i][j];//��ʼ���������
				matrix_path[i][j] = i;//��ʼ��·������
			}

		//����ѭ��
		for (k = 0; k < num_v; k++)
			for (i = 0; i < num_v; i++)
				for (j = 0; j < num_v; j++)
					if(matrix_dist[i][k]!=INF&& matrix_dist[k][j]!=INF)
					if ((temp = matrix_dist[i][k] + matrix_dist[k][j]) < matrix_dist[i][j]|| matrix_dist[i][j]==INF)
					{
						//���¾����·��
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


	//���
	friend ostream& operator<<(ostream& os,const Graph&g)
	{
		os << g.vertexes << g.matrix;
		os << g.matrix_path;
		return os;
	}

private:
	void initFromEdgeVector(const EdgeVector& edges)
	{
		int num_v = vertexes.size();//��ȡ������
		int i,j;
		int num_edge = edges.size();

		vector<Unit> row_empty;
		Unit u_t;
		row_empty.assign(num_v,u_t);
		//���󿪿ռ�
		matrix.assign(num_v,row_empty);

		for (i=0;i<num_edge;i++)
		{
			u_t.weight = edges[i].edge;
			u_t.edge = edges[i].edge;
			//���к���
			matrix[edges[i].first][edges[i].second] = u_t;
			matrix[edges[i].second][edges[i].first] = u_t;
		}

	}


};








