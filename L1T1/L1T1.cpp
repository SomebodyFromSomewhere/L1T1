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


void read(std::string filename, std::vector<std::vector<int>>& array, int& N) {
	std::fstream file;
	file.open(filename);
	if (!file.is_open()) {
		err.addCriticalError("CANNOT READ FILE:" + filename, "READ");
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

void createGraph(std::vector<std::vector<int>>& inpt_array, std::map<Node, std::set<Node>>& Graph, int N) {
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			//UP
			if (((i - 1) >= 0) && (inpt_array[i - 1][j]) == 0) {
				Graph[{i, j}].insert({ i - 1, j });
			}
			//DOWN
			if (((i + 1) < N) && (inpt_array[i + 1][j] == 0))
			{
				Graph[{ i, j }].insert({ i + 1, j });
			}
			//LEFT
			if (((j - 1) >= 0) && (inpt_array[i][j - 1]) == 0) {
				Graph[{i, j}].insert({ i, j - 1 });
			}
			//RIGHT
			if (((j + 1) < N) && (inpt_array[i][j + 1]) == 0) {
				Graph[{i, j}].insert({ i, j + 1 });
			}
		}
	}
}

void DFS(Node pos, std::vector<std::vector<int>>& data, std::map<Node, std::set<Node>>& Graph, int N) {
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
		coords.insert(Graph[it].cbegin(), Graph[it].cend());
		//LOOKING ALL NEIGHBOURS
		while (coords.size() != 0){
			std::set<Node>::iterator iter = coords.cbegin();
			DFS(*iter, data, Graph, N);
			coords.erase(iter);
		}
	}
}
template<typename T>
void write(T val, std::string filename) {
	std::ofstream file(filename);
	if (!file.is_open())
	{
		err.addCriticalError("CANNOT OPEN FILE: " + filename, "WRITE");
	}

	file << val;
}


int main() {
	time_t start = clock();

	std::vector<std::vector<int>> labirinth;
	int N;

	read("INPUT.txt", labirinth, N);

	std::map<Node, std::set<Node>> Graph{};
	createGraph(labirinth, Graph, N);

	DFS({0, 0}, labirinth, Graph, N);

	write(result, "OUTPUT.txt");

	calculateTime(start);
	return 0;
}