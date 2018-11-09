/*Создать односвязный линейный список (у каждого узла 1 информ. поле типа
Integer), с возможностью добавлять и удалять узлы.
После завершения редактирования списка запросить число N и разбить список на
два других, не меняя расположения элементов в памяти, следующим образом:
если значение информ. поля узла > N, включить его в 1 список, иначе включить
его во 2 список.
После завершения работы все списки разрушить.*/

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

struct Node
{
    int data;
    Node* next;
};

struct List
{
    Node* Begin;
    Node* End;
};

Node* CreateNode(int data)
{
    Node* result = new Node;
    result->data = data;
    result->next = NULL;
    return result;
}

List* CreateEmptyList()
{
    List* result = new List;
    result->Begin = NULL;
    result->End = NULL;
    return result;
}

void AddNode(List* list, Node* nodeToAdd)
{
    if (list->Begin == NULL)
    {
        list->Begin = nodeToAdd;
        list->End = nodeToAdd;
    }
    else
    {
        list->End->next = nodeToAdd;
        list->End = nodeToAdd;
    }
    nodeToAdd->next = NULL;
}

void AddData(List* list, int data)
{
    Node* nodeToAdd = CreateNode(data);
    AddNode(list, nodeToAdd);
}

void ShowList(List* list)
{
    cout << "[";
    Node* current = list->Begin;
    while (current != NULL)
    {
        cout << current->data;
        if (current->next)
        {
            cout << ", ";
        }
        current = current->next;
    }
    cout << "]" << endl;
}

List* CreateRandomList()
{
    List* result = CreateEmptyList();
    for (int i = 0; i < 10; i++)
    {
        AddData(result, rand() % 100);
    }
    return result;
}

void DeleteNode(List* list, Node* toDelete)
{
    Node* current = list->Begin;
    if (list->Begin == toDelete)
    {
        list->Begin = list->Begin->next;
    }
    while (current->next != toDelete)
    {
        current = current->next;
    }

    if (toDelete->next)
    {
        current->next = toDelete->next;
    }
    else
    {
        list->End = current;
        current->next = NULL;
    }
    delete toDelete;
}

void DeleteList(List* listToDelete)
{
    Node* current = listToDelete->Begin->next;
    Node* previous = listToDelete->Begin;
    while (current)
    {
        delete previous;
        previous = current;
        current = current->next;
    }
    delete listToDelete;
}

void DivideListInto2Sublists(List* someList)
{
    int divider;
    cout << "Enter N: ";
    cin >> divider;
    Node* current = someList->Begin;
    List* sublist1 = CreateEmptyList();
    List* sublist2 = CreateEmptyList();
    while (current)
    {
        Node* next = current->next;
        if (current->data < divider)
        {
            AddNode(sublist1, current);
        }
        else
        {
            AddNode(sublist2, current);
        }
        current = next;
    }
    cout << "First sublist:";
    ShowList(sublist1);
    cout << "Second sublist:";
    ShowList(sublist2);
    DeleteList(sublist1);
    DeleteList(sublist2);
}

void SolveTask()
{

    List* randomList = CreateRandomList();
    cout << "Randomly generated list is: " << endl;
    ShowList(randomList);

    cout << "Adding number 100 to the end of the list: " << endl;
    AddData(randomList, 100);
    ShowList(randomList);

    cout << "Removing last element: " << endl;
    DeleteNode(randomList, randomList->End);
    ShowList(randomList);

    cout << "Dividing list into 2 sublists: " << endl;
    DivideListInto2Sublists(randomList);
    DeleteList(randomList);
}

int main()
{
    srand(time(0));
    SolveTask();
}
