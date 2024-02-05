#include "..\Graph.h"
#include <assert.h>

void TestAdd()
{
	Graph<int, int> g;
	assert(g.GetVertecesCount()==0);
	g.Add(std::pair<int, int>(0,1), 10);
	assert(g.GetVertecesCount() == 2);
	g.Add(std::pair<int, int>(0, 2), 10);
	assert(g.GetVertecesCount() == 3);
}

void TestIsInUse()
{
	Graph<int, int> g;
	g.Add(std::pair<int, int>(0, 1), 10);
	g.Add(std::pair<int, int>(0, 2), 10);
	assert(g.IsInUse(std::pair<int,int>(0, 1)));
	assert(!g.IsInUse(std::pair<int, int>(2, 1)));
}


int main()
{
	TestAdd();
	TestIsInUse();
}