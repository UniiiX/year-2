#include <iostream>
#include <vector>
#include <queue>
#include <iterator>

using namespace std;

template <typename Typename>
class Graph;

template <typename Typename>
class List;

template <typename Typename>
class Node;

///-----------------------------------------------------------------------------------------------------------

template <typename Typename>
class Node
    {
        friend List<Typename>;
        friend Graph<Typename>;
    private:
        Typename data;
        Node* next;

        Node (Typename data = Typename(), Node* next = NULL)
        {
            this->data = data;
            this->next = next;
        }
    };

template <typename Typename>
class List
{
    friend Graph<Typename>;
public:
    List();
    ~List();
    void Append(Typename data);
    void Print();

private:
    Node<Typename>* head;
    Node<Typename>* tail;

};

template <typename Typename>
class Graph
{
public:
    ~Graph();
    void AddVertex(Typename vertex);
    void AddEdge(int vertexNumber1, int vertexNumber2);
    void PrintAdjacencyStruct();
    void PrintAdjacencyMatrix();
    void CheckConnectivity();
    int CountDistance(int vertexNumber1, int vertexNumber2);

private:
    vector<Typename> vertex;
    vector<List<int>* > neighbours;
    vector<vector<bool> > adjacencyMatrix; // storing a graph simultaneously as adjacency structure and adjacency matrix
};

///----------------------------------------class List methods-------------------------------------------------

template <typename Typename> // constructor
List<Typename>::List()
{
    head = NULL;
    tail = NULL;
}

template <typename Typename> // destructor
List<Typename>::~List()
{
    Node<Typename>* current = head;
    while (current)
    {
        Node<Typename>* next = current->next;
        delete current;
        current = next;
    }
}

template <typename Typename>
void List<Typename>::Append(Typename data)
{
    Node<Typename>* nodeToAdd = new Node<Typename>(data); // using Node constructor to initialize nodeToAdd->data with data and nodeToAdd->next with NULL
    if (!head)
    {
        head = nodeToAdd;
    }
    else
    {
        tail->next = nodeToAdd;
    }
    tail = nodeToAdd;
}

template <typename Typename>
void List<Typename>::Print()
{
    cout << "(";
    Node<Typename>* current = head;
    while (current)
    {
        cout << current->data;
        if (current != tail)
        {
            cout << ", ";
        }
        current = current->next;
    }
    cout << ")" << endl;
}

///----------------------------------------class Graph methods------------------------------------------------

template <typename Typename> // destructor
Graph<Typename>::~Graph()
{
    for (int i = 0; i < neighbours.size(); i++)
    {
        neighbours[i]->~List();
        adjacencyMatrix[i].clear();
    }
    adjacencyMatrix.clear();
    neighbours.clear();
    vertex.clear();
}

template <typename Typename>
void Graph<Typename>::AddVertex(Typename vertex)
{
    this->vertex.push_back(vertex); // adding vertex
    int newSize = this->vertex.size();

    List<int>* listToPush = new List<int>(); // creating list of neighbours for the new vertex
    listToPush->Append(newSize - 1); // This means that numeration of vertices in graph starts from 0
    neighbours.push_back(listToPush); // adding the list to the adjacency vector

    vector<bool> vectorToPush(newSize); // creating boolean vector to push it back to the adjacency matrix
    adjacencyMatrix.push_back(vectorToPush); // pushing it back
    for (int i = 0; i < newSize; i++) // initializing new row and column with false
    {
        adjacencyMatrix[i][newSize - 1] = false;
        adjacencyMatrix[newSize - 1][i] = false;
    }
}

template <typename Typename>
void Graph<Typename>::AddEdge(int vertexNumber1, int vertexNumber2)
{
    if (vertexNumber1 == vertexNumber2)
    {
        cout << "Can not add an edge(an edge can be added only in between two different vertices)" << endl;
        return;
    }
    if (vertexNumber1 > neighbours.size() - 1 || vertexNumber1 < 0)
    {
        cout << "Can not add an edge to vertex with number " <<  vertexNumber1 << "(there is no such vertex in the graph)" << endl;
        return;
    }
    if (vertexNumber2 > neighbours.size() - 1 || vertexNumber2 < 0)
    {
        cout << "Can not add an edge to vertex with number " <<  vertexNumber2 << "(there is no such vertex in the graph)" << endl;
        return;
    }

    neighbours[vertexNumber1]->Append(vertexNumber2); // adding an edge to the adjacency structure
    neighbours[vertexNumber2]->Append(vertexNumber1);

    adjacencyMatrix[vertexNumber1][vertexNumber2] = true; // adding an edge to the adjacency matrix
    adjacencyMatrix[vertexNumber2][vertexNumber1] = true;
}

