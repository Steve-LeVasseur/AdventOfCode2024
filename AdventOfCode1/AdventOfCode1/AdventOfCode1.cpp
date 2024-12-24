// AdventOfCode1.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Contains code for Part 1 and 2 of Advent of Code 2024 Day 1
// Steven LeVasseur

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

// USER INPUTS
const int length = 1000;
string fileName = "inputList.txt";
bool partOne = false;


int listFirst[length];
int listSecond[length];


void countNumLinesInFile(string inputList) 
{
    // Open the text file
    ifstream inputFile(inputList);  // Opening the file named "test.txt" for reading

    if (inputFile.is_open()) 
    {  // Checking if the file was successfully opened
        string line;  // Declaring a string variable to store each line of text
        int lineCount = 0;  // Initializing a variable to count lines

        while (getline(inputFile, line)) 
        {  // Loop through each line in the file
            lineCount++;  // Incrementing line count for each line read
        }

        inputFile.close();  // Closing the file after counting lines

        cout << "Number of lines in the file: " << lineCount << endl;  // Outputting the total line count
    }
    else
    {
        cout << "Failed to open the file." << endl;  // Display an error message if file opening failed
    }
}

void separateLinesInFile(string inputList, int listSize) 
{
    // Open the text file
    ifstream inputFile(inputList);
    char first[10];
    char second[10];

    if (inputFile.is_open())
    {  // Checking if the file was successfully opened
        string line;  // Declaring a string variable to store each line of text

        for (int index = 0; index < (listSize); index++) 
        {
            getline(inputFile, line);
            //cout << line << endl;
            stringstream ss(line);
            ss >> first >> ws >> second;
            //cout << first << " " << second << endl;
            listFirst[index] = stoi(first);
            listSecond[index] = stoi(second);
            //cout << listFirst[index] << " and " << listSecond[index] << endl;
        }

        inputFile.close();  // Closing the file
    }
    else
    {
        cout << "Failed to open the file." << endl;  // Display an error message if file opening failed
    }
}

int findDifference(int x, int y) 
{
    if (x >= y)
    {
        return x - y;
    }
    else
        return y - x;
}

int findSimilarity(int x) 
{
    int similarity = 0;
    for (int i = 0; i < length; i++) 
    {
        if (listSecond[i] == x) 
        {
            similarity++;
        }
        if (listSecond[i] > x) 
        {
            return similarity*x;
        }
    }
    return similarity*x;
}



int main()
{
    cout << "Hello World!\n";

    int diffSum = 0;
    int similarSum = 0;
    //countNumLinesInFile("inputTest.txt");
    separateLinesInFile(fileName, length);
    int n = sizeof(listFirst) / sizeof(listFirst[0]);
    sort(listFirst, listFirst + n);
    n = sizeof(listSecond) / sizeof(listSecond[0]);
    sort(listSecond, listSecond + n);

    if (partOne)
    {
        for (int i = 0; i < length; i++)
        {
            cout << listFirst[i] << "  " << listSecond[i] << endl;
            cout << "Diff of: " << findDifference(listFirst[i], listSecond[i]) << endl;
            diffSum += findDifference(listFirst[i], listSecond[i]);
        }
        cout << "And the answer is..." << endl << diffSum << endl;
    }
    else 
    {
        for (int i = 0; i < length; i++) 
        {
            cout << listFirst[i] << "  " << listSecond[i] << endl;
            cout << "Similarity of: " << findSimilarity(listFirst[i]) << endl;
            similarSum += findSimilarity(listFirst[i]);
        }

        cout << "And the answer is..." << endl << similarSum << endl;
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
