#pragma once
#include <string>
#include<vector> 
#include <cassert>

#include<iostream> 

#include<queue> //for BFS

#include<set> //one way of checking for unique edges (needed for checking completeness)

#include<algorithm> //for std::set_intersection -> used for `isSubGraphOf`
#include <unordered_set>
#include <map>
#include <random>
#include <unordered_map>

using namespace std; 



/*a simple graph class whose vertices are identified by INTEGER values (no strings like city names) */
class UnweightedGraph
{
public: 

	vector<int> vertices{};// = { 1, 2, 3, 4 }; 

	vector<pair<int, int>> edges; /*= {
		{1, 2}, {1, 3}, {1, 4},
		{2, 3}, {2, 4},
				{3, 4}
	};*/

	/*assumes an UNDIRECTED graph*/
	bool areAdjacentEdges(int vertex1, int vertex2)
	{
		if (std::find(vertices.begin(), vertices.end(), vertex1) == vertices.end())
		{
			cout << "The vertex " << vertex1 << " is not in the graph...\n";
			return false; 
		}

		if (std::find(vertices.begin(), vertices.end(), vertex2) == vertices.end())
		{
			cout << "The vertex " << vertex2 << " is not in the graph...\n";
			return false;
		}

		//loop through edges vector of pairs 
		for (auto& aPairOfVertices : edges)
		{
			if (aPairOfVertices.first == vertex1 && aPairOfVertices.second == vertex2)
			{
				return true;
			}
			//since graph is UNDIRECTED, {2, 1} is same as {1, 2}
			else if (aPairOfVertices.first == vertex2 && aPairOfVertices.second == vertex1)
			{
				return true;
			}
		}

		return false; 
	}

	/*Note that mathematicians call this the ORDER of the graph*/
	int getNumberOfVertices()
	{
		return vertices.size(); 
	}

	/*Size is the number of EDGES in the graph*/
	int getGraphSize()
	{
		return edges.size(); 
	}

	vector<int> getNeighborsOfVertex(int vertexOfInterest)
	{
		if (std::find(vertices.begin(), vertices.end(), vertexOfInterest) == vertices.end())
		{
			cout << "The vertex " << vertexOfInterest << " is not in the graph...\n";
			return vector<int>{}; //early return of empty vector
		}

		vector<int> theNeighbors; 

		for (auto& aPairOfVertices : edges)
		{
			if (aPairOfVertices.first == vertexOfInterest)
			{
				theNeighbors.push_back(aPairOfVertices.second);
			}

			//again, using undirected graph, so allow for switched order:
			//(ex: {2, 1} means vertex 2 has 1 as its neighbor and 
			//{1, 2} also means that vertex 2 has 1 as its neighbor)
			else if (aPairOfVertices.second == vertexOfInterest)
			{
				theNeighbors.push_back(aPairOfVertices.first);
			}
		}

		if (theNeighbors.size() == 0)
		{
			cout << vertexOfInterest << " has ZERO neighbors... lonely times.\n";
		}
		return theNeighbors;
	}

	void addVertex(int vertexToAdd)
	{
		if (std::find(vertices.begin(), vertices.end(), vertexToAdd) == vertices.end())
		{
			vertices.push_back(vertexToAdd);
		}

		else
		{
			cout << "The vertex " << vertexToAdd << " is already present in the graph.\n";
		}
	}

	/*mathematicians define an empty graph as one that has ZERO edges*/
	bool isEmptyGraph()
	{
		if (edges.size() == 0)
		{
			return true; 
		}

		return false; 
	}

	/*sets vertices to the empty set - also sets edges to the empty set (of pairs) */
	void clearGraph()
	{
		vertices = {}; 
		edges = {};
	}

	/*It can be proved that a graph with `n` vertices has `n(n-1)/2` (unique) edges */
	bool isCompleteGraph()
	{
		/*add all edges (a vector of pairs) to std::set to ensure no duplicates */
		std::set<pair<int, int>> setOfEdges; 
		for (auto& theEdge : edges)
		{
			//making an ORDERED edge ensures that, ex: ({2, 3} and {3, 2} 
			//are not BOTH present 
			pair<int, int> orderedEdge; 
			if (theEdge.first < theEdge.second)
			{
				orderedEdge = theEdge; 
			}

			else
			{
				orderedEdge = make_pair(theEdge.second, theEdge.first); 
			}

			setOfEdges.insert(orderedEdge);
		}

		int n = vertices.size(); 

		if (setOfEdges.size() == ((n * (n - 1)) / 2))
		{
			return true; 
		}

		else { return false; }


	}

#pragma region Abandoned (for now) method for determining if two graphs are complementary
	///*Two graphs G1 and G2 are "complementary" ON a particular set of vertices 
	//if all adjacent vertices in G1 are NOT adjacent in G2 */
	//bool isComplementaryGraph(SimpleGraph gOther)
	//{
	//	if (this->vertices.size() != gOther.vertices.size())
	//	{
	//		cout << "The two graphs do not have the same number of vertices\n";
	//		return false;//I suppose ... 
	//	}

