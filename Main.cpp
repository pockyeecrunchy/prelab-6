#include "Functions.h"
#include "Stack.h"
#include "Standard.h"


int main() {
    //variables
    stackType stack;
    node* pTemp = nullptr;
    ifstream fin;
    ofstream fout;

    char tempChar;
    string data;

    //open the data files
    fin.open("Input.txt");
    fout.open("Output.txt");
    if (!fin)
    {
        //print the error message if there is an error opening the input file
        cout << "Error opening input file\n";
        return 1;
    }

    //File processing loop: read each line from the input file
    while (getline(fin, data))
    {
        // loop through each character in the current line
        for (int index = 0; index < data.length(); index++)
        {
            //stores current character 
            tempChar = data[index];

            if (tempChar == ' ')
                continue; //skip spaces

            //if the current symbol is a digit (0-9), output it directly
            if (tempChar >= '0' && tempChar <= '9')
            {
                fout << tempChar << " ";
            }

            //if the current character is '(', push it onto the stack
            else if (tempChar == '(')
            {
                pTemp = new node;                           // allocate new node
                pTemp->data.symbol = tempChar;              // store the symbol
                pTemp->pNext = nullptr;                     // initialize next pointer

                stack.Push(pTemp);                          // push onto stack  
            }

            // If the current character is ')', pop until '(' is found.
            else if (tempChar == ')')
            {
                //Pop and output operators until '(' is reached.
                while (!stack.StackIsEmpty() && stack.GetTop()->data.symbol != '(')
                {
                    //output operator
                    fout << stack.GetTop()->data.symbol << " ";

                    //remove from the stack
                    stack.Pop();
                }

                // remove '(' from the stack
                if (!stack.StackIsEmpty())
                {
                    stack.Pop(); // remove '('
                }
            }

            //if the current symbol is an operator (*, /, +, -)
            else if (tempChar == '+' || tempChar == '-' || tempChar == '*' || tempChar == '/')
            {
                //pop operators with higher or equal priority
                while (!stack.StackIsEmpty() &&
                    ReturnPriority(stack.GetTop()->data.symbol) >= ReturnPriority(tempChar))
                {
                    //output operator
                    fout << stack.GetTop()->data.symbol << " ";

                    //pop the top of the stack
                    stack.Pop();

                }

                pTemp = new node;                           // allocate new node
                pTemp->data.symbol = tempChar;              // store operator
                pTemp->pNext = nullptr;                     // initialize new pointer

                stack.Push(pTemp);                          // push operator onto stack
            }
        }
        
        // After processing the line, pop all remaining operators from the stack
        while (!stack.StackIsEmpty())
        {
            fout << stack.GetTop()->data.symbol << " ";     // output remaining operator
            stack.Pop();                                    // remove from the stack
        }

        fout << endl; //print the enter key!
    }

    //close the output file 
    CloseFiles(fin, fout);

    // ---------------- EXTRA CREDIT ---------------- //

    // (1) Re-open files
    // (2) Read postfix + original lines
    // (3) Evaluate using stack
    // (4) Write to ExtraCreditOutput.txt

    // ---------------------------------------------- //

    ifstream extraCredit;
    ifstream originalFile;
    ofstream extraOut;

    extraCredit.open("Output.txt");
    originalFile.open("Input.txt");
    extraOut.open("ExtraCreditOutput.txt");

    if (!extraCredit || !originalFile)
    {
        cout << "There is an error opening the extra credit files!\n";
        return 1;
    }

    double tempA, tempB, tempAnswer;
    string originalLine;

    int lineNumber = 1;

    while (getline(originalFile, originalLine) && getline(extraCredit, data))
    {
        extraOut << "Line " << lineNumber << ": " << originalLine << endl;
        extraOut << "ANSWER = ";

        for (int index = 0; index < data.length(); index++)
        {
            tempChar = data[index];

            if (tempChar == ' ')
                continue;

            if (tempChar >= '0' && tempChar <= '9')
            {
                pTemp = new node;
                pTemp->data.number = tempChar - '0';
                pTemp->pNext = nullptr;

                stack.Push(pTemp);
            }

            else
            {

                tempB = stack.GetTop()->data.number;
                stack.Pop();

                tempA = stack.GetTop()->data.number;
                stack.Pop();

                tempAnswer = PerformMath(tempChar, tempA, tempB);

                pTemp = new node;
                pTemp->data.number = tempAnswer;
                pTemp->pNext = nullptr;

                stack.Push(pTemp);
            }

        }

        if (!stack.StackIsEmpty())
        {
            extraOut << stack.GetTop()->data.number << endl << endl;
            stack.Pop();
        }

        lineNumber++;
    }

    CloseFiles(extraCredit, originalFile, extraOut);

    return 0;
}

