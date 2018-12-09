#include <iostream>
#include <vector>

using namespace std;

// A class that represents an directed graph
class Graph
{
private:

    class Edge
    {
    public:
        int from;
        int to;
        Edge(int from, int to) {
            this->from = from;
            this->to = to;
        }
    };

	int verticesCount;    // count of vertices
	vector <vector<int> > adjStruct;    // adjacency structure for graph
	vector <vector<int> > adjStructTransposed;    // adjacency structure for transposed graph
	vector<bool> visited; // indicator whether the vertex has been visited or not (is used for DFS)

	// depth-first search
    void DFS(int currentVertex, const vector <vector<int> > &graph, vector<int> &result)
    {
        visited[currentVertex] = true;
        for (int i = 0; i < graph[currentVertex].size(); i++)
        {
            int neighbour = graph[currentVertex][i];
            if (!visited[neighbour])
            {
                DFS(neighbour, graph, result);
            }
        }
        result.push_back(currentVertex);
    }

    // prints vector from the end to begin is
    // used to print vertices in SCC in the same
    // exact order as they were visited by DFS
    void printSCC(const vector<int> &component)
    {
        for (int i = component.size() - 1; i >= 0; i--)
        {
            cout << component[i];
            if (i != 0)
            {
                cout << " -- ";
            }
        }
        cout << endl;
    }

//-----------------------------------------------------------------------------------------------------------

public:
	Graph(int verticesCount) {  // Constructor
		this->verticesCount = verticesCount;
		adjStruct.reserve(verticesCount);
		adjStructTransposed.reserve(verticesCount);
		visited.assign(verticesCount, false);
	}

	void addEdge(int from, int to) {   // function to add an edge to graph
		adjStruct[from].push_back(to); // adding directed edge to graph
		adjStructTransposed[to].push_back(from); // adding edge with opposite direction to transposed graph
	}

	// Korasaju-Sharir's algorithm of finding SCCs
	void findSCCs()
	{
	    vector<int> order; // vertices sorted by DFS exit time in ascending order
	    vector<int> component; // stores all vertices in the same strongly connected component

	    // getting order
	    for (int i = 0; i < verticesCount; i++)
        {
            if (!visited[i])
            {
                DFS(i, adjStruct, order);
            }
        }

        // now we can use DFS for transposed graph using found order
        // thus DFS will return only vertices that are in the same SCC
        visited.assign(verticesCount, false);
        for (int i = 0; i < verticesCount; i++)
        {
            int currentVertex = order[verticesCount - i - 1];
            if (!visited[currentVertex])
            {
                DFS(currentVertex, adjStructTransposed, component);
                printSCC(component);
                component.clear();
            }
        }
	}
};

//-----------------------------------------------------------------------------------------------------------

int main()
{
	Graph g(12);
	g.addEdge(0, 1); g.addEdge(1, 0);
	g.addEdge(1, 2); g.addEdge(2, 1);
	g.addEdge(1, 3); g.addEdge(3, 1);
	g.addEdge(2, 3); g.addEdge(3, 2);
	g.addEdge(2, 4); g.addEdge(4, 2);
	g.addEdge(3, 4); g.addEdge(4, 3);
	g.addEdge(1, 5); g.addEdge(5, 1);
	g.addEdge(0, 6); g.addEdge(6, 0);
	g.addEdge(5, 6); g.addEdge(6, 5);
	g.addEdge(5, 7); g.addEdge(7, 5);
	g.addEdge(5, 8); g.addEdge(8, 5);
	g.addEdge(7, 8); g.addEdge(8, 7);
	g.addEdge(8, 9); g.addEdge(9, 8);
	g.addEdge(10, 11); g.addEdge(11, 10);
    g.findSCCs();
	return 0;
}
