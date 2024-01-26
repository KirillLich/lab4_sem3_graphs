#pragma once
#include "DictionaryStructs\Dictionary.h"
#include "PairHash.h"
#include <vector>

template <typename TVertex, typename TWeight>
class Graph
{


private:

	class Edge
	{
		std::pair<TVertex, TVertex> vertices;
		TWeight weight;
	public:

		Edge(std::pair<TVertex, TVertex> V, TWeight W) : vertices(V), weight(W) {};

		TWeight GetWeight()
		{
			return weight;
		}

		bool IsSame(const Edge& another)
		{
			bool containFirst = (another.vertices.first == this->vertices.first) || (another.vertices.second == this->vertices.first);
			bool containSecond = (another.vertices.first == this->vertices.second) || (another.vertices.second == this->vertices.second);
			return containFirst && containSecond;
		}

		bool IsSame(const std::pair<TVertex, TVertex> another)
		{
			bool containFirst = (another.first == this->vertices.first) || (another.second == this->vertices.first);
			bool containSecond = (another.first == this->vertices.second) || (another.second == this->vertices.second);
			return containFirst && containSecond;
		}
	};

	IDictionary<std::pair<TVertex, TVertex>, Edge>* container;
	std::vector<std::pair<TVertex, TVertex>> binds;
	std::size_t vertecesNumber;

	template <typename TVertex>
	friend void VizualiseGraph(Graph<TVertex, TWeight> graph);

public:
	Graph(const Graph<TVertex, TWeight>& graph) :binds(graph.binds), vertecesNumber(graph.vertecesNumber)
	{
		container = MakeDictionary<std::pair<TVertex, TVertex>, Edge>(graph.container);
	};

	Graph():vertecesNumber(0) 
	{
		container = MakeDictionary<std::pair<TVertex, TVertex>, Edge>();
	};

	bool IsInUse(std::pair<TVertex, TVertex> bind)
	{
		std::pair<TVertex, TVertex> reverseBind(bind.second, bind.first);
		return container->ContainsKey(bind) || container->ContainsKey(reverseBind);
	}

	void Add(std::pair<TVertex, TVertex> bind, TWeight weight)
	{
		if (!(this->IsInUse(bind)))
		{
			Edge current(bind, weight);
			container->Add(bind, current);
			binds.push_back(bind);
			vertecesNumber++;
		}
	}


};
//
//template <typename TVertex>
//void VizualiseGraph(Graph<TVertex> graph)
//{
//	
//}