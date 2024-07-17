#include"Graph.h"

int main(int argc, char* argv)
{
	int squareGridDimension = 8; 
	GridGraph fiveGrid(squareGridDimension); 

	PairOfIntegers_Vertex startVertex = { 1, 1 };

	PairOfIntegers_Vertex endVertex = { squareGridDimension, squareGridDimension };

	//fiveGrid.takeRandomKnightWalk(startVertex, endVertex); 

	fiveGrid.takeKnightsTour(startVertex);


}