	//	//An approach that works only in a very particular case (more of a note to myself): 
	//	//if (this->isCompleteGraph() && gOther.isEmptyGraph())
	//	//{
	//	//	return true; 
	//	//}
	//	for (auto& theEdge : gOther.edges)
	//	{
	//		if (gOther.areAdjacentEdges(theEdge.first, theEdge.second)
	//			&&
	//			this->areAdjacentEdges(theEdge.first, theEdge.second))
	//		{
	//			return false;
	//		}
	//	}

	//	return true; 
	//}

#pragma endregion

	bool isTrivialGraph()
	{
		return (this->vertices.size() == 1 && this->edges.size() == 0);
	}

	bool isNullGraph()
	{
		return (this->vertices.size() == 0 && this->edges.size() == 0);
	}

	bool areAdjacentEdges(pair<int, int> firstEdge, pair<int, int> secondEdge)
	{
		if (std::find(edges.begin(), edges.end(), firstEdge) == edges.end())
		{
			//Note that this "existence check" is imperfect 
			// - does not account for {2, 1} -> {1, 2} type problem 
			cout << "The first edge supplied is not in the graph\n";
			return false; 
		}

		if (std::find(edges.begin(), edges.end(), secondEdge) == edges.end())
		{
			cout << "The second edge supplied is not in the graph\n";
			return false;
		}

		int edge1Vertex1 = firstEdge.first; 
		int edge1Vertex2 = firstEdge.second; 
		int edge2Vertex1 = secondEdge.first; 
		int edge2Vertex2 = secondEdge.second; 

		if (edge1Vertex1 == edge2Vertex1 || edge1Vertex1 == edge2Vertex2
			||
			edge1Vertex2 == edge2Vertex2 || edge1Vertex2 == edge2Vertex1)
		{
			return true; 
		}
		else { return false; }
	}

#pragma region isSubGraphOf method
	/*example: g1.isSubGraphOf(g2) == true for
	g1 = {{1, 2}, {{1, 2}}
	g2 = {{1, 2, 3}, {{1, 2}, {2, 3}}
	(vertices of g1 are a subset of g2's vertices AND
	edges of g1 are a subset of g2's edges) 
	*/
	//bool isSubGraphOf(SimpleGraph otherGraph)
	//{
	//	if (this->edges.size() > otherGraph.edges.size()
	//		||
	//		this->vertices.size() > otherGraph.vertices.size()
	//		)
	//	{
	//		cout << "\"this\" graph has greater size than the graph given as an argument\n";
	//		return false;
	//	}

	//	vector<int> verticesIntersection; 

	//	std::set_intersection(this->vertices.begin(), this->vertices.end(),
	//		otherGraph.vertices.begin(), otherGraph.vertices.end(),
	//		std::back_inserter(verticesIntersection));

	//	//std::set_intersection does not work in "straightforward" way for vector<pair> (edges)
	//	bool isAtLeastOneCommonEdge = false; 
	//	for (auto& theEdge : this->edges)
	//	{
	//		if (std::find(otherGraph.edges.begin(), otherGraph.edges.end(), theEdge)
	//			!= otherGraph.edges.end())
	//		{
	//			isAtLeastOneCommonEdge = true;
	//		}
	//	}
	//	//subset if interesection is not the null set 
	//	if (verticesIntersection.size() > 0
	//		&&
	//		isAtLeastOneCommonEdge)
	//	{
	//		return true;
	//	}

	//	else { return false; }
	//}

#pragma endregion  - abandoned for now 

	bool operator == (UnweightedGraph otherGraph)
	{
		return (this->edges == otherGraph.edges
			&&
			this->vertices == otherGraph.vertices);

	}

