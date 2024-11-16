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
#include <random> //for random walkin'
#include <unordered_map>

#include<iomanip> //for drawing GridGraph

#include<thread> 
#include<chrono> //thread and chrono for platform-independent pausing while taking random walk and displaying updated grid


#include"C:/Users/Work/Desktop/myCppLibrary/algos/swapShuffleReverseAndPermutations.h"

using namespace std; 



/*a simple graph class whose vertices are identified by INTEGER values (no strings like city names) */
class UnweightedGraph
{
public: 

	vector<int> vertices{};// = { 1, 2, 3, 4 }; 



	vector<pair<int, int>> edges; 
	// ex= {
//	{1, 2}, {1, 3}, {1, 4},
//	{2, 3}, {2, 4},
//			{3, 4}
//};*/



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

/*a pair of integers - x and y*/
struct PairOfIntegers_Vertex
{
	int x; 
	int y; 
	
	PairOfIntegers_Vertex(int x, int y)
		:x(x), y(y) {}; 

	friend ostream& operator << (ostream& os, const PairOfIntegers_Vertex& pair);

	bool operator == (const PairOfIntegers_Vertex& other)
	{
		return this->x == other.x && this->y == other.y;
	}

	bool isSameVertex(const PairOfIntegers_Vertex& other)
	{
		return this->x == other.x && this->y == other.y; 
	}

};

ostream& operator << (ostream& os, const PairOfIntegers_Vertex& pair)
{
	os << "(" << pair.x << " , " << pair.y << ")";

	return os;
}

struct GridEdge
{
	PairOfIntegers_Vertex firstVertex;
	PairOfIntegers_Vertex secondVertex;

	GridEdge(PairOfIntegers_Vertex firstVertex, PairOfIntegers_Vertex secondVertex)
		:firstVertex(firstVertex), secondVertex(secondVertex) {};

};

/*This is a SQUARE grid graph - and it is 2D*/
class GridGraph
{
public:

	vector<PairOfIntegers_Vertex> vertices;  //tuple or 3Dpointstruct  if desired 

	vector<GridEdge> gridEdges; //not vector

	/*@param dimensionOfSquareGrid - returns a grid graph (AKA: "lattice graph") of `d^2` vertices
	and 2d^2 - 2d edges (see https://mathworld.wolfram.com/GridGraph.html)
	ex: if user supplies an argument of 2, the following graph is made:
	vertices =
	{
		{2, 1}, {2, 2}
		{1, 1}, {1, 2}
	}

	edges =
	{
		{{1, 2}, {2, 2}},   //edge connecting (1, 2) to (2, 2)
		{{2, 2}, {2, 1}},
		{{2, 1}, {1, 1}},
		{{1, 1}, {1, 2}}
	}
	*/
	GridGraph(int dimensionOfSquareGrid)
	{
		//vertices first
		for (int x = 1; x <= dimensionOfSquareGrid; x++)
		{
			for (int y = 1; y <= dimensionOfSquareGrid; y++)
			{
				vertices.push_back({ x, y });
			}
		}

		//edges (pair of two pairs of integers) next: 

		//horizontal edges first: 
		for (int y = 1; y <= dimensionOfSquareGrid; y++)
		{
			for (int x = 1; x < dimensionOfSquareGrid; x++)
			{
				PairOfIntegers_Vertex firstVertex(x, y);
				PairOfIntegers_Vertex secondVertex(x + 1, y);
				GridEdge theGridEdge(firstVertex, secondVertex);

				gridEdges.push_back(theGridEdge);
			}

		}


		//now vertical edges:
		for (int x = 1; x <= dimensionOfSquareGrid; x++)
		{
			for (int y = 1; y < dimensionOfSquareGrid; y++)
			{
				PairOfIntegers_Vertex firstVertex(x, y);
				PairOfIntegers_Vertex secondVertex(x, y + 1);

				GridEdge theGridEdge(firstVertex, secondVertex);

				gridEdges.push_back(theGridEdge);
			}
		}
	}

