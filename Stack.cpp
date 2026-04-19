#include "Stack.h"
#include "Standard.h"

//Method Constructor
stackType::stackType()
{
    InitializeStack();
    ResetCounter();
}

//Method Destructor 
stackType::~stackType()
{
    //pop the stack while the stack is NOT empty
    while (!StackIsEmpty())
    {
        Pop();
    }
}

//Method InitializeStack
void stackType::InitializeStack()
{
    //set counter to 0
    _counter = 0;
}

//Method IncrementCounter
void stackType::IncrementCounter()
{
    //Add one to _counter
    _counter++;
}

//Method DecrementCounter
void stackType::DecrementCounter()
{
    //Subtract one from _counter
    _counter--;
}

//Method GetCounter
int stackType::GetCounter()
{
    //returning _counter
    return _counter;
}

void stackType::SetTop(node* newTop)
{
    //Assign pTop to NewTop
    pTop = newTop;
}

bool stackType::StackIsEmpty()
{
    //it is TRUE if pTop is NULL
    return (pTop == nullptr);
}

node* stackType::GetTop()
{
    return pTop;
}

void stackType::Push(node* pNewNode)
{
    // Defensive coding
    if (pNewNode == nullptr)
        return;

    // Link new node to current top
    pNewNode->pNext = pTop;

    // Move top to new node
    pTop = pNewNode;

    // Update counter
    IncrementCounter();
}

void stackType::Pop()
{
    //if the stack is not empty
    if (!StackIsEmpty())
    {
        //assign a temp variable to the top
        node* temp = pTop;

        //move the top pointer to the next node
        pTop = pTop->pNext;

        //Decrement the node counter
        DecrementCounter();

        //delete the temp node
        delete temp;
    }
}