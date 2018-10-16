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
    void PaintVertex(int vertexNumber, int* colors, int size);
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
    int size = adjacencyMatrix.size();
    int* colors = new int[size];
    for (int i = 0; i < size; i++)
    {
        colors[i] = -1; // -2 ~ can't be painted; -1 ~ not painted yet; 0,1 ~ painted
    }

    for (int i = 0; i < size; i++)
    {
        PaintVertex(i, colors, size);
        if (colors[i] == -2)
        {
            cout << "Can't paint graph" << endl;
            delete[] colors;
            return;
        }
    }
    cout << "Painted graph is: " << endl;
    for (int i = 0; i < size; i++)
    {
        cout << i + 1 << " : " << colors[i] << endl;
    }
    delete[] colors;
}

void Graph::PaintVertex(int vertexNumber, int* colors, int size)
{
    int neighboursColor = -1;
    for (int i = 0; i < size; i++)
    {
        if (adjacencyMatrix[vertexNumber][i] == 1 && colors[i] >= 0)
        {
            if (neighboursColor == -1)
            {
                colors[vertexNumber] = 1 - colors[i];
                neighboursColor = colors[i];
                continue;
            }
            if (neighboursColor != colors[i])
            {
                colors[vertexNumber] = -2; // vertex can not be painted
                cout << "result = -2; i = " << i << endl;
                return;
            }
        }

    }
    if (neighboursColor == -1)
    {
        colors[vertexNumber] = 1;
    }
}

int main()
{
    Graph* graph = new Graph;
    graph->ReadFromFile("input_task39.txt");
    graph->PaintGraph();
}
