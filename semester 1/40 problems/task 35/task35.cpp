#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <cstdlib>

using namespace std;

class Graph {
private:
	string **adjMatrix;
	int numVertex;
	string minElement;
	string maxElement;
	vector<bool> vertexArray;
	vector<string> resArray;
	void setMinMax(string left, string right);
	map<string, int> hashMap;
	void printResult(bool res);

public:
	Graph(ifstream& input);
	Graph(){

	}
	~Graph() {

	}
	void checkCycle();
};

Graph::Graph(ifstream& input) {
	int numRelations;
	minElement = "";
	input >> numVertex >> numRelations;

	adjMatrix = new string*[numVertex];
	for (int i(0); i < numVertex; i++) {
		adjMatrix[i] = new string[numVertex];
	}

	for (int i(0); i < numVertex; i++) {
		for (int j(0); j < numVertex; j++) {
			adjMatrix[i][j] = "";
		}
	}

	int keys = 0;
	string rowVertex = "";
	string columnVertex = "";
	for (int i(0); i < numRelations; i++) {
		input >> rowVertex >> columnVertex;
		// check if there are such key in hashMap
		// return 1 if it does, 0 if not
		if (hashMap.count(rowVertex) == 0) {
			hashMap[rowVertex] = keys++;
		}
		if (hashMap.count(columnVertex) == 0)
			hashMap[columnVertex] = keys++;
		setMinMax(rowVertex, columnVertex);
		adjMatrix[hashMap[rowVertex]][hashMap[columnVertex]] = columnVertex;
	}

	// creating vertex array
	for (int i(0); i < numVertex; i++) {
		vertexArray.push_back(false);
	}
}

void Graph::checkCycle() {
	resArray.push_back(minElement);
	string currString = minElement;
	for (int i(0); i < numVertex; i++) {
		bool aloneV = true;
		if (currString == maxElement && resArray.size() != vertexArray.size()) { // check if the "greatest" elem is found but not all vertexes were traversed
			printResult(false);
			break;
		}
		for (int j(0); j < numVertex; j++) {
			string tmp = adjMatrix[hashMap[currString]][j];
			if (vertexArray[hashMap[currString]] == true && tmp != "") { // check if we want to pass the vertex twice
				printResult(false);
				break;
			}
			else if (tmp != "") {
				resArray.push_back(tmp);
				vertexArray[hashMap[currString]] = true; // mark passed
				currString = tmp;
				aloneV = false;
				break;
			}
		}
		if (aloneV && currString != maxElement) { /// if there are two or more groups of connectivity
			printResult(false);
			break;
		}
	}


	printResult(true);
}

// searching the min element in the set
// if the graph is not linked the DFS exclude the possibility of forming the right ...
void Graph::setMinMax(string left, string right) {
	if (maxElement == "")
		maxElement = right;
	if (minElement == "")
		minElement = left;
	if (minElement == right)
		minElement = left;
	if (maxElement == left)
		maxElement = right;
}

void Graph::printResult(bool res) {
	if (res)
		for (int i(0); i < resArray.size(); i++) {
			cout << resArray[i];
			if (i != resArray.size() - 1)
			cout << " -> ";
		}
	else {
		cout << " Impossible to create the ascending set of the elements" << endl;
		system("pause");
		exit(0);
		return;
	}
	cout << endl;
}

int main(){
	ifstream input("relations.txt");
	Graph graph(input);
	graph.checkCycle();
	system("pause");
}
