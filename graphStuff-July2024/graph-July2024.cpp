#include <iostream>
#include <string>
#include <vector>
#include<fstream> 
#include<iomanip>

#include"Graph.h"

//#include<unordered_set> 

using namespace std; 

/*The example graphs G, H, and J can be found in: 
https://youtu.be/rKnKwGhRObE?si=zTbYaDpXBjXEEH7A&t=122*/
SimpleGraph generateExampleGraphG()
{
	SimpleGraph G; 
	
	G.vertices = { 1, 2, 3, 4, 5, 6 };

	G.edges = 
	{ 
		{1, 2}, {1, 3}, {1, 4},			{1, 6}, 
						{2, 4}, {2, 5}, {2, 6},
										{3, 6},
		
										{5, 6}
	};

	return G; 
}

SimpleGraph generateExampleGraphH()
{
	SimpleGraph H;

	H.vertices = { 1, 2, 3, 4, 5, 6 };

	H.edges =
	{
		{1, 2}, {1, 3}, {1, 4},			{1, 6},
						{2, 4},			{2, 6},
										{3, 6},
								{4, 5}
										
	};

	return H;
}

int main()
{
	cout << std::boolalpha; 
	auto H = generateExampleGraphH(); 
	//cout << G.isCompleteGraph() << endl; 

	//int vertexOfInterest = 6; 
	//auto neighborsOfVOI = G.getNeighborsOfVertex(vertexOfInterest); 

	//for (auto& theNeighbor : neighborsOfVOI)
	//{
	//	cout << theNeighbor << "\n";
	//}

	//int startVertex = 4; 
	//G.scanBreadth_givenStartingVertex(startVertex);
	H.fullBreadthFirstScan(); 


#pragma region Testing various methods of SimpleGraph
	//unordered_set<int> integerSet = { 2, 3, 11, 4, 5, 1 };

	////cout << integerSet.size() << endl; 
	//for (auto& element : integerSet)
	//{
	//	cout << element << endl; 

	//}

	//SimpleGraph g1;
	//g1.vertices = { 1, 2, 3, 4 };
	//g1.edges = {
	//				{1, 2}, {1, 3}, {1, 4},
	//						{2, 3}, { 2, 4 },
	//								{3, 4}
	//};

//#pragma region Demoing methods of `SimpleGraph`
//	int vertex1 = 7; 
//	int vertex2 = 1; 
//
//	if (g1.areAdjacentEdges(vertex1, vertex2))
//	{
//		cout << vertex1 << " and " << vertex2 << " are adjacent\n";
//	}
//
//	else
//	{
//		cout << vertex1 << " and " << vertex2 << " are NOT adjacent\n";
//	}
//
//
//	cout << "The ORDER of the graph (number of vertices) is: " << g1.getNumberOfVertices() << endl; 
//
//	cout << "The SIZE of the graph (number of EDGES) is : " << g1.getGraphSize() << endl; 
//
//	int vertexOfInterest = 2; 
//
//	auto neighbors = g1.getNeighborsOfVertex(vertexOfInterest); 
//	cout << "Neighbors of vertex " << vertexOfInterest << " are: \n";
//	for (auto& theNeighbor : neighbors)
//	{
//		cout << theNeighbor << " "; 
//	}
//
//	int vertexToAdd = 5; 
//
//	g1.addVertex(vertexToAdd); 
//
//	cout << "New order of graph: " << g1.getNumberOfVertices() << endl; 
//	g1.clearGraph(); 
//	cout << std::boolalpha << g1.isEmptyGraph() << endl; 
//
//#pragma endregion EndDemo

	//SimpleGraph g2; 
	//g2.vertices = { 1, 2, 3, 4 };
	//g2.edges = { {1, 2}, {2, 3} }; //empty 

	//cout << "Is graph complete? " << std::boolalpha << g1.isCompleteGraph() << endl; 
	//cout << "Is G2 complete? " << std::boolalpha << g2.isCompleteGraph() << endl; 
	
	//cout << "G2 is trivial? " << std::boolalpha << g2.isTrivialGraph() << endl; 

	//cout << g1.areAdjacentEdges({ 1, 2 }, { 1, 4 });

	//cout << (g1 == g2) << endl; 

#pragma endregion  with two graphs g1 and g


	return 0; 
}