	/*Note that there is no "root" - since graphs (not trees)*/
	void scanBreadth_givenStartingVertex(int startingVertex)
	{
		int numberOfVerticesVisited = 0; 
		//make sure startingVertex is in vertices: 
		if (std::find(vertices.begin(), vertices.end(), startingVertex)
			== vertices.end())
		{
			cout << startingVertex << " is not in the list of vertices\n";
			return; 
		}

		std::queue<int> theScanQ;

		theScanQ.push(startingVertex);

		unordered_set<int> alreadyVisitedSet; 

		while (!theScanQ.empty())
		{
			int currentVertex = theScanQ.front(); 

			if (alreadyVisitedSet.find(currentVertex) == alreadyVisitedSet.end())
			{
				alreadyVisitedSet.insert(currentVertex);
				numberOfVerticesVisited++; 
			}

			//enqueue the neighbors of `currentVertex`
			vector<int> neighborsOfCurrentVertex = this->getNeighborsOfVertex(currentVertex);

			for (auto& theNeighbor : neighborsOfCurrentVertex)
			{
				//note that the `find` function is a MEMBER of std::set class
				if (alreadyVisitedSet.find(theNeighbor) == alreadyVisitedSet.end())
				{
					//if not already visited, add to queue: 
					theScanQ.push(theNeighbor);
					alreadyVisitedSet.insert(theNeighbor); //use of set prevents duplicates (waste of space using vector)
					numberOfVerticesVisited++;
				}

			}
			cout << currentVertex << " "; 
			//the operation of interest (add weight/visit/print vertex) 
			theScanQ.pop(); 
		}
		cout << "\n\n";
		if (numberOfVerticesVisited != vertices.size())
		{
			cout << "At least one vertex in the graph was NOT visited \n";
			cout << "This suggests something about the \"connectedness\" of the start vertex = " << startingVertex << "\n";
		}

	}

	/*Does NOT take a starting vertex (as an arg) 
	Runs through the vector of vertices and calls scanBreadth for each
	*/
	void fullBreadthFirstScan()
	{
		for (auto& theVertex : vertices)
		{
			cout << "Starting at vertex = " << theVertex
				<< "-BFS visits vertices in the following order: \n";
			scanBreadth_givenStartingVertex(theVertex); 
		}
	}



};

struct WeightedEdge
{
	string vertex1; 
	string vertex2; 
	int weight; 
};

class WeightedUndirectedGraph
{
public:
	vector<string> vertices{};// = { 1, 2, 3, 4 }; 

	/*Weighted edge is a struct of three ints - similar to a tuple
	(rather than the std::pair I used for the `SimpleGraph` class above*/
	vector<WeightedEdge> edges;


	/*NOTE: this function DOES "handle" loops
	* - ex: if vertex A has an edge to itself, A will be returned
	* as one of the neighbors of A
	*/
	vector<string> getNeighborsOfVertex(string vertexOfInterest)
	{
		if (std::find(vertices.begin(), vertices.end(), vertexOfInterest) == vertices.end())
		{
			cout << "The vertex " << vertexOfInterest << " is not in the graph...\n";
			return vector<string>{}; //early return of empty vector
		}

		vector<string> theNeighbors;

		for (auto& aPairOfVertices : edges)
		{
			if (aPairOfVertices.vertex1 == vertexOfInterest)
			{
				theNeighbors.push_back(aPairOfVertices.vertex2);
			}

			//again, using undirected graph, so allow for switched order:
			//(ex: {2, 1} means vertex 2 has 1 as its neighbor and 
			//{1, 2} also means that vertex 2 has 1 as its neighbor)
			else if (aPairOfVertices.vertex2 == vertexOfInterest)
			{
				theNeighbors.push_back(aPairOfVertices.vertex1);
			}


		}

		if (theNeighbors.size() == 0)
		{
			cout << vertexOfInterest << " has ZERO neighbors... lonely times.\n";
		}
		return theNeighbors;
	}

