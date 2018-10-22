/*Ñîçäàòü îäíîñâÿçíûé ëèíåéíûé ñïèñîê (ó êàæäîãî óçëà 1 èíôîðì. ïîëå òèïà
Integer), ñ âîçìîæíîñòüþ äîáàâëÿòü è óäàëÿòü óçëû.
Ïîñëå çàâåðøåíèÿ ðåäàêòèðîâàíèÿ ñïèñêà çàïðîñèòü ÷èñëî N è ðàçáèòü ñïèñîê íà
äâà äðóãèõ, íå ìåíÿÿ ðàñïîëîæåíèÿ ýëåìåíòîâ â ïàìÿòè, ñëåäóþùèì îáðàçîì:
åñëè çíà÷åíèå èíôîðì. ïîëÿ óçëà > N, âêëþ÷èòü åãî â 1 ñïèñîê, èíà÷å âêëþ÷èòü
åãî âî 2 ñïèñîê.
Ïîñëå çàâåðøåíèÿ ðàáîòû âñå ñïèñêè ðàçðóøèòü.*/

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

void AddNode(List* list, int data)
{
    Node* nodeToAdd = CreateNode(data);
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

void ShowList(List* list)
{
    cout << "[";
    Node* current = list->Begin;
    while (current)
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
        AddNode(result, rand() % 100);
    }
    return result;
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

void DivideListOn2Sublists(List* someList)
{
    int divider;
    cout << "Enter N: ";
    cin >> divider;
    Node* current = someList->Begin;
    List* sublist1 = CreateEmptyList();
    List* sublist2 = CreateEmptyList();
    while (current)
    {
        if (current->data < divider)
        {
            AddNode(sublist1, current->data);
        }
        else
        {
            AddNode(sublist2, current->data);
        }
        current = current->next;
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
    cout << "Randomly generated list is: ";
    ShowList(randomList);
    DivideListOn2Sublists(randomList);
    delete randomList;
}

int main()
{
    srand(time(0));
    SolveTask();
}
