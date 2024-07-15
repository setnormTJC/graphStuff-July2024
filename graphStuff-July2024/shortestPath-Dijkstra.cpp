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

	anExampleWeightedGraph.findDijkstraShortestPath(startingVertex, endingVertex); 


}