	/*Note that there is no "root" - since graphs (not trees)*/
	void scanBreadth(string startingVertex)
	{
		int numberOfVerticesVisited = 0;

		int totalWeight = 0;

		//make sure startingVertex is in vertices: 
		if (std::find(vertices.begin(), vertices.end(), startingVertex)
			== vertices.end())
		{
			cout << startingVertex << " is not in the list of vertices\n";
			return;
		}

		std::queue<string> theScanQ;

		theScanQ.push(startingVertex);

		unordered_set<string> alreadyVisitedSet;

		while (!theScanQ.empty())
		{
			string currentVertex = theScanQ.front();

			if (alreadyVisitedSet.find(currentVertex) == alreadyVisitedSet.end())
			{
				alreadyVisitedSet.insert(currentVertex);
				numberOfVerticesVisited++;

			}

			//enqueue the neighbors of `currentVertex`
			vector<string> neighborsOfCurrentVertex = this->getNeighborsOfVertex(currentVertex);

			for (auto& theNeighbor : neighborsOfCurrentVertex)
			{
				//note that the `find` function is a MEMBER of std::set class
				if (alreadyVisitedSet.find(theNeighbor) == alreadyVisitedSet.end())
				{
					//if not already visited, add to queue: 
					theScanQ.push(theNeighbor);
					alreadyVisitedSet.insert(theNeighbor); //use of set prevents duplicates (waste of space using vector)
					numberOfVerticesVisited++;
				}

			}
			cout << currentVertex << " ";
			//the operation of interest (add weight/visit/print vertex) 
			theScanQ.pop();
		}
		cout << "\n\n";
		if (numberOfVerticesVisited != vertices.size())
		{
			cout << "At least one vertex in the graph was NOT visited \n";
			cout << "This suggests something about the \"connectedness\" of the start vertex = " << startingVertex << "\n";
		}

	}


	int findEdgeWeight(string startingVertex, string endingVertex)
	{
		bool edgeFound = false;
		for (auto& theEdge : edges)
		{
			if ((theEdge.vertex1 == startingVertex && theEdge.vertex2 == endingVertex)

				||

				(theEdge.vertex2 == startingVertex && theEdge.vertex1 == endingVertex)
				)
			{
				edgeFound = true;
				return theEdge.weight;
			}
		}

		if (edgeFound == false)
		{
			cout << "No edge found between vertices " << startingVertex << " and " << endingVertex << "\n";
			return -1;
		}
	}

	/*given a startingVertex, this looks at edges where vertex1 = starting vertex and
	randomly picks a vertex2
	->this continues until vertex1 = endingVertex
	NOTE that if graph of interest is not "sufficiently connected", this random walk may lead to an infinite loop
	@return the totalPathWeight
	*/
	int takeRandomWalk_UntilSomeEnd(string startingVertex, string endingVertex)
	{
		string currentVertex = startingVertex;

		int totalPathWeight = 0;

		//hold onto the path taken with string concatenation: 
		string pathTaken = startingVertex;

		while (currentVertex != endingVertex)
		{
			auto neighbors = getNeighborsOfVertex(currentVertex);

			//pick random neighbor to go to
			random_device rd;
			mt19937 gen(rd());
			uniform_int_distribution<> distribution(0, neighbors.size() - 1);
			//stores random integers with range neighbors[0 -> lastNeighborIndex] in ``distribution` variable 

			//cout << distribution(gen) << "\n"; 
			string randomlyChosenNeighbor = neighbors[distribution(gen)];

			int weightToRandomlyChosenNeighbor = findEdgeWeight(currentVertex, randomlyChosenNeighbor);

			totalPathWeight += weightToRandomlyChosenNeighbor;
			currentVertex = randomlyChosenNeighbor;

			pathTaken += " " + currentVertex;

			cout << "Moving along weight w = " << weightToRandomlyChosenNeighbor <<
				" to neighbor " << currentVertex << "\n";

		}

		cout << "Path taken: " << pathTaken << "\n"; //this string COULD be returned in an overloaded version 
		//of this function 
		cout << "Total weight (distance) traveled: " << totalPathWeight << "\n";

		return totalPathWeight;
	}