	vector<PairOfIntegers_Vertex> getNeighborsOfVertex(PairOfIntegers_Vertex vertexOfInterest)
	{
		if (std::find(vertices.begin(), vertices.end(), vertexOfInterest) == vertices.end())
		{
			cout << "The vertex " << vertexOfInterest << " is not present in the graph.\n";
			return vector<PairOfIntegers_Vertex>(); //empty vertex of pairs

		}
		vector<PairOfIntegers_Vertex> neighbors;
		//max possible neighbor count: 4 (ex: (2, 2) has (1, 2), (2, 3), (3, 2) and (2, 1)  

		//loop through edges: 
		for (auto& theVertex : vertices)
		{
			//four scenarios on a 2 x 2 grid make a neighbor: 

			//first - same x value, y is shifted down 1 unit 
			if (theVertex.x == vertexOfInterest.x && theVertex.y - 1 == vertexOfInterest.y)
			{
				neighbors.push_back(theVertex);
			}

			//second - same x, y + 1
			if (theVertex.x == vertexOfInterest.x && theVertex.y + 1 == vertexOfInterest.y)
			{
				neighbors.push_back(theVertex);
			}

			//third: x leftshifted 1 unit, same y 
			if (theVertex.x - 1 == vertexOfInterest.x && theVertex.y == vertexOfInterest.y)
			{
				neighbors.push_back(theVertex);
			}

			//fourth x shifted right 1 unit, same y
			if (theVertex.x + 1 == vertexOfInterest.x && theVertex.y == vertexOfInterest.y)
			{
				neighbors.push_back(theVertex);
			}

		}
		return neighbors;
	}

	void takeRandomWalk(PairOfIntegers_Vertex startVertex, PairOfIntegers_Vertex endVertex)
	{

		if (std::find(vertices.begin(), vertices.end(), startVertex) == vertices.end())
		{
			cout << "starting vertex = " << startVertex << " is not present in the graph.\n";
			return;
		}

		if (std::find(vertices.begin(), vertices.end(), endVertex) == vertices.end())
		{
			cout << "ending vertex = " << endVertex << " is not present in the graph.\n";
			return;
		}

		PairOfIntegers_Vertex currentVertex = startVertex;

		random_device rd;
		std::mt19937 gen(rd());

		auto gridDrawing = getInitialGridDrawing();

		int stepCountForCharacters = 0;
		size_t totalStepCount = 0;
		while (!currentVertex.isSameVertex(endVertex))
		{
			auto neighbors = getNeighborsOfVertex(currentVertex);

			uniform_int_distribution<int> distribution(0, neighbors.size() - 1);

			int randomNeighborIndex = distribution(gen);

			PairOfIntegers_Vertex randomlyChosenNeighbor = neighbors[randomNeighborIndex];

			totalStepCount++;
			//cout << "\nStep " << totalStepCount << " - moving to vertex = " << randomlyChosenNeighbor << "\n";
			currentVertex = randomlyChosenNeighbor;

			stepCountForCharacters++;
			if (stepCountForCharacters > 26)
			{
				stepCountForCharacters = 1;
			}

			char characterOfCurrentPosition = (64 + stepCountForCharacters); //wrap back around to A once 90 is hit 

			gridDrawing[currentVertex.x - 1][currentVertex.y - 1] = characterOfCurrentPosition;

			this_thread::sleep_for(chrono::milliseconds(50)); //Change to 50 for a good time ...
			system("cls");
			drawGrid(gridDrawing);

			if (currentVertex.isSameVertex(endVertex))
			{
				cout << "Reached target in " << totalStepCount << " steps.\n";
				drawGrid(gridDrawing);
			}
		}
	}

