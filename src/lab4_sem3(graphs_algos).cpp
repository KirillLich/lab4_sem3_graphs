// lab4_sem3(graphs_algos).cpp: определяет точку входа для приложения.
//

#include "lab4_sem3(graphs_algos).h"
#include <utility>
#include "DictionaryStructs\HashTable.h"
#include "Graph.h"
#include "UI_funcs.h"

void ColorGraph(Graph<char, int>& g)
{
	IDictionary<char, int>* colored = g.Color();
	for (auto i : g.GetVertices())
	{
		std::cout << '\n' << i << " color: " << colored->Get(i);
	}
	delete colored;
}

void SearchConnectedComponents(Graph<char, int>& g)
{
	IDictionary<char, int>* dict = g.ConnectedComponents();
	for (std::size_t i = 0; i < g.GetVertecesCount(); i++)
	{
		std::cout << "\nVertex: " << g.GetVertices()[i] << ", component: " << dict->Get(g.GetVertices()[i]);
	}
	delete dict;
}

int main()
{
	Graph<char, int> g;

	std::cout << "Write number of edges\n";
	std::size_t edgesNum = TakeItem<std::size_t>("Use unsigned int");

	if(edgesNum) std::cout << "Write " << edgesNum << " graph edges in format: \<char\> \<char\> \<size_t\>\n";

	char firstVertex = 0, secondVertex = 0;
	std::size_t weight = 0;

	for (std::size_t i = 0; i < edgesNum; i++)
	{
		std::cout << '\n' << i + 1 << " edge:\n";
		firstVertex = TakeItem<char>("Use char sympols");
		secondVertex = TakeItem<char>("Use char sympols");
		weight = TakeItem<std::size_t>("Use unsigned int");

		g.Add(std::pair<char, char>(firstVertex, secondVertex), weight);
	}

	std::cout << "Write number of solo vertices\n";
	std::size_t soloNum = TakeItem<std::size_t>("Use unsigned int");
	char coloVertex = 0;

	for (std::size_t i = 0; i < soloNum; i++)
	{
		std::cout << '\n' << i + 1 << " solo vertex:\n";
		firstVertex = TakeItem<char>("Use char sympols");

		g.Add(firstVertex);
	}

	bool exit = false;
	Graph<char, int>*sG = g.Skeleton();
	std::cout << "1. SearchConnectedComponents 2. ColorGraph 3. Skeleton 4. Exit\n";
	while (! exit)
	{
		switch (TakeItem<int>("Use numbers from 1 to 4"))
		{
		case 1:
			SearchConnectedComponents(g);
			break;
		case 2:
			ColorGraph(g);
			break;
		case 3:
			VizualiseGraph(sG);
			break;
		case 4:
			exit = true;
			break;
		default:
			std::cout << "Use numbers from 1 to 4\n";
		}
	}
	delete sG;
}
