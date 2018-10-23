#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

using namespace std;

class Graph
{
public:
    ~Graph();
    void PrintAdjacencyMatrix();
    void ReadFromFile(char* filename);
    int CountDistance(int vertexNumber1, int vertexNumber2);

private:
    void ResizeMatrix(char* filename);
    vector<vector<bool> > adjacencyMatrix;
};

void Graph::ResizeMatrix(char* filename)
{
    int size = 0;
    ifstream fin(filename);
    while (!fin.eof())
    {
        int vertexNumber1;
        int vertexNumber2;
        fin >> vertexNumber1;
        fin >> vertexNumber2;
        size = max(size, max(vertexNumber1, vertexNumber2));
    }
    //resizing matrix and initializing it with zeros
    adjacencyMatrix.resize(size);
    for (int i = 0; i < size; i++)
    {
        adjacencyMatrix[i].resize(size);
        for (int j = 0; j < size; j++)
        {
            adjacencyMatrix[i][j] = 0;
        }
    }
    fin.close();
}

Graph::~Graph()
{
    for (int i = 0; i < adjacencyMatrix.size(); i++)
    {
        adjacencyMatrix[i].clear();
    }
    adjacencyMatrix.clear();
}

void Graph::ReadFromFile(char* filename)
{
    ResizeMatrix(filename);
    int size = adjacencyMatrix.size();
    ifstream fin(filename);
    while (!fin.eof())
    {
        int vertexNumber1;
        int vertexNumber2;
        fin >> vertexNumber1;
        fin >> vertexNumber2;

        //adding edge between vertices vertexNumber1 and vertexNumber2
        adjacencyMatrix[vertexNumber1 - 1][vertexNumber2 - 1] = 1;
        adjacencyMatrix[vertexNumber2 - 1][vertexNumber1 - 1] = 1;
    }
    fin.close();
}

int Graph::CountDistance(int vertexNumber1, int vertexNumber2)
{
    if (vertexNumber1 == vertexNumber2)
    {
        cout << "Distance can only be counted between different vertices" << endl;
        return 0;
    }
    if (vertexNumber1 > adjacencyMatrix.size() || vertexNumber1 <= 0)
    {
        cout << "Can not count distance to vertex with number " <<  vertexNumber1 << "(there is no such vertex in the graph)" << endl;
        return -1;
    }
    if (vertexNumber2 > adjacencyMatrix.size() || vertexNumber2 <= 0)
    {
        cout << "Can not count distance to vertex with number " <<  vertexNumber2 << "(there is no such vertex in the graph)" << endl;
        return -1;
    }

    int currentVertexNumber = vertexNumber1;
    int size = adjacencyMatrix.size();
    queue<int> q;
    int result; // we need this variable in order to free the memory off of distance array
    int* distance = new int[size]; // array that contains information about distance from initial vertex to current
    bool* visited = new bool[size]; // array that indicates whether the vertex has already been visited or not
    for (int i = 0; i < size; i++) // initializing arrays
    {
        distance[i] = 0;
        visited[i] = false;
    }

    q.push(currentVertexNumber);
    visited[currentVertexNumber - 1] = true;
    while (!q.empty())
    {
        currentVertexNumber = q.front();
        if (currentVertexNumber == vertexNumber2) // if we have found second vertex we can exit the width-first search here
        {
            result = distance[currentVertexNumber - 1]; // after this we can free the memory up
            delete[] visited; // freeing the memory up
            delete[] distance;
            return result;
        }
        q.pop();

        for (int i = 0; i < size; i++)
        {
            if (!visited[i] && adjacencyMatrix[currentVertexNumber - 1][i] == 1) //if neighbour is not visited
            {
                visited[i] = true; // marking neighbour as visited and pushing it into the queue
                q.push(i + 1);
                distance[i] = distance[currentVertexNumber - 1] + 1; // distance to each unvisited neighbour is greater than distance to current vertex by 1
            }
        }
    }
    // if we haven't exited the function yet this means that given vertices belong to different connected components
    cout << "Can not count distance(graph is not connected)" << endl;
    delete[] visited;
    delete[] distance;
    return -1;
}

void Graph::PrintAdjacencyMatrix()
{
    int size = adjacencyMatrix.size();
    cout << "Printing graph as adjacency matrix:" << endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << int(adjacencyMatrix[i][j]) << " ";
        }
        cout << endl;
    }
}

void DemonstrationFunction()
{
    Graph* graph = new Graph;
    graph->ReadFromFile("input_task15.txt");
    graph->PrintAdjacencyMatrix();
    int vertexNumber1;
    int vertexNumber2;
    cout << "Input vertex 1 number: " << endl;
    cin >> vertexNumber1;
    cout << "Input vertex 2 number: " << endl;
    cin >> vertexNumber2;
    int distance = graph->CountDistance(vertexNumber1, vertexNumber2);
    cout << "Distance between verices " << vertexNumber1 << " and " << vertexNumber2 << " is: " << distance << endl;
    graph->~Graph();
}

int main()
{
    DemonstrationFunction();
}
