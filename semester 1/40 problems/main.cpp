#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

class Heap
{
private:
	int heapSize;
	vector<int> heapVector;
	void maxHeapify(int index);
	void swap(int* a, int* b)
    {
		int c = *a;
		*a = *b;
		*b = c;
	}

public:
	Heap(vector<int> newVector)
    {
		heapVector = newVector;
		heapSize = newVector.size();
		for (int i((heapSize - 2) / 2); i >= 0; i--)
        {
			maxHeapify(i);
		}
	}
	Heap(int* newArray)
    {
		heapSize = sizeof(newArray) / sizeof(int);
		for (int i(0); i < heapSize; i++)
        {
			heapVector.push_back(newArray[i]);
		}
		for (int i((heapSize - 2) / 2); i >= 0; i--)
        {
			maxHeapify(i);
		}
	}
	void heapSort();
	void printVector();
};

void Heap::maxHeapify(int parent)
{
	int max = parent;
	int leftChild = 2 * parent + 1;
	int rightChild = 2 * parent + 2;

	if (leftChild < heapSize && heapVector[leftChild] > heapVector[max])
    {
		max = leftChild;
	}

	if (rightChild < heapSize && heapVector[rightChild] > heapVector[max])
    {
		max = rightChild;
	}

	// change root, put max into the root
	if (max != parent) {
		swap(&heapVector[max], &heapVector[parent]);
		maxHeapify(max);
	}
}

void Heap::heapSort()
{
	while (heapSize > 1)
    {
		swap(&heapVector[0], &heapVector[heapSize - 1]);
		heapSize--;
		maxHeapify(0);
	}
}

void Heap::printVector()
{
	for (int i(0); i < heapVector.size(); i++)
    {
		cout << heapVector[i] << " ";
	}
	cout << endl;
}

int main()
{
    srand(time(NULL));
	vector<int> newVector1;
	cout << "Randomly generated vector is: " << endl;
	for (int i(0); i < 10; i++)
    {
        newVector1.push_back(rand() % 100 + 1);
        cout << newVector1[i] << " ";
    }
    cout << endl;
	Heap heap1(newVector1);
	cout << "Heap: " << endl;
	heap1.printVector();
	heap1.heapSort();
	cout << "Sorted vector: " << endl;
	heap1.printVector();
}
