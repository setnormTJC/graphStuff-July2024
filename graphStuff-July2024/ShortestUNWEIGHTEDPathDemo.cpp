#include"Graph.h"

#include"direct.h" //for _chdir() to image file containing picture of graph used

/*A (to scale) photo of the graph generated here is contained in the 
image file "AWeightedGraph.jpg" in the same folder as the .sln file*/
WeightedUndirectedGraph  generatedAnExampleWeightedGraph()
{
	WeightedUndirectedGraph anExampleWeightedGraph; 

	anExampleWeightedGraph.vertices = { "A", "B", "C", "D", "E", "F", "G" };

	anExampleWeightedGraph.edges =
	{
		{"A", "B", 3}, {"A", "C", 1}, {"A", "D", 6},
														{"B", "E", 2},
														{"C", "E", 4},			{"C", "F", 5},
																				{"D", "F", 4},
																									{"E", "G", 7},
																									{"F", "G", 5}
	};

	return anExampleWeightedGraph; 
}


int main(int argc, char* argv)
{
	auto anExampleWeightedGraph = generatedAnExampleWeightedGraph(); 

	string startingVertex = "A"; 
	string endingVertex = "G"; 

	//anExampleWeightedGraph.traverseBreadthFirst(startingVertex, endingVertex);


	//_chdir("C:\\Users\\Work\\Desktop\\myCppLibrary\\dataStructs\\graphStuff-July2024");

	//system("AWeightedGraph.jpg"); //ridiculous 

	cout << anExampleWeightedGraph.traverseShortestPath_assumingEqualWeightPaths(startingVertex, endingVertex) << " edges traversed from start to finish\n";
	

	//cin.get(); 


	//Demoing a graph containing a loop (and verifying that a vertex can be a neighbor of itself)
	//WeightedUndirectedGraph w; 
	//w.vertices = { "A", "B" }; 
	//w.edges =
	//{
	//	{"A", "B", 2},
	//	{"A", "A", 1}
	//}; 

	//auto neighs = w.getNeighborsOfVertex("A"); 
	//for (auto theNeighbor : neighs)
	//{
	//	cout << theNeighbor << endl; 
	//}
}