	vector<PairOfIntegers_Vertex> generateAllowedKnightMoves(PairOfIntegers_Vertex startVertex)
	{
		vector<PairOfIntegers_Vertex> all8Moves;

		PairOfIntegers_Vertex firstMove = { startVertex.x + 2, startVertex.y + 1 }; //right 2 spaces, up 1
		PairOfIntegers_Vertex secondMove = { startVertex.x + 1, startVertex.y + 2 }; //right 1 spaces, up 2
		PairOfIntegers_Vertex thirdMove = { startVertex.x - 2, startVertex.y - 1 }; //left 2, down 1
		PairOfIntegers_Vertex fourthMove = { startVertex.x - 1, startVertex.y - 2 }; //left 1, down 2

		PairOfIntegers_Vertex fifthMove = { startVertex.x + 2, startVertex.y - 1 }; //etc.
		PairOfIntegers_Vertex sixthMove = { startVertex.x + 1, startVertex.y - 2 };
		PairOfIntegers_Vertex seventhMove = { startVertex.x - 2, startVertex.y + 1 };
		PairOfIntegers_Vertex eighthMove = { startVertex.x - 1, startVertex.y + 2 };

		all8Moves.push_back(firstMove);
		all8Moves.push_back(secondMove);
		all8Moves.push_back(thirdMove);
		all8Moves.push_back(fourthMove);

		all8Moves.push_back(fifthMove);
		all8Moves.push_back(sixthMove);
		all8Moves.push_back(seventhMove);
		all8Moves.push_back(eighthMove);

		vector<PairOfIntegers_Vertex> theAllowedMoves;

		int dimensionOfSquareGrid = (int)sqrt(vertices.size());

		for (auto& theMove : all8Moves)
		{
			if (theMove.x > 0 && theMove.x <= dimensionOfSquareGrid
				&&
				theMove.y > 0 && theMove.y <= dimensionOfSquareGrid)
			{
				theAllowedMoves.push_back(theMove);
			}
		}

		return theAllowedMoves;
	}


	vector<PairOfIntegers_Vertex> generateAllowedTOURMoves(PairOfIntegers_Vertex startVertex,
		vector< PairOfIntegers_Vertex>& alreadyVisited)
	{
		auto allowedBaseMoves = generateAllowedKnightMoves(startVertex);

		vector<PairOfIntegers_Vertex> allowedTOURmoves;

		for (auto& theMove : allowedBaseMoves)
		{
			if (std::find(alreadyVisited.begin(), alreadyVisited.end(), theMove) == alreadyVisited.end())
			{
				allowedTOURmoves.push_back(theMove);
			}
		}

		return allowedTOURmoves;

	}

	/*allows revisiting*/
	void takeRandomKnightWalk(PairOfIntegers_Vertex startVertex, PairOfIntegers_Vertex endVertex)
	{
		if (std::find(vertices.begin(), vertices.end(), startVertex) == vertices.end())
		{
			cout << "starting vertex = " << startVertex << " is not present in the graph.\n";
			return;
		}

		if (std::find(vertices.begin(), vertices.end(), endVertex) == vertices.end())
		{
			cout << "ending vertex = " << endVertex << " is not present in the graph.\n";
			return;
		}

		PairOfIntegers_Vertex currentVertex = startVertex;

		random_device rd;
		std::mt19937 gen(rd());

		auto gridDrawing = getInitialGridDrawing();

		int stepCountForCharacters = 0;
		size_t totalStepCount = 0;
		while (!currentVertex.isSameVertex(endVertex))
		{
			auto neighbors = generateAllowedKnightMoves(currentVertex);

			uniform_int_distribution<int> distribution(0, neighbors.size() - 1);


			int randomNeighborIndex = distribution(gen);

			PairOfIntegers_Vertex randomlyChosenNeighbor = neighbors[randomNeighborIndex];

			totalStepCount++;
			//cout << "\nStep " << totalStepCount << " - moving to vertex = " << randomlyChosenNeighbor << "\n";
			currentVertex = randomlyChosenNeighbor;

			stepCountForCharacters++;
			if (stepCountForCharacters > 26)
			{
				stepCountForCharacters = 1;
			}

			char characterOfCurrentPosition = (64 + stepCountForCharacters); //wrap back around to A once 90 is hit 

			gridDrawing[currentVertex.x - 1][currentVertex.y - 1] = characterOfCurrentPosition;

			this_thread::sleep_for(chrono::milliseconds(10)); //Change to 50 for a good time ...
			system("cls");
			drawGrid(gridDrawing);

			if (currentVertex.isSameVertex(endVertex))
			{
				cout << "Reached target in " << totalStepCount << " steps.\n";
				drawGrid(gridDrawing);
			}

		}
	}

