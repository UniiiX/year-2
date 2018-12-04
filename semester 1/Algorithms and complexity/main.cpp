#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

class Heap
{
private:
    const int dimension = 5;
	int heapSize;
	vector<int> heapVector;
	void maxHeapify(int parent);
	int getMax(int parent);
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
		for (int i(heapSize / dimension - 1); i >= 0; i--)
        {
			maxHeapify(i);
		}
	}
	int extractMax();
	void insert(int data);
	void increaseKey(int key, int increment);
	void heapSort();
	void printVector();
};

int Heap::getMax(int parent)
{
    int result = parent;
	vector<int> children(dimension);
	for (int i(0); i < dimension; i++)
    {
        children[i] = dimension * parent + (i + 1);
        if (children[i] < heapSize && heapVector[children[i]] > heapVector[result])
        {
            result = children[i];
        }
    }
    return result;
}

void Heap::maxHeapify(int parent)
{
    int max = getMax(parent);

	// change root, put max into the root
	if (max != parent)
    {
		swap(&heapVector[max], &heapVector[parent]);
		maxHeapify(max);
	}
}

void Heap::heapSort()
{
	while (heapSize > 1)
    {
		extractMax();
	}
}

int Heap::extractMax()
{
    swap(&heapVector[0], &heapVector[heapSize - 1]);
    heapSize--;
    maxHeapify(0);
    return heapVector.at(heapSize - 1);
}

void Heap::insert(int key)
{
    heapVector.insert(heapVector.begin(), key);
    heapSize++;
    maxHeapify(0);
}

void Heap::increaseKey(int child, int increment)
{
    int parent = child / dimension;
    for (int i(0); i < heapSize; i++)
    {
        if (child == heapVector.at(i))
        {
            heapVector.at(i) += increment;
            while (child > parent)
            {
                maxHeapify(parent);
                child = parent;
                parent = parent / dimension;
            }
        }
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

vector<int> generateRandomVector(int size)
{
    cout << "Randomly generated vector is: " << endl;
    vector<int> result;
    for (int i(0); i < size; i++)
    {
        result.push_back(rand() % 100 + 1);
        cout << result[i] << " ";
    }
    cout << endl;
    return result;
}

int main()
{
    srand(time(NULL));
    const int size = 15;
	vector<int> newVector = generateRandomVector(size);
	Heap heap1(newVector);
	cout << "Heap: " << endl;
	heap1.printVector();

	cout << "Extracting max: " << endl;
	heap1.extractMax();
	heap1.printVector();

	int key = rand() % 70 + 30;
	cout << "Inserting key " << key << endl;
	heap1.insert(key);
	heap1.printVector();

	int increment = rand() % 40;
	cout << "Inserting key " << key  << " by " << increment << endl;
	heap1.increaseKey(key, increment);
	heap1.printVector();

	heap1.heapSort();
	cout << "Sorted vector: " << endl;
	heap1.printVector();
}
