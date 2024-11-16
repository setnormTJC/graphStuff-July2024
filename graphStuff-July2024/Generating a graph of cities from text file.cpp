#include"Graph.h"

#include"fstream"


auto readFile_andReturnCityCoordinatesMap(string filepath)
{
	std::ifstream fin{ filepath };
	std::map<string, std::pair<double, double>> citiesCoordinatesMap;

	if (!fin)
	{
		cout << "FNFE!\n";
		return citiesCoordinatesMap; 
	}

	while (!fin.eof())
	{
		string city;
		char comma;
		double latitude;
		double longitude;

		//fin >> city;
		getline(fin, city, ',');
		/*fin >> comma;*/
		fin >> latitude;
		fin >> comma;
		fin >> longitude;
		fin.ignore();
		citiesCoordinatesMap.insert({ city, {latitude, longitude} });
	}

	fin.close();

	return citiesCoordinatesMap;

};

void printCitiesCoordinatesMap(const map <string, pair<double, double>>& citiesCoordinatesMap)
{
	for (auto& entry : citiesCoordinatesMap)
	{
		cout << std::fixed; 
		cout << setprecision(2); //display lat and long to hundredth of a degree 

		cout << std::left << setw(15)
			 << entry.first << "("
			//<< std::right << std::setw(10) 
			<< entry.second.first << " , " 
			//<< std::left << std::setw(10)
			<< entry.second.second << ")\n";
	}
}


const double EARTH_RADIUS_MILES = 3958.8; // Radius of the Earth in miles

double toRadians(double degree) 
{
	return degree * (3.14159 / 180.0);
}

/*Note that I did not dig into the details of haversine (not the name of a person)...*/
double calculateHaversineDistance(double lat1, double lon1, double lat2, double lon2) 
{
	double dLat = toRadians(lat2 - lat1);
	double dLon = toRadians(lon2 - lon1);

	lat1 = toRadians(lat1);
	lat2 = toRadians(lat2);

	double a = sin(dLat / 2) * sin(dLat / 2) +
		cos(lat1) * cos(lat2) *
		sin(dLon / 2) * sin(dLon / 2);

	double c = 2 * atan2(sqrt(a), sqrt(1 - a));

	return EARTH_RADIUS_MILES * c;
}

double calculateDistanceBetweenTwoCities(const map <string, pair<double, double>>& citiesCoordinatesMap,
	const string& firstCity, const string& secondCity)
{

	if (citiesCoordinatesMap.find(firstCity) == citiesCoordinatesMap.end()
		||
		citiesCoordinatesMap.find(secondCity) == citiesCoordinatesMap.end())
	{
		cout << "Either " << firstCity << "or " << secondCity << " was not found in map!\n";
		return -999.99; //perhaps not a good choice...
	}


	double firstCityLatitude = citiesCoordinatesMap.at(firstCity).first; 
	double secondCityLatitude = citiesCoordinatesMap.at(secondCity).first;

	double firstCityLongitude  = citiesCoordinatesMap.at(firstCity).second;
	double secondCityLongitude = citiesCoordinatesMap.at(secondCity).second;

	//cout << firstCity << "'s loc: (" << firstCityLatitude << "," << firstCityLongitude << ")\n";
	//cout << secondCity << "'s loc: (" << secondCityLatitude << "," << secondCityLongitude << ")\n";

	//double radicand = (pow(secondCityLatitude - firstCityLatitude, 2)
	//	+
	//	pow(secondCityLongitude - firstCityLongitude, 2));

	//double distance = sqrt(radicand);

	//double approximateMilesPerDegree = 60; //very approximate -> will be problematic for certain inputs 

	//return distance * approximateMilesPerDegree; //temp

	return calculateHaversineDistance(firstCityLatitude, firstCityLongitude, secondCityLatitude, secondCityLongitude);

}

WeightedUndirectedGraph generateGraph_givenCityCoordinatesMap(const map <string, pair<double, double>>& citiesCoordinatesMap)
{
	WeightedUndirectedGraph graphOfNCities; 

	for (auto& entry : citiesCoordinatesMap)
	{
		graphOfNCities.addVertex(entry.first); 
	}

	string firstCity = graphOfNCities.vertices.at(0);
	string secondCity = graphOfNCities.vertices.at(0 + 1);

	double distance = calculateDistanceBetweenTwoCities(citiesCoordinatesMap, firstCity, secondCity);
	//edges.push_back({ firstCity, secondCity, (int)distance });
	graphOfNCities.addEdge(firstCity, secondCity, (int)distance); 

	while (myNextPermutation(graphOfNCities.vertices)) //myNextPermutation is overkill (inefficient) here...
	{
		for (int i = 0; i < graphOfNCities.vertices.size() - 1; ++i)
		{
			string firstCity = graphOfNCities.vertices.at(i);
			string secondCity = graphOfNCities.vertices.at(i + 1);

			double distance = calculateDistanceBetweenTwoCities(citiesCoordinatesMap, firstCity, secondCity);
			//cout << fixed << setprecision(0); //only display to nearest mile
			//cout << "Distance between " << firstCity << " and " << secondCity << ": " << distance << " miles\n";

			graphOfNCities.addEdge(firstCity, secondCity, (int)distance); 

			//edges.push_back({ firstCity, secondCity, (int)distance });
		}
	}

	//sort for ease of comprehension:
	std::sort(graphOfNCities.vertices.begin(), graphOfNCities.vertices.end()); //sorting strings
	std::sort(graphOfNCities.edges.begin(), graphOfNCities.edges.end()); 
	//sorting requires overloaded < operator for WeightedEdge class (I sorted by first vertex alphabetical)

	return graphOfNCities; 
}
//WeightedUndirectedGraph generateGraphOf5Cities()
//{

int main()
{

	//auto citiesCoordinatesMap = readFile_andReturnCityCoordinatesMap
	//								("some cities and their latitudes and longitudes.txt");

	auto citiesCoordinatesMap = readFile_andReturnCityCoordinatesMap
	("copilot generated cities and their coordinates.txt");


	//printCitiesCoordinatesMap(citiesCoordinatesMap); 

	//string firstCity = "Austin TX"; 
	//string secondCity = "Dallas TX";
	//double distance = calculateDistanceBetweenTwoCities(citiesCoordinatesMap, firstCity, secondCity);


	//cout << "Distance between these is: " << distance << " miles\n";

	auto graphOfNCities = generateGraph_givenCityCoordinatesMap(citiesCoordinatesMap); 

	//cout << std::boolalpha; 
	//cout << graphOfNCities.isCompleteGraph() << "\n"; //true

	string startingCity = "San Francisco CA";
	//auto neighborsOfStartingCity = graphOfNCities.getNeighborsOfVertex(startingCity);
	//for (auto& neigh : neighborsOfStartingCity)
	//{
	//	cout << neigh << "\n";
	//}

	//graphOfNCities.bruteForceTSP_November14(startingCity); 
	graphOfNCities.approximatelySolveTSP_WithGreed(startingCity); 


	//Houston TX, 29.76, -95.37
	//	Seattle WA, 47.61, -122.33
	//	Boston MA, 42.36, -71.06
	//	Las Vegas NV, 36.17, -115.14
	return 0; 
}