	/*does NOT allow revisiting
	returns true if tour was successful
	*/
	bool attemptKnightsTour(PairOfIntegers_Vertex startVertex)
	{
		vector<PairOfIntegers_Vertex> visitedVertices;

		PairOfIntegers_Vertex currentVertex = startVertex;
		visitedVertices.push_back(currentVertex);

		random_device rd;
		std::mt19937 gen(rd());

		auto gridDrawing = getInitialGridDrawing();

		int stepCountForCharacters = 0;
		size_t totalStepCount = 0;

		while (visitedVertices.size() < vertices.size())
		{
			//vector<PairOfIntegers_Vertex> allowedMoves = generateAllowedKnightMoves(currentVertex);

			auto allowedMoves = generateAllowedTOURMoves(currentVertex, visitedVertices);

			//don't revisit previously-visited position
			//for (auto& theVertex : allowedMoves)
			//{
			//	auto locOfTheVertex = std::find(visitedVertices.begin(), visitedVertices.end(), theVertex);

			//	if (locOfTheVertex != visitedVertices.end()) 
			//	{
			//		//allowedMoves.erase(locOfTheVertex);
			//		std::erase(allowedMoves, theVertex); 
			//	}
			//}

			if (allowedMoves.size() == 0)
			{
				//cout << "Dead end, dead end, dead end!\n";
				//backtrack how?

				return false;
			}


			uniform_int_distribution<int> distribution(0, allowedMoves.size() - 1);
			//NOTE: if second arg to `distribution` == 0 - 1 (ZERO allowed moves) 
			//uniform_int_distribution will kill program without the `if` above

			int randomNeighborIndex = distribution(gen);

			PairOfIntegers_Vertex randomlyChosenNeighbor = allowedMoves[randomNeighborIndex];

			totalStepCount++;
			//cout << "\nStep " << totalStepCount << " - moving to vertex = " << randomlyChosenNeighbor << "\n";
			currentVertex = randomlyChosenNeighbor;

			visitedVertices.push_back(currentVertex);

			stepCountForCharacters++;
			if (stepCountForCharacters > 26)
			{
				stepCountForCharacters = 1;
			}

			char characterOfCurrentPosition = (64 + stepCountForCharacters); //wrap back around to A once 90 is hit 

			gridDrawing[currentVertex.x - 1][currentVertex.y - 1] = characterOfCurrentPosition;

			//this_thread::sleep_for(chrono::milliseconds(1000)); //Change to 50 for a good time ...
			//system("cls");
			//drawGrid(gridDrawing);

			if (visitedVertices.size() == vertices.size())
			{
				//cout << "Visited all vertices in " << totalStepCount << " steps.\n";
				drawGrid(gridDrawing);

				return true;
			}

		}

	}

	vector<vector<char>> getInitialGridDrawing()
	{
		int squareBoxDimension = (int)sqrt(vertices.size());
		//draw top line of grid box: 

		vector<vector<char>> characterGrid;
		//char characterGrid[squareBoxDimension][squareBoxDimension];
		for (int y = squareBoxDimension; y > 0; y--)
		{
			vector<char> currentRow;
			for (int x = 1; x <= squareBoxDimension; x++)
			{
				currentRow.push_back(' ');
			}
			characterGrid.push_back(currentRow);
		}

		return characterGrid;
	}



	/*abandoned for now*/
	bool takeKnightsTour_WithBackTracking(PairOfIntegers_Vertex currentVertex, vector<PairOfIntegers_Vertex>& visitedVertices)
	{
		return false;
	}




