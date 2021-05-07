//Question13144
#include <iostream>
#include <string>
using namespace std;

//Class
template <class T>
class BaseStack
{
private:
    T *_stack;
    int _top;
    int capacity;

public:
    BaseStack() : _top(-1), capacity(10)
    {
        _stack = new T[capacity];
    }

    ~BaseStack()
    {
        delete[] _stack;
    }

    bool empty()
    {
        return (_top == -1);
    }

    int size()
    {
        return _top + 1;
    }

    T &top()
    {
        if (empty())
            throw "The stack is empty!";
        else
            return _stack[_top];
    }

    void push(const T &item)
    {
        //double the capacity
        if (_top == capacity - 1)
        {
            capacity *= 2;
            T *newStack = new T[capacity];

            for (int i = 0; i < (capacity / 2); i++)
            {
                newStack[i] = _stack[i];
            }

            delete[] _stack;
            _stack = newStack;
        }
        _stack[++_top] = item;
    }

    void pop()
    {
        if (empty())
            throw "The stack is empty!";
        else
            _top--;
    }
};

template <class T>
class BaseQueue
{
private:
    T *_queue;
    int _front, _rear;
    int capacity;

public:
    BaseQueue() : _front(0), _rear(0), capacity(100)
    {
        _queue = new T[capacity];
    }

    ~BaseQueue()
    {
        delete[] _queue;
    }

    bool empty()
    {
        return (_front == _rear);
    }

    int size()
    {
        if (_rear >= _front)
            return (_rear - _front);
        else
            return (capacity - (_front - _rear));
    }

    T &front()
    {
        if (empty())
            throw "The queue is empty!";
        else
            return _queue[(_front + 1) % capacity];
    }

    void push(const T &item)
    {
        // if the queue is full -> double the capacity
        if ((_rear + 1) % capacity == _front || ((_rear == capacity - 1) && (_front == 0)))
        {
            T *newQueue = new T[capacity * 2];

            int j = _front;

            for (int i = 1; i <= size(); i++)
            {
                newQueue[i] = _queue[++j % capacity];
            }

            _front = 0;
            _rear = size();
            capacity *= 2;

            delete[] _queue;
            _queue = newQueue;
        }

        // Regular push
        _rear = (_rear + 1) % capacity;
        _queue[_rear] = item;
    }

    void pop()
    {
        if (empty())
            throw "The queue is empty!";

        _front = (_front + 1) % capacity;
        _queue[_front].~T();
    }
};

//Construct
BaseQueue<char> slot[100]; //Don't change
BaseStack<string> storage;

//Function
void insert(int L)
{
    int num, count = 1;
    string word;

    cin >> num >> word;

    for (int i = num; i < (num + word.length()); i++)
    {
        if (slot[i].size() >= count)
            count = slot[i].size() + 1;
    }

    for (int i = num; i < (num + word.length()); i++)
    {
        while (slot[i].size() + 1 != count)
        {
            slot[i].push('@');
        }
        slot[i].push(word[i - num]);
    }
}

string first_row(int L, bool print = false)
{
    string bottom = "";

    cout << "BOTTOM_ROW" << endl;

    for (int i = 0; i < L; i++)
    {
        if (slot[i].empty())
            bottom.append("~");
        else
            bottom.append(1, slot[i].front());
    }

    cout << bottom << endl;

    return bottom;
}

void query(int L)
{
    string substr, str = "";

    //Catch bottom row(str)
    for (int i = 0; i < L; i++)
    {
        if (slot[i].empty())
            str.append(" ");
        else
            str.append(1, slot[i].front());
    }

    cin >> substr;

    //Identify whether substr belongs to (or equals to) str
    size_t find = str.find(substr);
    int len = substr.length();

    //Detect
    if (find != string::npos)
    {
        storage.push(substr);

        for (int i = find; i < find + substr.length(); i++)
            slot[i].pop();
    }
}

void flush()
{
    cout << "FLUSH" << endl;

    while (!storage.empty())
    {
        cout << storage.top() << endl;
        storage.pop();
    }
}

void reset(int L)
{
    //Flush queue
    for (int i = 0; i < L; i++)
    {
        while (!slot[i].empty())
            slot[i].pop();
    }

    //Flush stack
    while (!storage.empty())
        storage.pop();
}

int main(void)
{
    int L, C;
    string command;

    cin >> L >> C;

    for (int i = 0; i < C; i++)
    {
        cin >> command;

        if (command == "INSERT")
        {
            insert(L);
        }
        else if (command == "BOTTOM_ROW")
        {
            first_row(L, true);
        }
        else if (command == "QUERY")
        {
            query(L);
        }
        else if (command == "FLUSH")
        {
            flush();
        }
        else if (command == "RESET")
        {
            reset(L);
        }
    }
}