template <typename Typename>
void Graph<Typename>::PrintAdjacencyStruct()
{
    cout << "Printing graph as adjacency structure:" << endl;
    for (int i = 0; i < neighbours.size(); i++)
    {
        neighbours[i]->Print();
    }
}

template <typename Typename>
void Graph<Typename>::PrintAdjacencyMatrix()
{
    int size = neighbours.size();
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

template <typename Typename>
void Graph<Typename>::CheckConnectivity()
{
    int currentVertexNumber = 0; // this is the initial vertex for width-first search
    int size = vertex.size();
    queue<int> q;
    bool* visited = new bool[size]; // array that indicates whether the vertex has already been visited or not
    for (int i = 0; i < size; i++)
    {
        visited[i] = false;
    }

    q.push(currentVertexNumber);
    visited[currentVertexNumber] = true;
    while (!q.empty())
    {
        currentVertexNumber = q.front();
        q.pop();
        Node<int>* current = neighbours[currentVertexNumber]->head;
        while (current)
        {
            if (!visited[current->data])
            {
                visited[current->data] = true; // marking neighbour as visited and adding the vertex to the queue
                q.push(current->data);
            }
            current = current->next; // moving to the next neighbour
        }
    }

    for (int i = 0; i < size; i++)
    {
        if (!visited[i]) // if at least one vertex was unvisited then graph is not connected
        {
            cout << "Graph is not connected" << endl;
            delete[] visited;
            return;
        }
    }
    cout << "Graph is connected" << endl;
    delete[] visited;
}


template <typename Typename>
int Graph<Typename>::CountDistance(int vertexNumber1, int vertexNumber2)
{
    if (vertexNumber1 == vertexNumber2)
    {
        cout << "Distance can only be counted between different vertices" << endl;
        return 0;
    }
    if (vertexNumber1 > neighbours.size() - 1 || vertexNumber1 < 0)
    {
        cout << "Can not count distance to vertex with number " <<  vertexNumber1 << "(there is no such vertex in the graph)" << endl;
        return -1;
    }
    if (vertexNumber2 > neighbours.size() - 1 || vertexNumber2 < 0)
    {
        cout << "Can not count distance to vertex with number " <<  vertexNumber2 << "(there is no such vertex in the graph)" << endl;
        return -1;
    }

    int currentVertexNumber = vertexNumber1;
    int size = vertex.size();
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
    visited[currentVertexNumber] = true;
    while (!q.empty())
    {
        currentVertexNumber = q.front();
        if (currentVertexNumber == vertexNumber2) // if we have found second vertex we can exit the width-first search here
        {
            result = distance[currentVertexNumber]; // after this we can free the memory up
            delete[] visited; // freeing the memory up
            delete[] distance;
            return result;
        }
        q.pop();
        Node<int>* current = neighbours[currentVertexNumber]->head;
        while (current)
        {
            if (!visited[current->data])
            {
                visited[current->data] = true; // marking neighbour as visited and adding the vertex to the queue
                q.push(current->data);
                distance[current->data] = distance[currentVertexNumber] + 1; // distance to each unvisited neighbour is greater than distance to current vertex by 1
            }
            current = current->next; // moving to the next neighbour
        }
    }
    // if we haven't exited the function yet this means that given vertices belong to different connected components
    cout << "Can not count distance(graph is not connected)" << endl;
    delete[] visited;
    delete[] distance;
    return -1;
}

///-----------------------------------------------------------------------------------------------------------

int main()
{
    List<int> exampleList;
    exampleList.Append(5);
    exampleList.Append(6);
    exampleList.Append(7);
    exampleList.Print();

    Graph<int> exampleGraph;
    exampleGraph.AddVertex(100);
    exampleGraph.AddVertex(200);
    exampleGraph.AddVertex(300);
    exampleGraph.AddVertex(1100);
    exampleGraph.AddVertex(77);
    exampleGraph.AddEdge(0,1);
    exampleGraph.AddEdge(0,2);
    exampleGraph.AddEdge(2,1);
    exampleGraph.AddEdge(3,1);
    exampleGraph.AddEdge(4,3);
    exampleGraph.PrintAdjacencyStruct();
    exampleGraph.PrintAdjacencyMatrix();
    exampleGraph.CheckConnectivity();
    cout << exampleGraph.CountDistance(4,2) << endl;
}
