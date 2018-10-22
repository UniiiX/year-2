/* Имеется N человек и прямоугольная таблица А[1:N,1:N];элемент A[i,j] равен 1,
если человек i знаком с человеком j, А[i,j] == А[j,i]. Можно ли разбить людей на 2
группы, чтобы в каждой группе были только незнакомые люди. */

#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <string>

using namespace std;

class Graph
{
public:
    ~Graph();
    void PaintGraph();
    void ReadFromFile(char* filename);

private:
    vector<vector<int> > adjacencyMatrix;
    void PaintVertex(int vertexNumber, int* colors, queue<int> q);
};

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
    int size;
    ifstream fin(filename);
    fin >> size;
    adjacencyMatrix.resize(size);
    for (int i = 0; i < size; i++)
    {
        adjacencyMatrix[i].resize(size);
        for (int j = 0; j < size; j++)
        {
            fin >> adjacencyMatrix[i][j];
        }
    }
    fin.close();
}

void Graph::PaintGraph()
{
    queue<int> q;
    int vertexNumber;
    int size = adjacencyMatrix.size();
    int* colors = new int[size];
    for (int i = 0; i < size; i++)
    {
        colors[i] = -1; // -2 ~ can't be painted; -1 ~ not painted yet; 0,1 ~ painted
    }

    for (int i = 0; i < size; i++)
    {
        // doing width-first search for each vertex
        if (colors[i] == -1)
        {
            q.push(i);
            colors[i] = 0;
            while (!q.empty())
            {
                vertexNumber = q.front();
                q.pop();
                PaintVertex(vertexNumber, colors, q); // painting vertex depending on the color of neighbours
                if (colors[vertexNumber] == -2)
                {
                    cout << "Can't paint graph" << endl;
                    delete[] colors;
                    return; // exiting the function if graph can not be painted
                }
            }
        }
    }
    cout << "Painted graph is: " << endl;
    for (int i = 0; i < size; i++)
    {
        cout << i + 1 << " : " << colors[i] << endl;
    }
    delete[] colors;
}

void Graph::PaintVertex(int vertexNumber, int* colors, queue<int> q)
{
    int size = adjacencyMatrix.size();
    int neighboursColor = -1;
    for (int i = 0; i < size; i++)
    {
        if (adjacencyMatrix[vertexNumber][i] == 1)
        {
            if (colors[i] == -1)
            {
                q.push(i); // if neighbour was not painted pushing it to the queue
            }
            if (colors[i] >= 0)
            {
                if (neighboursColor == -1)
                {
                    colors[vertexNumber] = 1 - colors[i]; // painting vertex with opposite color to the color of neighbours
                    neighboursColor = colors[i];
                    continue;
                }
                if (neighboursColor != colors[i])
                {
                    colors[vertexNumber] = -2; // vertex can not be painted because different neighbours have different colors
                    return;
                }
            }
        }
    }
    if (neighboursColor == -1)
    {
        colors[vertexNumber] = 0; // painting with 0 if all neighbours haven't been painted yet
    }
}

int main()
{
    Graph* graph = new Graph;
    graph->ReadFromFile("input_task39.txt");
    graph->PaintGraph();
}
