//#include"Graph.h"
//
//WeightedUndirectedGraph generateGraphOfFourCities()
//{
//	WeightedUndirectedGraph graphOfFourCities; 
//
//	//it would be reasonable to add these vertices in ALPHABETICAL order (because next_permutation may be used in TSP algo) 
//	graphOfFourCities.addVertex("Albuquerque");
//	graphOfFourCities.addVertex("Atlanta");
//	graphOfFourCities.addVertex("Austin"); 
//	graphOfFourCities.addVertex("Chicago");
//
//	graphOfFourCities.addEdge("Albuquerque", "Chicago", 1100);
//	graphOfFourCities.addEdge("Albuquerque", "Atlanta", 1200);
//	graphOfFourCities.addEdge("Albuquerque", "Austin", 600);
//
//	graphOfFourCities.addEdge("Austin", "Chicago", 1000);
//	graphOfFourCities.addEdge("Austin", "Atlanta", 800);
//
//	graphOfFourCities.addEdge("Atlanta", "Chicago", 600); 
//
//
//	return graphOfFourCities;
//
//}
//
//WeightedUndirectedGraph generateGraphOf5Cities()
//{
//	WeightedUndirectedGraph graphOf5Cities;
//
//	//it would be reasonable to add these vertices in ALPHABETICAL order (because next_permutation may be used in TSP algo) 
//	graphOf5Cities.addVertex("Albuquerque");
//	graphOf5Cities.addVertex("Atlanta");
//	graphOf5Cities.addVertex("Austin");
//	graphOf5Cities.addVertex("Chicago");
//	graphOf5Cities.addVertex("Denver");
//
//	graphOf5Cities.addEdge("Albuquerque", "Atlanta", 1250);
//	graphOf5Cities.addEdge("Albuquerque", "Austin", 600);
//	graphOf5Cities.addEdge("Albuquerque", "Chicago", 1100);
//	graphOf5Cities.addEdge("Albuquerque", "Denver", 300);
//
//
//	graphOf5Cities.addEdge("Atlanta", "Austin", 800);
//	graphOf5Cities.addEdge("Atlanta", "Chicago", 550);
//	graphOf5Cities.addEdge("Atlanta", "Denver", 1200);
//
//	graphOf5Cities.addEdge("Austin", "Chicago", 1000);
//	graphOf5Cities.addEdge("Austin", "Denver", 750);
//
//	graphOf5Cities.addEdge("Chicago", "Denver", 900);
//
//
//	return graphOf5Cities;
//
//}
//
//
//int main(int argc, char* argv)
//{
//	auto graphOfFourCities = generateGraphOfFourCities(); 
//	//graphOfFourCities.isCompleteGraph()
//	string startCity = "Austin"; 
//	
//	//srand(time(0));
//
//	//graphOfFourCities.bruteForceTSP_November14(startCity); 
//
//
//	auto graphOf5Cities = generateGraphOf5Cities(); 
//
//	//cout << std::boolalpha; 
//	//cout << graphOf5Cities.isCompleteGraph() << "\n";
//
//	graphOf5Cities.bruteForceTSP_November14(startCity); 
//
//	
//	
//	//string endCity = "Chicago"; 
//
//	//graphOfFourCities.takeRandomWalk_UntilSomeEnd(startCity, endCity);
//
//	//graphOfFourCities.findDijkstraShortestPath(startCity, endCity); 
//
//	//cout << graphOfFourCities.findEdgeWeight(startCity, endCity) << "\n";
//	
//	//auto neighs = graphOfFourCities.getNeighborsOfVertex(startCity); 
//
//	//for (auto& neigh : neighs)
//	//{
//	//	cout << neigh << "\n";
//	//}
//
//	//cout << graphOfFourCities.isCompleteGraph();
//	
//
//	//auto map = graphOfFourCities.mapDegreesOfAllVertices(); 
//	//for (auto& pair : map)
//	//{
//	//	cout << pair.first << "\t" << pair.second << "\n";
//	//}
//
//	//graphOfFourCities.removeVertex_andAnyAssociatedEdges(startCity); 
//
//
//
//	return 0; 
//}