// CS320A4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

bool Solve(string);

const char atom = 'a';

int main()
{
    // Get the number of test cases to process
    string input;
    getline(cin, input);
    string::size_type sz;
    int countCases = stoi(input, &sz);
    
    // Solve for each case.
    for (size_t i = 0; i < input.size(); i++)
    {
        // Read in the test case.
        getline(cin, input);

        // Solve it.
        bool isSet = Solve(input);

        // print "Set" or "No Set."
        if (isSet)
        {
            cout << "Word #" << to_string(i + 1) << ": Set\n";
        }
        else
        {
            cout << "Word #" << to_string(i + 1) << ": No Set\n";
        }
    }
}

bool Solve(string input)
{
    bool result = false;

    int last = input.length() - 1;

    // Check that the input is of the form "{ ... }".
    if ((input[0] == '{') && (input[last] == '}'))
    {
        // Keep track of the number of braces we have open.
        int openBraces = 0;
        // Copy our input string into a new string where we can play around with things.
        string solution = input;
        // Create a vector to keep track of failures, when any of them reach 2 then we're unable to continue.
        vector<int> failures(input.length());

        for (size_t i = 1, len = input.length() - 2; i < len; i++)
        {
            char c = input[i]; // get the current char.
            char p = solution[i - 1]; // get the previous char from our "solution"

            // Assume that the current char is an atom and see if it works.
            if (failures[i] == 0) // this is the first check we will fo, hence checking if failures[i] is 0.
            {
                if (p == atom // aa
                    || p == '}') // }a
                { // Doesn't work as an atom.
                    failures[i]++;
                    i--;
                    continue;
                }
                else // Works as an atom.
                {
                    // Replace the current index in the solution with an 'a'
                    solution[i] = atom;
                    continue;
                }
            }
            
            // Assume the current char is what it says it is and see if it works.
            else if (failures[i] == 1)
            {
                if ((p == '}' && c == '{')  // }{
                    || (p == '}' && c == ',')  // },
                    || (p == '{' && c == ',')  // {,
                    || (p == ',')) // ,, ,} ,{
                { // Doesn't work as a structural element.
                    failures[i]++;
                    i--;
                    continue;
                }
                else // Works as a structural element.
                {
                    // Modify the number of open braces.
                    openBraces += (c == '{' ? 1 : (c == '}' ? -1 : 0));
                    // Check if this is the last run through, as braces only matter at this point.
                    if (i == len && openBraces != 0)
                    {
                        // Braces don't match, fail.
                        cout << "Braces don't match, failing.";
                        return false;
                    }
                    // Don't need to change the solution string.
                    continue;
                }
            }
            else // Didn't work as an atom or a structural element, we should quit reporting failure.
            {
                return false;
            }
        }
        return true;
    }
    else // Not in correct form, return false.
    {
        result = false;
    }

    return result;
}


