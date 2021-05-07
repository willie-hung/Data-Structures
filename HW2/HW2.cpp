//Problem 13183
#include <iostream>
using namespace std;

class List;   

struct Node 
{
    int data;
    Node* next;

    Node(int a):data(a), next(0){};

    friend class List;
};

class List
{
private:
    Node *head;
            
public:
    List():head(0){};      
    void Insert(int a);    
    void Delete(int a);
    void Reverse();     
    void PrintList();          
};

void List::Insert(int a) 
{
    Node *newNode = new Node(a);
    Node *current = head, *previous = NULL;

    if (head == NULL)
    {
        head = newNode;
        return;
    }
        
    while (current->data < a)
    {
        previous = current;
        current = current->next;
        if (current == NULL) 
        {
            previous->next = newNode;
            return;
        }
    }
    
    if (current->data == a) 
        return;
        
    if (previous == NULL) 
    {
        newNode->next = current;
        head = newNode;
        return;
    }
    
    newNode->next = current;
    previous->next = newNode;
}

void List::Delete(int a)
{
    Node *current = head, *previous = NULL;
    
    if (head == NULL) 
    {
        return;
    } 
    
    if (current->data == a) 
    {
        head = current->next;
        delete current;
        current = NULL;
        return;
    }
    
    while (current != NULL)
    {
        if (current->data != a) 
        {
			previous = current;
			current = current->next;
		} 
        else 
		    break;
    }
    
    if (current == NULL)
    {
        return;
    }
    
    if(current->data == a && current->next != NULL) 
    {
        previous->next = current->next;
        delete current;
        current = NULL;
        return;
    } 
    
    else if (current->data == a)
    {
        previous->next = NULL;
        delete current;
        current = NULL;
        return;
    }
}

void List::Reverse()
{
	if (head == 0 || head->next == 0) 
		return;

	Node *previous = 0, *current = head, *preceding = head->next;
	
    while (preceding != 0) 
    {
		current->next = previous;
		previous = current;
		current = preceding;
		preceding = preceding->next;
	}
	current->next = previous;
	head = current;
}

void List::PrintList()
{
    if (head == NULL) 
        return;

    Node *current = head;

    while (current != NULL) 
    {                 
        cout << current->data << endl;
        current = current->next;
    }
}

int main(void) 
{
	List list;
	
    int num;
	string command;
	
    cin >> num;
	
    for (int i = 0; i < num; i++) 
    {
		cin >> command;
		if (command == "House") 
        {
			int a;
			cin >> a;
			list.Insert(a);
		} 
        
        else if (command == "Bomb") 
        {
			int a, d;
			cin >> a >> d;
			
            for (int i = a - d; i <= a + d; i++) 
            {
				list.Delete(i);
			}
		} 
        
        else if (command == "PrintFront")
        {
			cout << "PrintFront" << endl;
			list.PrintList();
		} 
        
        else if (command == "PrintEnd") 
        {
			cout << "PrintEnd" << endl;
			list.Reverse();
			list.PrintList();
			list.Reverse();
		}
	}
}
