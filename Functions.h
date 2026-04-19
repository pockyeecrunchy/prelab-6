#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Standard.h"

// Performs math operation (+, -, *, /)
double PerformMath(char operation, double valueA, double valueB);

// Returns operator priority
int ReturnPriority(char symbol);

// Close input and output files
void CloseFiles(ifstream& fin, ofstream& fout);

// Overloaded version for extra credit
void CloseFiles(ifstream& extraCredit, ifstream& fin, ofstream& fout);

#endif 


