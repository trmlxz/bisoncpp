/*
                              demo.cc
*/

#include <iostream>

#include "parser/Parser.h"

using namespace std;

int main(int argc)
{
    cout << "Enter lines containing  NR + NR =\n"
        "The numbers should be integral numbers.\n"
        "Other non-empty lines should result in a `syntax error'\n"
        "Blanks and tabs are ignored. Use q, ^c or ^d to end the program\n"
        "Use any program argument to view parser debug output\n";

    Parser parser;

    parser.setDebug(argc > 1);

    cout << "Parser returns " << parser.parse() << endl;
    return 0;
}