	void drawGrid(vector<vector<char>> characterGrid)
	{
		int squareBoxDimension = characterGrid.at(0).size();

		cout << " " << setw(squareBoxDimension + 1) << setfill('=') << "\n";
		for (auto& row : characterGrid)
		{
			cout << "|";
			for (auto& character : row)
			{
				cout << character;
			}
			cout << "|\n";
		}
		cout << " " << setw(squareBoxDimension + 1) << setfill('=') << "\n";
		cout << "\n";
	}

};




struct WeightedEdge
{
	string vertex1; 
	string vertex2; 
	int weight; 

	bool operator == (const WeightedEdge& otherWeightedEdge)
	{
		return
			(this->vertex1 == otherWeightedEdge.vertex1
				&&
				this->vertex2 == otherWeightedEdge.vertex2
				&&
				this->weight == otherWeightedEdge.weight);

	}
};



class WeightedUndirectedGraph
{
public:
	vector<string> vertices{};

	/*Weighted edge is a struct of two strings and an int - similar to a tuple
	(rather than the std::pair I used for the `SimpleGraph` class above*/
	vector<WeightedEdge> edges;


	/*
	@param squareGridDimension - 
	this constructor will return a square grid of points of a graph with all edge weights = 1
	EX: if the arg. = 2
	vertices = {1, 2}
	edges = {
		{1, 2}
	}
	*/


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

	/*finds shortest path from start to target AND certain other vertices in graph
	(dependent on the depth of these vertices relative to `targetVertex`)*/
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

	private:

	/*Called by the Dijkstra method (a member of WeightedUndirectedGraph) - does NONE of the "main work" of the algo*/
	void printAMinimalDistancePath(string startVertex, string targetVertex, unordered_map<string, string> predecessorMap)
	{
		string currentKey = targetVertex;

		string visitedVertices = targetVertex;
		while (currentKey != startVertex)
		{
			visitedVertices += ">-" + predecessorMap[currentKey]; //goofy >- because reverse will be used 

			currentKey = predecessorMap[currentKey];

		}

		std::reverse(visitedVertices.begin(), visitedVertices.end()); 
		//NOTE that this will print city names in reverse ... :)

		cout << visitedVertices << endl;
	}

	public: 
	/*Does NOT take a starting vertex (as an arg)
	Runs through the vector of vertices and calls scanBreadth for each
	*/
	void fullBreadthFirstScan()
	{
		for (auto& theVertex : vertices)
		{
			cout << "Starting at vertex = " << theVertex
				<< "-BFS visits vertices in the following order: \n";
			scanBreadth(theVertex);
		}
	}

	void removeVertex_andAnyAssociatedEdges(string vertexToRemove)
	{
		//simple bit: 
		auto locationOfVertexToRemove = std::find(vertices.begin(), vertices.end(), vertexToRemove);
		if (locationOfVertexToRemove != vertices.end())
		{
			vertices.erase(locationOfVertexToRemove);
			//cout << "Updated number of vertices: " << vertices.size() << "\n";

			//now erase all edges incident on the vertex (more of a chore than I thought ...) 
			auto edgeIterator = edges.begin();
			int numberOfEdgesRemoved = 0;
			while (edgeIterator != edges.end()) //for loop running over size of edges will NOT work here 
				//(since erasing updates size) 
			{
				if (edgeIterator->vertex1 == vertexToRemove || edgeIterator->vertex2 == vertexToRemove)
				{
					edgeIterator = edges.erase(edgeIterator); //interesting approach here
					numberOfEdgesRemoved++;
				}

				else
				{
					++edgeIterator;
				}
			}

			cout << "Successfully removed vertex " << vertexToRemove
				<< " and its " << numberOfEdgesRemoved << " incident edges.\n";
		}

		else
		{
			cout << "The vertex " << vertexToRemove << " is not present in the graph\n";
		}



	}


	void addVertex(string vertexToAdd)
	{
		vertices.push_back(vertexToAdd);
	}

