// AdventOfCodeDay2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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

int currentReport[20];
int originalReport[20];
string line;
int currentReportLength = 0;

void countNumLinesInFile(string inputList)
{
    // Open the text file
    ifstream inputFile(inputList);  // Opening the file named "test.txt" for reading

    if (inputFile.is_open())
    {  // Checking if the file was successfully opened
        string line2;  // Declaring a string variable to store each line of text
        int lineCount = 0;  // Initializing a variable to count lines

        while (getline(inputFile, line2))
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

void readLine(string line) 
{
    

    stringstream ss(line);
    string temp;
    int index = 0;
    currentReportLength = 0;
    //ss >> first >> ws >> second;
    while (getline(ss, temp, ' ')) 
    {
        currentReportLength++;
        currentReport[index] = stoi(temp);
        //cout << currentReport[index] << endl;
        index++;
    }
    //cout << line << endl;
}

bool checkIncOrDec()
{
    if (currentReport[0] > currentReport[1]) // decreasing
    {
        for (int index = 1; index < currentReportLength; index++) 
        {
            if (currentReport[index - 1] > currentReport[index]) 
            {
                continue;
            }
            else 
            {
                return 0; // UNSAFE
            }
        }
        return 1; // SAFE
    }

    else if (currentReport[0] < currentReport[1]) // increasing
    {
        for (int index = 1; index < currentReportLength; index++)
        {
            if (currentReport[index - 1] < currentReport[index])
            {
                continue;
            }
            else
            {
                return 0; // UNSAFE
            }
        }
        return 1; // SAFE
    }
    else // values are the same
    {
        return 0; // UNSAFE
    }
}

bool checkAdjacentDiff() 
{
    int diff = 0;
    for (int index = 0; index < (currentReportLength-1); index++) 
    {
        diff = currentReport[index + 1] - currentReport[index];
        if ( (diff > 3) || (diff < -3) || (diff==0) ) // violates adjacent rules
        {
            return 0; // UNSAFE
        }
    }
    return 1; // SAFE
}

bool checkSafe() 
{
    if (!checkIncOrDec()) // Failed increasing or decreasing check
        return false;

    if (!checkAdjacentDiff()) // Failed adjacent values check
        return false;

    return true;
}


int main()
{

    std::cout << "Hello World!\n";
    countNumLinesInFile(fileName);

    int safeCounter = 0;

    ifstream inputFile(fileName);
    if (inputFile.is_open())
    {
        for (int index = 0; index < length; index++) 
        {
            getline(inputFile, line);
            cout << line << endl;
            readLine(line);

            if (partOne) 
            {
                if (checkSafe())
                {
                    safeCounter++;
                    cout << "SAFE" << endl;
                }
                else
                {
                    cout << "UNSAFE" << endl;
                }
            }
            else // part 2 
            {
                // instead of just checking the report as given. Must check every version of the report missing 1 level
                // instead of just checking 1 2 3 4 5
                // must also check 2 3 4 5 --- 1 3 4 5 --- 1 2 4 5 --- 1 2 3 5 --- 1 2 3 4

                if (checkSafe())
                {
                    safeCounter++;
                    cout << "SAFE" << endl;
                }
                else // initial report as given is unsafe. Must check for alterations
                {
                    for (int i = 0; i < currentReportLength; i++) // save original report
                    {
                        originalReport[i] = currentReport[i];
                    }
                    int skip = 0;
                    currentReportLength -= 1;
                    for (int i = 0; i < currentReportLength+1; i++) // i is the index being excluded
                    {
                        skip = 0;
                        for (int j = 0; j < currentReportLength+1; j++) // constructing the adjusted report
                        {
                            if (i == j) 
                            {
                                skip = 1;
                            }
                            if ((j + skip) >= currentReportLength+1) 
                            {}
                            else 
                            {
                                currentReport[j] = originalReport[j + skip];
                            }
                        }
                        if (checkSafe())
                        {
                            safeCounter++;
                            cout << "SAFE" << endl;
                            break;
                        }
                    }
                    //cout << "UNSAFE" << endl;
                }
                
            }    
        }
    }
    inputFile.close();

    cout << "And the answer is..." << endl << safeCounter << endl;
}
