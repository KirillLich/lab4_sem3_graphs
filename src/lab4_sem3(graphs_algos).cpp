// lab4_sem3(graphs_algos).cpp: определяет точку входа для приложения.
//

#include "lab4_sem3(graphs_algos).h"
#include <utility>
#include "DictionaryStructs\HashTable.h"
#include "Graph.h"

int main()
{
	Graph<char, int> g;
	g.Add(std::pair<char, char>('a', 'b'), 5);
	std::cout << g.IsInUse(std::pair<char, char>('b', 'a'));
}
