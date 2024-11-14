#include"Graph.h"

WeightedUndirectedGraph generateGraphOfFourCities()
{
	WeightedUndirectedGraph graphOfFourCities; 

	graphOfFourCities.addVertex("Albuquerque");
	graphOfFourCities.addVertex("Atlanta");
	graphOfFourCities.addVertex("Austin"); 
	graphOfFourCities.addVertex("Chicago");

	graphOfFourCities.addEdge("Albuquerque", "Chicago", 1100);
	graphOfFourCities.addEdge("Albuquerque", "Atlanta", 1200);
	graphOfFourCities.addEdge("Albuquerque", "Austin", 600);

	graphOfFourCities.addEdge("Austin", "Chicago", 1000);
	graphOfFourCities.addEdge("Austin", "Atlanta", 800);

	graphOfFourCities.addEdge("Atlanta", "Chicago", 600); 


	return graphOfFourCities;

}


int main(int argc, char* argv)
{
	auto graphOfFourCities = generateGraphOfFourCities(); 
	//graphOfFourCities.isCompleteGraph()
	string startCity = "Austin"; 
	
	srand(time(0));

	graphOfFourCities.bruteForceTSP_November14(startCity); 





	//string endCity = "Chicago"; 

	//graphOfFourCities.takeRandomWalk_UntilSomeEnd(startCity, endCity);

	//graphOfFourCities.findDijkstraShortestPath(startCity, endCity); 

	//cout << graphOfFourCities.findEdgeWeight(startCity, endCity) << "\n";
	
	//auto neighs = graphOfFourCities.getNeighborsOfVertex(startCity); 

	//for (auto& neigh : neighs)
	//{
	//	cout << neigh << "\n";
	//}

	//cout << graphOfFourCities.isCompleteGraph();
	

	//auto map = graphOfFourCities.mapDegreesOfAllVertices(); 
	//for (auto& pair : map)
	//{
	//	cout << pair.first << "\t" << pair.second << "\n";
	//}

	//graphOfFourCities.removeVertex_andAnyAssociatedEdges(startCity); 



	return 0; 
}