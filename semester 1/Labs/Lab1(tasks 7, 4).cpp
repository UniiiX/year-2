#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>

using namespace std;

template <typename Typename>
class Graph;

template <typename Typename>
class List;

template <typename Typename>
class Node;

class Dice;

class SetOfDices;

///-----------------------------------------------------------------------------------------------------------

template <typename Typename>
class Node
    {
        friend List<Typename>;
        friend Graph<Typename>;
    public:
        Typename GetData()
        {
            return data;
        }

    private:
        Typename data;
        Node* next;

        Node (Typename data = Typename(), Node* next = NULL)
        {
            this->data = data;
            this->next = next;
        }

        Node (Typename (*randomizationFunction)(), Node* next = NULL)
        {
            data = randomizationFunction();
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
    Typename GetVertex(int vertexNumber);
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

class SetOfDices
{
public:
    ~SetOfDices();
    void AddDice(Dice dice);
    void Print();

private:
    vector<Dice> dices;
    vector<double> probability; // probabilities of all possible sums
    void CorrectProbabilityOfSum(Dice dice);
};

class Dice
{
    friend class SetOfDices;
public:
    Dice(int sides, vector<double> &probability);
    Dice(int sides);
    ~Dice();
    void Print();

private:
    int sides;
    int possibleSidesValues[7] = {2, 4, 6, 8, 10, 12, 20};
    vector<double> probability;
    void CorrectSidesValue(int sides);
    void CorrectProbabilityValues(vector<double> &probability);
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
Typename Graph<Typename>::GetVertex(int vertexNumber)
{
    if (vertexNumber > neighbours.size() - 1 || vertexNumber < 0)
    {
        cout << "Can not access vertex with number " <<  vertexNumber << "(there is no such vertex in the graph)" << endl;
        return Typename();
    }
    return vertex[vertexNumber];
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

///----------------------------------------class Dice methods-------------------------------------------------

Dice::Dice(int sides, vector<double> &probability)
{
    CorrectSidesValue(sides);
    CorrectProbabilityValues(probability);
}

Dice::Dice(int sides)
{
    CorrectSidesValue(sides);
    vector<double> probability;
    for (int i = 0; i < this->sides; i++)
    {
        probability.push_back(rand());
    }
    CorrectProbabilityValues(probability);
    probability.clear();
}

Dice::~Dice()
{
    probability.clear();
}

void Dice::CorrectSidesValue(int sides)
{
    if (possibleSidesValues[0] > sides)
    {
        this->sides = possibleSidesValues[0];
        return;
    }

    for (int i = 1; i < 7; i++)
    {
        if (possibleSidesValues[i] > sides)
        {
            this->sides = possibleSidesValues[i-1];
            return;
        }
    }

    this->sides = possibleSidesValues[6];
}

void Dice::CorrectProbabilityValues(vector<double> &probability)
{
    double sum =  0;

    for (int i = 0; i < this->sides; i++)
    {
        sum += probability[i];
    }

    for (int i = 0; i < this->sides; i++)
    {
        this->probability.push_back(probability[i] / sum);
    }
}

void Dice::Print()
{
    cout << "Printing dice(side : probability): " << endl;
    for (int i = 0; i < sides; i++)
    {
        cout << i + 1 << " : " << probability[i] << endl;
    }
}

///----------------------------------------class SetOfDices methods-------------------------------------------

SetOfDices::~SetOfDices()
{
    this->dices.clear();
    this->probability.clear();
}

void SetOfDices::AddDice(Dice dice)
{
    this->dices.push_back(dice);
    CorrectProbabilityOfSum(dice);
}

void SetOfDices::CorrectProbabilityOfSum(Dice dice)
{
    if (this->probability.size() == 0)
    {
        this->probability.push_back(0); // probability of sum which is equal 0 is 0
        for (int i = 0; i < dice.sides; i++)
        {
            this->probability.push_back(dice.probability[i]); // if there is only one dice in the set then the probability of the sum equals the probability of side
        }
    }
    else
    {
        vector<double> currentProbability(this->probability); // creating auxiliary vector to store current probabilities
        for (int i = 0; i < this->probability.size(); i++)
        {
            this->probability[i] = 0; // now that we have copied this vector we can set the values to zero
        }
        int minSum = 0;
        int maxSum = currentProbability.size(); // current maximal sum equals the size of current probabilities vector
        while (currentProbability[minSum] == 0)
        {
            minSum++; // counting current minimal sum
        }
        maxSum += dice.sides; // new maximal sum
        this->probability.resize(maxSum, 0); // resizing to the size of new maximal sum

        for (int i = minSum; i < currentProbability.size(); i++)
        {
            for (int j = 0; j < dice.sides; j++)
            {
                this->probability[i + j + 1] += currentProbability[i] * dice.probability[j]; // counting new probabilities
            }
        }
        currentProbability.clear(); // clearing auxiliary vector
    }

}

void SetOfDices::Print()
{
    cout << "Printing set of dices:" << endl;
    for (int i = 0; i < this->dices.size(); i++)
    {
        this->dices[i].Print();
    }
    cout << "Printing all possible sums and the probability of each sum(sum : probability)" << endl;
    for (int i = 0; i < this->probability.size(); i++)
    {
        if (this->probability[i] != 0)
        {
            cout << i << " : " << this->probability[i] << endl;
        }
    }
}

///-----------------------------------------------------------------------------------------------------------

void DemonstrationOfGraph()
{
    Graph<int> sampleGraph;
    sampleGraph.AddVertex(rand());

    int vertexNumber1 = 0;
    cout << "Vertex #" << vertexNumber1 << " in graph is: " << sampleGraph.GetVertex(vertexNumber1) << endl;

    sampleGraph.AddVertex(rand());
    sampleGraph.AddVertex(rand());
    sampleGraph.AddVertex(rand());
    sampleGraph.AddVertex(rand());
    sampleGraph.AddEdge(0,1);
    sampleGraph.AddEdge(0,2);
    sampleGraph.AddEdge(2,1);
    sampleGraph.AddEdge(3,1);
    sampleGraph.AddEdge(4,3);
    sampleGraph.PrintAdjacencyStruct();
    sampleGraph.PrintAdjacencyMatrix();
    sampleGraph.CheckConnectivity();
    vertexNumber1 = 4;
    int vertexNumber2 = 2;
    cout << "Distance between vertices #" << vertexNumber1 << " and #" << vertexNumber2 << " is: " << sampleGraph.CountDistance(vertexNumber1, vertexNumber2) << endl;
}

void DemonstrationOfDices()
{
    int dicesCount;
    SetOfDices dices;
    cout << "Enter count of dices: " << endl;
    cin >> dicesCount;
    for (int i = 0; i < dicesCount; i++)
    {
        int sides;
        cout << "Enter sides count of dice #" << i + 1 << ":(probabilities will be generated randomly) " << endl;
        cin >> sides;
        Dice dice(sides);
        dices.AddDice(dice);
    }
    dices.Print();
}

void DemonstrationFunction()
{
    DemonstrationOfGraph();
    DemonstrationOfDices();
}

int main()
{
    srand(time(NULL));
    DemonstrationFunction();
}
