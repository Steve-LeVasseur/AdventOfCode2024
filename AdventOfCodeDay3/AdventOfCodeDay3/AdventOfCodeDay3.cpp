// AdventOfCodeDay3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <regex>

using namespace std;


// USER INPUTS
string fileName = "inputList.txt";
bool partOne = false;



string line; 
int answer = 0;
bool allowed = true;

void regexSearch() 
{
    string s = "hithere";

    if (partOne)
        s = "mul\\(([0-9]+),([0-9]+)\\)";
    else
        s = "mul\\(([0-9]+),([0-9]+)\\)|do\\(\\)|don't\\(\\)";

    regex r(s);

    // flag type for determining the matching behavior
// here it is for matches on 'string' objects
    smatch m;

    int i = 1;
    while (regex_search(line, m, r)) {
        cout << "\nMatched string is " << m.str(0) << endl
            << "and it is found at position "
            << m.position(0) << endl;
        i++;
        //cout << m.str(1) << " " << m.str(2) << endl;

        if (partOne) 
        {
            answer += stoi(m.str(1)) * stoi(m.str(2));
        }
        else
        {
            if (m.str(0).find("don") != string::npos)
                allowed = false;
            else if (m.str(0).find("do") != string::npos)
                allowed = true;
            else if (allowed)
                answer += stoi(m.str(1)) * stoi(m.str(2));
        }


        // suffix to find the rest of the string.
        line = m.suffix().str();
    }
}


int main()
{
    std::cout << "Hello World!\n";


    ifstream inputFile(fileName);
    if (inputFile.is_open()) 
    {
        while (getline(inputFile, line))
        {
            cout << line << endl;
            regexSearch();
        }
        
        

        

        cout << "And the answer is..." << endl << answer << endl;
    }
}

