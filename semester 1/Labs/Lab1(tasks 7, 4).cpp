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
    void CheckConnectivity();

private:
    vector<Typename> vertex;
    vector<List<int>* > neighbours;
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
    }
    neighbours.clear();
    vertex.clear();
}

template <typename Typename>
void Graph<Typename>::AddVertex(Typename vertex)
{
    this->vertex.push_back(vertex);
    List<int>* toPush = new List<int>();
    toPush->Append(this->vertex.size() - 1); // This means that numeration of vertices in graph starts from 0
    neighbours.push_back(toPush);
}

template <typename Typename>
void Graph<Typename>::AddEdge(int vertexNumber1, int vertexNumber2)
{
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
    neighbours[vertexNumber1]->Append(vertexNumber2);
    neighbours[vertexNumber2]->Append(vertexNumber1);
}

template <typename Typename>
void Graph<Typename>::PrintAdjacencyStruct()
{
    for (int i = 0; i < neighbours.size(); i++)
    {
        neighbours[i]->Print();
    }
}

template <typename Typename>
void Graph<Typename>::CheckConnectivity()
{
    int initialVertexNumber = 0;
    int size = vertex.size();
    queue<int> q;
    bool* visited = new bool[size];
    for (int i = 0; i < size; i++)
    {
        visited[i] = false;
    }

    q.push(initialVertexNumber);
    visited[initialVertexNumber] = true;
    while (!q.empty())
    {
        initialVertexNumber = q.front();
        q.pop();
        Node<int>* current = neighbours[initialVertexNumber]->head;
        while (current)
        {
            if (!visited[current->data])
            {
                visited[current->data] = true;
                q.push(current->data);
            }
            current = current->next;
        }
    }

    for (int i = 0; i < size; i++)
    {
        if (!visited[i])
        {
            cout << "Graph is not connected" << endl;
            delete[] visited;
            return;
        }
    }
    cout << "Graph is connected" << endl;
    delete[] visited;
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
    exampleGraph.AddVertex(true);
    exampleGraph.AddVertex(true);
    exampleGraph.AddVertex(true);
    exampleGraph.AddEdge(0,1);
    exampleGraph.AddEdge(0,2);
    exampleGraph.PrintAdjacencyStruct();
    exampleGraph.CheckConnectivity();
}