	/*This method will assume that the two supplied vertices ARE present in the graph
	If not, call `addVertex` a time or two first.
	*/
	void addEdge(string firstVertex, string secondVertex, int weight)
	{
		//confirm that both first and secondVertex are present 
		if (std::find(vertices.begin(), vertices.end(), firstVertex) == vertices.end())
		{
			cout << "The vertex " << firstVertex << " is not present - call `addVertex(" << firstVertex << ") first.\n";
			return; 
		}

		if (std::find(vertices.begin(), vertices.end(), secondVertex) ==  vertices.end())
		{
			cout << "The vertex " << secondVertex << " is not present - call `addVertex(" << secondVertex << ") first.\n";
			return; //a bit goofy for the user with two returns here
		}

		edges.push_back({ firstVertex, secondVertex, weight });

	}


	/*Not certain this has no bugs ...*/
	multimap<int, string> mapDegreesOfAllVertices()
	{
		multimap<int, string> mapOfDegreesToVertices;
		

		for (auto& theVertex : vertices)
		{
			auto neighbors = getNeighborsOfVertex(theVertex);
			int degreeCount = neighbors.size();

			mapOfDegreesToVertices.insert({ degreeCount, theVertex });
		}

		return mapOfDegreesToVertices;
	}

	/*graph is complete if every vertex is connected to every other vertex - except itself (I think)
	NOTE that this is an alternative to the "combinatorics" approach used in `UnWeightedGraph` class above*/
	bool isCompleteGraph()
	{
		auto mapOfDegreesToVertices = mapDegreesOfAllVertices(); 

		for (auto& thePair : mapOfDegreesToVertices)
		{
			if (thePair.first != vertices.size() - 1)
			{
				cout << thePair.second << " only connects to " << thePair.first << " of " << vertices.size() - 1
					<< " vertices - not a complete graph\n";
					//only doing one print statement
				return false; 
			}
		}

		return true;
	}

	/**/
	void printPath_AssumingCompleteGraph()
	{

		for (int i = 0; i < vertices.size() - 1; ++i)
		{
			cout << std::left << std::setw(20) << vertices.at(i) 
				<< std::left << std::setw(4) << "-> ";
		}
		//print final vertex without the trailing -> 
		cout << vertices.at(vertices.size() - 1) << "\n";
	}

	auto generatePossiblePaths_ForTSP(string startingVertex)
	{
		std::set<vector<string>> possiblePaths; 

		std::vector<string> verticesWithoutStartingVertex;
		for (int i = 0; i < vertices.size(); ++i)
		{
			if (vertices[i] != startingVertex)
			{
				verticesWithoutStartingVertex.push_back(vertices[i]);
			}
		}

		std::vector<string> currentPath; 

		currentPath.push_back(startingVertex); 

		for (auto& vertex : verticesWithoutStartingVertex)
		{
			currentPath.push_back(vertex); 
			//cout << std::left << std::setw(15) << vertex << "->";
		}
		currentPath.push_back(startingVertex); 
		possiblePaths.insert(currentPath); 

		currentPath.clear(); //clear!

		while (myNextPermutation(verticesWithoutStartingVertex))
		{
			currentPath.push_back(startingVertex); 

			//cout << std::left << std::setw(15) << startingVertex << "->";
			for (auto& vertex : verticesWithoutStartingVertex)
			{
				currentPath.push_back(vertex); 
			}
			currentPath.push_back(startingVertex); 

			possiblePaths.insert(currentPath); 

			currentPath.clear(); //clear!
		}

		return possiblePaths; 
	}