	/*
	This is a BFS algorithm (see `UnWeightedGraph`) with two additions: 
	1) A boolean is used to verify whether or not ANY path from start to end is found (may not be if "weakly-connected")
	
	2) An std::unordered_map of successor vertices to predecessor vertices is used to keep track of the path taken (a bit tricky) 
	@return the total weight of the path
	*/
	int traverseShortestPath_assumingEqualWeightPaths(string startingVertex, string endingVertex)
	{
		queue<string> traversalQ;
		traversalQ.push(startingVertex); 

		vector<string> path; 

		set<string> alreadyVisited = { startingVertex }; 

		bool pathFound = false; 

		unordered_map<string, string> successorToPredecessorMap; 
		//ex: if we take an edge from vertex "A" to "B"
		//successorToPredecessorMap["B"] = "A"


		while (!traversalQ.empty() && pathFound == false)
		{
			string currentVertex = traversalQ.front(); 
			traversalQ.pop();

			vector<string> neighbors = getNeighborsOfVertex(currentVertex); 

			for (auto& theNeighbor : neighbors)
			{
				if (alreadyVisited.find(theNeighbor) == alreadyVisited.end())

				{
					traversalQ.push(theNeighbor);
					alreadyVisited.insert(theNeighbor);

					successorToPredecessorMap[theNeighbor] = currentVertex;  //read: predecessor of theNeighbor is currentVertex 
																//ex: B and A in the JPG image file 

					if (theNeighbor == endingVertex)
					{
						pathFound = true;
						break;
					}
				}
			}
		}

		if (pathFound)
		{
			for (string at = endingVertex; at != startingVertex; at = successorToPredecessorMap[at]) //note the string-based loop
			{
				path.push_back(at); 
			}

			path.push_back(startingVertex); 

			std::reverse(path.begin(), path.end());

		}

		for (auto& element : path)
		{
			cout << element << " ...";
		}

		cout << "\n\n";
		return path.size() - 1; //no accounting for weights here 
							//this will only find ONE POSSIBLE shortest path
	}


	void findDijkstraShortestPath(string startVertex, string targetVertex)
	{
		priority_queue < pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> minHeap;
					//the edge (pair of verts) //the "underlying container"  //the custom comparator 
		
		unordered_map<string, int> distanceMap; 
		unordered_map<string, string> predecessorMap; 
		unordered_set<string> visited; 


		for (string theVertex : vertices)
		{
			distanceMap[theVertex] = numeric_limits<int>::max(); 		//init distances to "inf"
			predecessorMap[theVertex] = "-1"; //assume that -1 will NEVER be the name of a vertex
		}

		distanceMap[startVertex] = 0; 

		minHeap.push({ 0, startVertex });

		while (!minHeap.empty())
		{
			string currentVertex = minHeap.top().second; 

			minHeap.pop();

			if (visited.find(currentVertex) != visited.end())
			{
				continue; //!
			}
			visited.insert(currentVertex); 

			if (currentVertex == targetVertex)
			{
				break; //!
			}

			for (auto& theNeighbor : getNeighborsOfVertex(currentVertex))
			{
				string neighborVertex = theNeighbor;  //just sticking with GitHub copilot's approach here
				int weight = findEdgeWeight(currentVertex, neighborVertex); 

				if (distanceMap[currentVertex] + weight < distanceMap[neighborVertex])
				{
					distanceMap[neighborVertex] = distanceMap[currentVertex] + weight; 
					predecessorMap[neighborVertex] = currentVertex; 
					minHeap.push({ distanceMap[neighborVertex], neighborVertex });
				}

			}
		}

		cout << "Starting at vertex " << startVertex << ", the following is a map of shortest distances to given vertices: \n";
		for (auto& pair : distanceMap)
		{
			cout << pair.first << "\t" << pair.second << endl; 
		}

		cout << "ONE POSSIBLE path of minimal distance/weight for those vertices are : \n";

		for (auto& theVertex : vertices)
		{
			cout << "\n";
			printAMinimalDistancePath(startVertex, theVertex, predecessorMap);
		}
		
	}

	/*Called by the Dijkstra method (a member of WeightedUndirectedGraph) - does NONE of the "main work" of the algo*/
	void printAMinimalDistancePath(string startVertex, string targetVertex, unordered_map<string, string> predecessorMap)
	{
		string currentKey = targetVertex;

		string visitedVertices = targetVertex;
		while(currentKey != startVertex)
		{
			visitedVertices +=  ">-" + predecessorMap[currentKey]; //goofy >- because reverse will be used 

			currentKey = predecessorMap[currentKey]; 

		}

		std::reverse(visitedVertices.begin(), visitedVertices.end());

		cout << visitedVertices << endl; 
	}

	/*Does NOT take a starting vertex (as an arg)
	Runs through the vector of vertices and calls scanBreadth for each
	*/
	//void fullBreadthFirstScan()
	//{
	//	for (auto& theVertex : vertices)
	//	{
	//		cout << "Starting at vertex = " << theVertex
	//			<< "-BFS visits vertices in the following order: \n";
	//		scanBreadth_givenStartingVertex(theVertex);
	//	}
	//}



};




