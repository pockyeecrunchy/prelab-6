#ifndef STACK_H
#define STACK_H


// Structure: record
struct record
{
    char symbol;
    double number; //doing this for the extra credit. 
};

// Structure: node
struct node
{
    record data;
    node* pNext;
};

class stackType 

{
private:
    node* pTop;
    //Note: The counter should always reflect the number of nodes currently in the stack.
    int _counter;

    void InitializeStack();
    void ResetCounter();
    void SetTop(node* newTop);

public:
    stackType(); //Constructor
    ~stackType(); //Destructor

    bool StackIsEmpty();
    node* GetTop();

    void IncrementCounter();
    void DecrementCounter();
    int GetCounter();

    void Push(node* pNewNode);
    void Pop();

};

#endif 