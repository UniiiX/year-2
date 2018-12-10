#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

class Graph
{
public:
	Graph(istream &);
	~Graph();
	void input(istream &);
	void print();
	void findHammocks();

private:
	vector<vector<bool> > adjMatrix;
	set<int> hammock;
	vector<bool> visited;
	int size;
	bool successfulDFS;

	void DFS(int begin, int end);
	bool checkIfHammock(int begin, int end);
};

//------------------------------------------------------------------------------------

Graph::Graph(istream &in)
{
	input(in);
}

Graph::~Graph()
{
    for (int i = 0; i < size; i++)
    {
        adjMatrix[i].clear();
    }
    adjMatrix.clear();
    visited.clear();
    hammock.clear();
}

void Graph::input(istream &fin)
{
	vector<int> vertices;
	vector<int> vEdges;
    set<int> uniqueVertices;
	int currEdge, currVer;
	while (fin >> currEdge >> currVer) {
		vertices.push_back(currVer);
		uniqueVertices.insert(currVer);
		vEdges.push_back(currEdge);
	}

	size = uniqueVertices.size();
	adjMatrix.resize(size, vector<bool>(size, false));

	for (int i = 0; i < vEdges.size(); i++)
		for (int j = i + 1; j < vEdges.size(); j++) {
			if (vEdges[j] == vEdges[i]) {
				int firstVertex = vertices[i];
				int secondVertex = vertices[j];
                adjMatrix[firstVertex][secondVertex] = true;
			}
		}
}

void Graph::DFS(int begin, int end)
{
    visited[begin] = true;
    hammock.insert(begin);
    if (begin == end)
    {
        successfulDFS = true;
        return;
    }
    for (int i = 0; i < size; i++)
    {
        if (!visited[i] && adjMatrix[begin][i])
        {
            DFS(i, end);
        }
    }
}

bool Graph::checkIfHammock(int begin, int end)
{
    visited.assign(size, false);
    successfulDFS = false;
    DFS(begin, end);

    for (int i = 0; i < size; i++)
    {
        if (successfulDFS)
        {
            if (adjMatrix[i][begin] && hammock.count(i))
            {
                return false;
            }

            if (adjMatrix[end][i] && hammock.count(i))
            {
                return false;
            }
            if (visited[i] && !hammock.count(i))
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    return true;
}

void Graph::findHammocks()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i != j)
            {
                hammock.clear();
                if (checkIfHammock(i,j))
                {
                    cout << "Found hammock(first end, second end): (" << i << ", " << j << ")" << endl;
                }
            }
        }
    }
}

void Graph::print()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
}


//------------------------------------------------------------------------------------

int main() {
	ifstream input("input.txt");
	Graph myGraph(input);
    myGraph.print();
    myGraph.findHammocks();
}

