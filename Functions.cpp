#include "Standard.h"
#include "Functions.h"


double PerformMath(char operation, double valueA, double valueB)
{
    //perform the switch statement on the operation character
    switch (operation)
    {

    //addition
    case '+':
        return valueA + valueB;

    //subtraction
    case '-':
        return valueA - valueB;

    //multiplication
    case '*':
        return valueA * valueB;

    //division
    case '/':
        return valueA / valueB;

    default:
        return 0xFFFFFFFFFFFF; // invalid result
    }
}

int ReturnPriority(char symbol)
{
    if (symbol == '(')
        return 0;

    if (symbol == '+' || symbol == '-')
        return 1;

    if (symbol == '*' || symbol == '/')
        return 2;
}

//close all files
void CloseFiles(ifstream& fin, ofstream& fout)
{
    fin.close();
    fout.close();
}

//close all files 
void CloseFiles(ifstream& extraCredit, ifstream& fin, ofstream& fout)
{
    extraCredit.close();
    fin.close();
    fout.close();
}

