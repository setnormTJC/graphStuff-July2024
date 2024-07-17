//#include"Graph.h"
//
//#include"algorithm"
//
//WeightedUndirectedGraph  generatedAnExampleWeightedGraph()
//{
//	WeightedUndirectedGraph anExampleWeightedGraph; 
//
//	anExampleWeightedGraph.vertices = { "A", "B", "C", "D", "E", "F", "G"/*, "H"*/};
//
//	anExampleWeightedGraph.edges =
//	{
//		{"A", "B", 3}, {"A", "C", 1}, {"A", "D", 6},
//														{"B", "E", 2},
//														{"C", "E", 4},			{"C", "F", 5},
//																				{"D", "F", 4},
//																									{"E", "G", 7},
//																									{"F", "G", 5}
//																													//,{"G", "H", 1284 }
//	};		
//
//	return anExampleWeightedGraph; 
//}
//
//int main(int argc, char* argv)
//{
//
//	cout << std::boolalpha; 
//
//	auto aWeightedGraph = generatedAnExampleWeightedGraph();
//
//
//
//
//	//aWeightedGraph.
//	// 
//	//string vertexToRemove = "A";
//	//aWeightedGraph.removeVertex_andAnyAssociatedEdges(vertexToRemove);
//	
//
//
//	//auto mapOfDegreesToVertices = aWeightedGraph.mapDegreesOfAllVertices(); 
//	//for (auto& thePair : mapOfDegreesToVertices)
//	//{
//	//	cout << thePair.first << "\t" << thePair.second << "\n";
//	//} 
//	// 
//	//cout << "Is it complete? " << aWeightedGraph.isCompleteGraph() << endl;
//
//
//	//WeightedUndirectedGraph aCompleteGraph; 
//
//	//aCompleteGraph.vertices = { "A", "B", "C" };
//	//aCompleteGraph.edges =
//	//{
//	//	{"A", "B", 1}, {"A", "C", 1},
//	//	{"B", "C", 1}
//	//};
//
//	//cout << aCompleteGraph.isCompleteGraph(); 
//
//	//aWeightedGraph.fullBreadthFirstScan(); 
//
//	//cout << aWeightedGraph.edges.size() << endl; 
//
//
//	//fooling with vectorName.erase method below ...
//	//vector <int> nums = { 1, 2, 3, 3, 3, 4, 5 };
//
//	//auto iterator = nums.begin(); 
//	//while (iterator != nums.end())
//	//{
//	//	if (*iterator == 3)
//	//	{
//	//		iterator = nums.erase(iterator); 
//	//	}
//
//	//	else
//	//	{
//	//		++iterator; 
//	//	}
//	//}
//
//	//std::erase(nums, 3);
//	//
//	//for (auto num : nums)
//	//{
//	//	cout << num << endl; 
//	//}
//}