	/*generate all possible paths, then find the one(s) of minimum weight*/
	void bruteForceTSP_November14(string startingVertex)
	{
		//first, test myNextPermutation with all cities: 
		//int possiblePathCount = 1; 

		//printPath_AssumingCompleteGraph();
		//while (myNextPermutation(vertices))
		//{
		//	printPath_AssumingCompleteGraph(); 
		//	//cout << "\nNext permutation of cities:\n";
		//	possiblePathCount++; 
		//}
		//cout << "Total possible path count: " << possiblePathCount << "\n";

		//std::vector<string> verticesWithoutStartingVertex; 
		//for (int i = 0; i < vertices.size(); ++i)
		//{
		//	if (vertices[i] != startingVertex)
		//	{
		//		verticesWithoutStartingVertex.push_back(vertices[i]);
		//	}
		//}

		//cout << "If starting at " << startingVertex << ", visiting all cities, and going back to " << startingVertex
		//	<< ", then possible paths are: \n";
		//cout << std::left << std::setw(15) << startingVertex << "->";
		//for (auto& vertex : verticesWithoutStartingVertex)
		//{
		//	cout << std::left << std::setw(15) << vertex << "->";
		//}
		//cout << std::left << std::setw(15) << startingVertex << "\n";

		//while (myNextPermutation(verticesWithoutStartingVertex))
		//{
		//	//cout << std::left << std::setw(15) << startingVertex << "->";
		//	//for (auto& vertex : verticesWithoutStartingVertex)
		//	//{
		//	//	cout << std::left << std::setw(15) << vertex << "->";
		//	//}
		//	//cout << std::left << std::setw(15) << startingVertex << "\n";

		//}
		//if (std::find())

		auto possiblePaths = generatePossiblePaths_ForTSP(startingVertex); 
	
		//print paths (optional, for sanity check) 
		for (auto& path : possiblePaths)
		{
			int counter = 1; 
			for (auto& city : path)
			{
				cout << std::left << std::setw(15) << city; 
				if (counter < path.size())
				{
					cout << "->";
				}
				counter++; 
			}
			cout << "\n";
		}

		for (auto& path : possiblePaths)
		{
			int totalPathWeight = 0; 
			for (int i = 0; i < path.size() - 1; ++i)
			{
				totalPathWeight += findEdgeWeight(path[i], path[i + 1]);
			}

			cout << "Total path weight: " << totalPathWeight << " miles\n";
		}

		//get weights of each path: 

	}

	/*
	ABANDONED - for now
	traverses all possible paths (by def, a "path" does visits each vertex only once)
	Assumes (to some extent) that graph is COMPLETE 
	for all paths, stores map of path and its total weight (distance) 
	@return  the path (concatenated string, ex: Austin->Chicago->Boston->etc) 
	and its weight (as std::pair)
	*/
	map<int, string> solveTSP_ByBruteForce(string startingVertex)
	{
		if (!isCompleteGraph())
		{
			cout << "Warning - graph is not complete -> might get stuck here ...";
		}

		map<int, string> pathsAndTheirWeights;

		string currentVertex = startingVertex;

		vector<string> alreadyVisited;// = { currentVertex };

		random_device rd;
		mt19937 engine(rd());

		int totalPathWeight = 0;

		string pathSoFar = startingVertex;

		do
		{
			auto neighbors = getNeighborsOfVertex(currentVertex);

			vector<string> nonvisitedNeighbors;
			//remove previously-visted neighbors from consideration: 
			for (auto& theNeighbor : neighbors)
			{
				if (std::find(neighbors.begin(), neighbors.end(), theNeighbor) == neighbors.end())
				{
					nonvisitedNeighbors.push_back(theNeighbor);
				}
			}


			uniform_int_distribution<int> dist(0, neighbors.size() - 1);

			//pick random neighbor from remainder

			int chosenIndex = dist(engine);  //maybe the correct syntax

			string chosenNeighbor = neighbors[chosenIndex];
			//update currentVertex
			alreadyVisited.push_back(chosenNeighbor);

			totalPathWeight += findEdgeWeight(currentVertex, chosenNeighbor);

			currentVertex = chosenNeighbor;

			cout << "Moving to " << chosenNeighbor << "\n";
			pathSoFar += "->" + chosenNeighbor;


		} while (currentVertex != startingVertex);

		pathsAndTheirWeights.insert({ totalPathWeight, pathSoFar });

		return pathsAndTheirWeights;
	}

	//is it "greedy" or "lazy"? 
	// Chooses to take shortest edge (excluding previously-visited vertices) at all steps 
	void approximatelySolveTSP_WithGreed()
	{

	}

};




