#pragma once
#include "DictionaryStructs\Dictionary.h"
#include "PairHash.h"
#include <vector>

#include <iostream>
#include <unordered_map>
#include <set>
#include <queue>
#include <unordered_set>
#include <stack>
#include <list>
#include <algorithm>
#include <iomanip>

template <typename TVertex, typename TWeight>
class Graph
{
private:

	class Edge
	{
		TWeight weight;
		std::pair<TVertex, TVertex> vertices;
	public:

		TVertex& first()
		{
			return vertices.first;
		}

		TVertex& second()
		{
			return vertices.second;
		}

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

		void Reverse()
		{
			std::pair<TVertex, TVertex> reversePair(vertices.second, vertices.first);
			vertices.swap(reversePair);
		}
	};

	IDictionary<TVertex, std::vector<Edge>>* container;
	std::vector<TVertex> vertices;

	template <typename TVertex, typename TWeight>
	friend void VizualiseGraph(Graph<TVertex, TWeight>* graph);

	void Dive(TVertex currentVertex, IDictionary<TVertex, bool>* usedVertices, IDictionary<TVertex, int>* components, int compNumber)
	{
		usedVertices->Get(currentVertex) = true;
		components->Add(currentVertex, compNumber);
		std::vector<Edge> binds = container->Get(currentVertex);
		for (size_t i = 0; i < binds.size(); i++)
		{
			if(!usedVertices->Get(binds[i].second()))
				this->Dive(binds[i].second(), usedVertices, components, compNumber);
		}
	}

public:
	Graph(const Graph<TVertex, TWeight>& graph) = delete;

	Graph()
	{
		container = MakeDictionary<TVertex, std::vector<Edge>>();
	};

	~Graph()
	{
		delete container;
	}

	std::size_t GetVertecesCount()
	{
		return vertices.size();
	}

	std::vector<TVertex> GetVertices()
	{
		return vertices;
	}
	
	//contains bind
	bool IsInUse(std::pair<TVertex, TVertex> bind)
	{
		bool out = false;
		if(container->ContainsKey(bind.first)) 
			for (std::size_t i = 0; i < container->Get(bind.first).size(); i++)
			{
				out = out || ((container->Get(bind.first))[i].IsSame(bind));
			}
		return out;
	}

	void Add(std::pair<TVertex, TVertex> bind, TWeight weight)
	{
		if (!(this->IsInUse(bind)))
		{
			Edge current(bind, weight);

			if (!container->ContainsKey(bind.first))
			{
				vertices.push_back(bind.first);
				std::vector<Edge> adBinds{current};
				container->Add(bind.first, adBinds);
			}
			else
			{
				container->Get(bind.first).push_back(current);
			}
			current.Reverse();
			if (!container->ContainsKey(bind.second))
			{
				vertices.push_back(bind.second);
				std::vector<Edge> adBinds{ current };
				container->Add(bind.second, adBinds);
			}
			else
			{
				container->Get(bind.second).push_back(current);
			}
		}
		else
		{
			throw std::runtime_error("Bind is already added");
		}
	}

	void Add(TVertex soloVertex)
	{
		if (!container->ContainsKey(soloVertex))
		{
			container->Add(soloVertex, std::vector<Edge>());
			vertices.push_back(soloVertex);
		}
		else
			throw std::runtime_error("Vertex is already added");
	}

	//get coloration
	IDictionary<TVertex, int>* Color()
	{
		IDictionary<TVertex, int>* coloredVertices = MakeDictionary<TVertex, int>();
		std::vector<bool> usedColors;

		for (std::size_t i = 0; i < vertices.size(); i++)
		{
			usedColors.push_back(false);
		}

		for (std::size_t j = 0; j < vertices.size(); j++)
		{
			TVertex currentVertex = vertices[j];
			std::vector<Edge>adjVertices = container->Get(currentVertex);
			for (std::size_t i = 0; i < adjVertices.size(); i++)
			{
				if (coloredVertices->ContainsKey(adjVertices[i].second()))
					usedColors[coloredVertices->Get(adjVertices[i].second())] = true;
			}

			int currentColor = 0;

			for (std::size_t i = 0; i < usedColors.size(); i++)
			{
				if (!usedColors[i])
				{
					currentColor = i;
					break;
				}
			}

			coloredVertices->Add(currentVertex, currentColor);

			for (std::size_t i = 0; i < vertices.size(); i++)
			{
				usedColors[i] = false;
			}
		}

		return coloredVertices;
	}

	//get
	IDictionary<TVertex, int>* ConnectedComponents()
	{
		IDictionary<TVertex,bool>* usedVertices = MakeDictionary<TVertex, bool>();
		IDictionary<TVertex, int>* components = MakeDictionary<TVertex, int>();
		for (auto currentVertex : vertices)
		{
			usedVertices->Add(currentVertex, false);
		}

		int compNumber = 1;
		for (auto currentVertex : vertices)
		{
			if (!usedVertices->Get(currentVertex))
			{
				Dive(currentVertex, usedVertices, components, compNumber);
				compNumber++;
			}
		}
		delete usedVertices;
		return components;
	}

	//get
	Graph<TVertex, TWeight>* Skeleton()
	{
		IDictionary<TVertex, bool>* usedVertices = MakeDictionary<TVertex, bool>();
		for (auto currentVertex : vertices)
		{
			usedVertices->Add(currentVertex, false);
		}

		Graph<TVertex, TWeight>* resultGraph = new Graph<TVertex, TWeight>();

		for (auto currentVertex : vertices)
		{
			usedVertices->Get(currentVertex) = true;
			for (auto binds : container->Get(currentVertex))
			{
				if(!usedVertices->Get(binds.second()))
					resultGraph->Add(std::pair<TVertex, TVertex>(currentVertex, binds.second()), binds.GetWeight());
				usedVertices->Get(binds.second()) = true;
			}
		}

		return resultGraph;
	}
};

template <typename TVertex, typename TWeight>
void VizualiseGraph(Graph<TVertex, TWeight>* graph)
{
	IDictionary<TVertex, bool>* usedVertices = MakeDictionary<TVertex, bool>();
	for (auto currentVertex : graph->vertices)
	{
		usedVertices->Add(currentVertex, false);
	}

	for (auto currentVertex : graph->vertices)
	{
		for (std::size_t i = 0; i < graph->container->Get(currentVertex).size(); i++)
		{
			TVertex neighbour = graph->container->Get(currentVertex)[i].second();
			if (!(usedVertices->Get(currentVertex)|| usedVertices->Get(neighbour)))
				std::cout << currentVertex << '-' << neighbour << '\n';
		}
		usedVertices->Get(currentVertex) = true;
	}
};