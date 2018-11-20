/*Реализовать работу динамической структуры: ОЧЕРЕДЬ
Добавление элемента·Удаление·Сортировка: В работе использовать два метода
сортировки: быструю и вставками. Сравнить эффективность.*/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

struct Node
{
    int data;
    Node* next;
    Node* prev;
};

struct Queue
{
    int Size;
    Node* Head;
    Node* Tail;
};

Queue* CreateEmpty()
{
    Queue* result = new Queue;
    result->Head = NULL;
    result->Tail = NULL;
    result->Size = 0;
    return result;
}

void Push(Queue* someQueue, int data)
{
    Node* toPush = new Node;
    toPush->data = data;
    toPush->prev = NULL;
    if (someQueue->Head && someQueue->Tail)
    {
        someQueue->Tail->prev = toPush;
        toPush->next = someQueue->Tail;
    }
    else
    {
        toPush->next = NULL;
        someQueue->Head = toPush;
    }
    someQueue->Tail = toPush;
    someQueue->Size++;
}

Node* Remove(Queue* someQueue)
{
    if (someQueue->Head && someQueue->Tail)
    {
        Node* toRemove = someQueue->Head;
        someQueue->Head = someQueue->Head->prev;
        someQueue->Head->next = NULL;
        toRemove->prev = NULL;
        someQueue->Size--;
        return toRemove;
    }
    else
    {
        return NULL;
    }
}

void ShowQueue(Queue* queueToShow)
{
    cout << "[";
    Node* current = queueToShow->Tail;
    while (current)
    {
        cout << current->data;
        if (current->next != NULL)
        {
            cout << ", ";
        }
        current = current->next;
    }
    cout << "]" << endl;
}

void InsertionSort(Queue* queueToSort)
{
    Node* current = queueToSort->Head;
    while (current)
    {
        Node* innerCurrent = current;
        while (innerCurrent->next && innerCurrent->data > innerCurrent->next->data)
        {
            swap(innerCurrent->data, innerCurrent->next->data);
            innerCurrent = innerCurrent->next;
        }
        current = current->prev;
    }
}

Node* At(Queue* someQueue, int number)
{
    Node* result = someQueue->Tail;
    int counter = 0;
    while (counter < number)
    {
        counter++;
        result = result->next;
    }
    return result;
}

void QuickSort(Queue* queueToSort, int low, int high)
{
    int l = low;
    int h = high;
    Node* currentLow = At(queueToSort, low);
    Node* currentHigh = At(queueToSort, high);
    int pivot = At(queueToSort, (low + high) / 2)->data;
    do
    {
        while (currentLow->data < pivot)
        {
            l++;
            currentLow = currentLow->next;
            if (l == high)
            {
                break;
            }
        }
        while (currentHigh->data > pivot)
        {
            h--;
            currentHigh = currentHigh->prev;
            if (h == low)
            {
                break;
            }
        }
        if (l <= h)
        {
            swap(currentHigh->data, currentLow->data);
            l++;
            currentLow = currentLow->next;
            h--;
            currentHigh = currentHigh->prev;
        }
    }
    while (l < h);
    if (low < h)
    {
        QuickSort(queueToSort, low, h);
    }
    if (l < high)
    {
        QuickSort(queueToSort, l, high);
    }

}

Queue* CreateRandomQueue(int size)
{
    Queue* result = CreateEmpty();
    for (int i = 0; i < size; i++)
    {
        Push(result, rand() % 200 - 100);
    }
    return result;
}

void CompareEfficiency()
{
    Queue* veryLongQueue = CreateRandomQueue(10000);
    clock_t startTime = clock();
    InsertionSort(veryLongQueue);
    clock_t endTime = clock();
    double deltaTime = double(endTime - startTime) / CLOCKS_PER_SEC;
    cout << "Time of InsertionSort: " << deltaTime << endl;


    veryLongQueue = CreateRandomQueue(10000);
    startTime = clock();
    QuickSort(veryLongQueue, 0, veryLongQueue->Size - 1);
    endTime = clock();
    deltaTime = double(endTime - startTime) / CLOCKS_PER_SEC;
    cout << "Time of QuickSort: " << deltaTime << endl;
}

void TestFunction()
{
    cout << "Randomly generated queue is: " << endl;;
    Queue* randomQueue = CreateRandomQueue(10);
    ShowQueue(randomQueue);

    cout << "Removing last element: " << endl;
    Remove(randomQueue);
    ShowQueue(randomQueue);

    cout << "Sorting elements in queue with Insertion Sort: " << endl;
    InsertionSort(randomQueue);
    ShowQueue(randomQueue);

    cout << "Randomly generated queue is: " << endl;
    randomQueue = CreateRandomQueue(10);
    ShowQueue(randomQueue);

    cout << "Sorting elements in queue with QuickSort: " << endl;
    QuickSort(randomQueue, 0, randomQueue->Size - 1);
    ShowQueue(randomQueue);

    CompareEfficiency();
}

int main()
{
    srand(time(0));
    TestFunction();
}
