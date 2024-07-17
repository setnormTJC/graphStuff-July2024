#include"Graph.h"

int main(int argc, char* argv)
{
	int squareGridDimension = 5; 
	GridGraph fiveGrid(squareGridDimension); 

	PairOfIntegers_Vertex startVertex = { 1, 1 };

	PairOfIntegers_Vertex endVertex = { squareGridDimension, squareGridDimension };

	//fiveGrid.takeRandomKnightWalk(startVertex, endVertex); 

	//const int NUMBER_OF_EXPERIMENTS = 100; 

	bool hadSuccessfulTour = false; 

	size_t attemptCount = 0;  //long long (size_t) might overflow ...
	while (hadSuccessfulTour == false)
	{
		hadSuccessfulTour = fiveGrid.takeKnightsTour(startVertex);
		attemptCount++; 

	}

	cout << "Took this many attempts: " << attemptCount << "\n";

}