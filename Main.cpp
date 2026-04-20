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

    // Open the postfix, original input, output files for extra credit result
    extraCredit.open("Output.txt");
    originalFile.open("Input.txt");
    extraOut.open("ExtraCreditOutput.txt");

    // verify if input files opened successfully
    if (!extraCredit || !originalFile)
    {
        cout << "There is an error opening the extra credit files!\n";
        return 1;
    }

    // Variables to store operands and computed result using temp
    double tempA, tempB, tempAnswer;
    string originalLine;

    // Line counter for labeling output
    int lineNumber = 1;

    // Read corresponding lines from original and postfix files
    while (getline(originalFile, originalLine) && getline(extraCredit, data))
    {
        // Output the original infix expression with line number
        extraOut << "Line " << lineNumber << ": " << originalLine << endl;

        // Prepare to output evaluated result
        extraOut << "ANSWER = ";

        // Loop through each character in the postfix expression
        for (int index = 0; index < data.length(); index++)
        {
            tempChar = data[index];                         // stores current character 

            if (tempChar == ' ')
                continue;                                   // skip the space!

            if (tempChar >= '0' && tempChar <= '9')
            {
                pTemp = new node;                           // Allocate new node
                pTemp->data.number = tempChar - '0';        // Convert char to integer value
                pTemp->pNext = nullptr;                     // Initialize next pointer 

                stack.Push(pTemp);                          // Push the number into stack!
            }

            // If the character is an operator, please perform the calculation
            else
            {
                // Pop top value (right operand)
                tempB = stack.GetTop()->data.number;
                stack.Pop();

                // Pop next value (left operand)
                tempA = stack.GetTop()->data.number;
                stack.Pop();

                // Perform the operation using the two operands
                tempAnswer = PerformMath(tempChar, tempA, tempB);

                // Create new node with result
                pTemp = new node;
                pTemp->data.number = tempAnswer;
                pTemp->pNext = nullptr;

                // We will push result back onto stack
                stack.Push(pTemp);
            }

        }

        if (!stack.StackIsEmpty())
        {
            //This is the output result
            extraOut << stack.GetTop()->data.number << endl << endl;    
            stack.Pop();                                     // Remove result from stack
        }

        lineNumber++;                                        // Increment line counter
    }

    // Close all extra credit file streams
    CloseFiles(extraCredit, originalFile, extraOut);

    return 0;
}

