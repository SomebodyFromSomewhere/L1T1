#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include "utils/Error.h"
#include "utils/utils.h"

Error err;
int result = 0;
const int segmentSize = 9;

using Node = std::pair<int, int>;
std::map<Node, bool> isVisited{};


void read(std::string fileName, std::vector<std::vector<int>>& array, int& N) {
	std::fstream file;
	file.open(fileName);
	if (!file.is_open()) {
		err.addCriticalError("CANNOT READ FILE:" + fileName, "READ");
	}
	file >> N;
	if (N < 3 && N > 33)
	{
		err.addCriticalError("FILE MUST BE NOT LESS THAN 3 OR NOT GREATER THAN 33", "READ");
	}
	array.resize(N);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (file.eof())
			{
				err.addCriticalError("CANNOT READ FILE: EOF", "READ");
			}
			char temp;
			file >> temp;
			if (temp == '.') {
				array[i].push_back(0);
			}
			else {
				array[i].push_back(1);
			}
		}
	}
}

void createGraph(std::vector<std::vector<int>>& inptArray, std::map<Node, std::set<Node>>& graph, int N) {
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			//UP
			if (((i - 1) >= 0) && (inptArray[i - 1][j]) == 0) {
				graph[{i, j}].insert({ i - 1, j });
			}
			//DOWN
			if (((i + 1) < N) && (inptArray[i + 1][j] == 0))
			{
				graph[{ i, j }].insert({ i + 1, j });
			}
			//LEFT
			if (((j - 1) >= 0) && (inptArray[i][j - 1]) == 0) {
				graph[{i, j}].insert({ i, j - 1 });
			}
			//RIGHT
			if (((j + 1) < N) && (inptArray[i][j + 1]) == 0) {
				graph[{i, j}].insert({ i, j + 1 });
			}
		}
	}
}

void DFS(Node pos, std::vector<std::vector<int>>& data, std::map<Node, std::set<Node>>& graph, int N) {
	const Node& it = pos;
	//std::cout << "[" << it.first << ", " << it.second << "]" << std::endl; //UNCOMMENT TO DEBUG
	if (!isVisited[it])
	{
		if ((it.first || it.second))
		{
			//UP
			if ((it.first - 1) < 0)
			{
				result += segmentSize;
			}
			else if (data[it.first - 1][it.second] == 1)
			{
				result += segmentSize;
			}
			//LEFT
			if ((it.second - 1) < 0)
			{
				result += segmentSize;
			}
			else if (data[it.first][it.second - 1] == 1)
			{
				result += segmentSize;
			}
		}

		if ((it.first != (N - 1)) || (it.second != (N - 1)))
		{
			//DOWN
			if ((it.first + 1) >= N)
			{
				result += segmentSize;
			}
			else if (data[it.first + 1][it.second] == 1)
			{
				result += segmentSize;
			}
			//RIGHT
			if ((it.second + 1) >= N)
			{
				result += segmentSize;
			}
			else if (data[it.first][it.second + 1] == 1)
			{
				result += segmentSize;
			}
		}
		
		isVisited[it] = true;
		std::set<Node> coords;
		coords.insert(graph[it].cbegin(), graph[it].cend());
		//LOOKING ALL NEIGHBOURS
		while (coords.size() != 0){
			std::set<Node>::iterator iter = coords.cbegin();
			DFS(*iter, data, graph, N);
			coords.erase(iter);
		}
	}
}
template<typename T>
void write(T val, std::string fileName) {
	std::ofstream file(fileName);
	if (!file.is_open())
	{
		err.addCriticalError("CANNOT OPEN FILE: " + fileName, "WRITE");
	}

	file << val;
}


int main() {
	time_t start = clock();

	std::vector<std::vector<int>> labirinth;
	int N;

	read("INPUT.txt", labirinth, N);

	std::map<Node, std::set<Node>> graph{};
	createGraph(labirinth, graph, N);

	DFS({0, 0}, labirinth, graph, N);

	write(result, "OUTPUT.txt");

	calculateTime(start);
	return 0;
}