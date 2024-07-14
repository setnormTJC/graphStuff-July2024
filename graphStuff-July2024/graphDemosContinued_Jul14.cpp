#include"Graph.h"

WeightedUndirectedGraph generate3By3Grid_Graph()
{
	WeightedUndirectedGraph threeBy3Grid_Graph; 

	threeBy3Grid_Graph.vertices =
	{ "02", "12", "22",
		"01", "11", "21",
		"00", "10", "20"
	};

	//generate programmatically for larger grids, of course (all weights/distances are 1) 
	threeBy3Grid_Graph.edges =
	{
		{"02", "12", 1},							{"12", "22", 1}, //horizontal lines 
		{"02", "01", 1},	{"12", "11", 1},		{"22", "21", 1}, //the "down strokes"/vertical lines in the grid
		{"01", "11", 1},							{"11", "21", 1},
		{"01", "00", 1},	{"11", "10", 1},		{"21", "20", 1},
		{"00", "10", 1},							{"10", "20", 1}
	};

	return threeBy3Grid_Graph;
}

int main(int argc, string* argv)
{
	auto threeBy3Grid_Graph = generate3By3Grid_Graph(); 

	string startingVertex = "02"; //"top left" (x = 0, y = 2)
	string endingVertex = "20"; //bpttom right (x = 2, y = 0)


	threeBy3Grid_Graph.takeRandomWalk_UntilSomeEnd(startingVertex, endingVertex); 

}