// CS320A4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
std::ifstream infile("C:\\Users\\ibro991\\Desktop\\input.txt");
typedef std::chrono::high_resolution_clock Clock;

using namespace std;

bool Solve(string);

const char atom = 'a';
const float nanoseconds_per_ms = 1000000;
string output;

int main()
{
	// Get the number of test cases to process
	string input;
	getline(infile/*cin*/, input);
	string::size_type sz;
	int countCases = 2000;//stoi(input, &sz);

	// Solve for each case.
	for (size_t i = 0; i < countCases; i++)
	{

		// Read in the test case.
		getline(infile/*cin*/, input);

		// Start timing to benchmark.
		//auto start = Clock::now();

		// Solve it.
		bool isSet = Solve(input);

		/*auto end = Clock::now();*/
		/*std::// cout
			<< "Took "
			<< std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / nanoseconds_per_ms
			<< " | "
			<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
			<< " ms to solve." << std::endl;*/

		// print "Set" or "No Set."
		/*start = Clock::now();*/
		if (isSet)
		{
			output = "Word #" + to_string(i) + ": Set\n";
			fwrite(output.data(), sizeof(char), output.size(), stdout);
		}
		else
		{
			output = "Word #" + to_string(i) + ": No Set\n";
			fwrite(output.data(), sizeof(char), output.size(), stdout);
		}
		/*end = Clock::now();
		std::// cout
			<< "Took "
			<< std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / nanoseconds_per_ms
			<< " | "
			<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
			<< " ms to print output." << std::endl;*/
	}
}

bool Solve(string input)
{
	 // cout << "\n===================================\n";
	 // cout << "trying to solve " << input << "\n";
	 // cout << "===================================\n";
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

		for (size_t i = 1, len = input.length() - 1; i < len; i++)
		{
			// Get the current char from our input.
			char c = input[i];
			// Get the previous char from our "solution".
			char p = solution[i - 1];

#pragma region VerbosePrinting
			// Verbose printing.
			// cout << "\n===================================\n\n";
			// cout << "i:" << to_string(i) << "/" << to_string(len - 1) << "\n\n";
			// cout << "p:" << p << "\n";
			// cout << "c:" << c << "\n";
			// cout << "f:" << to_string(failures[i]) << "\n";
			// cout << "open braces:" << to_string(openBraces) << "\n";


			// cout << "failures: ";
			//for each (int f in failures)
			//{
			//	// cout << to_string(f) << " ";
			//}
			//// cout << "\n";
			//// cout << "input:    ";
			//for each (char c in input)
			//{
			//	// cout << c << " ";
			//}
			//// cout << "\n";
			//// cout << "solution: ";
			//for each (char c in solution)
			//{
			//	// cout << c << " ";
			//}
			//// cout << "\n";
			//// cout << "          ";
			//for (size_t j = 0; j < input.length(); j++)
			//{
			//	if (j == i) { // cout << "^ "; }
			//	//else if (j == i - 1) // cout << "^ ";
			//	else { // cout << "  "; }
			//}
			// cout << "\n";
			//End Verbose printing.

#pragma endregion

			// Assume that the current char is an atom and see if it works.
			if (failures[i] == 0) // this is the first check we will for, hence checking if failures[i] is 0.
			{
				// cout << "Does " << c << " work as an atom... ";
				if (p == atom // aa
					|| p == '}') // }a
				{ // Doesn't work as an atom.
					failures[i]++;
					// cout << "No!\n";
				}
				else // Works as an atom.
				{
					// Check if this is the last run through, as braces only matter at this point.
					if (i == len - 1 && openBraces != 0)
					{
						// Braces don't match, fail.
						// cout << "No. Last element and braces don't match, failing.\n";\
							// increment failures.
							failures[i]++;
					}
					else // No issues with braces. Change the solution string, incase it was overwritten by atom being possible.
					{
						// Replace the current index in the solution with an 'a'
						solution[i] = atom;
						// cout << "Yes!\n"; // No op.
						continue;
					}
				}
			}

			// Assume the current char is what it says it is and see if it works.
			if (failures[i] == 1)
			{
				// cout << "Does " << c << " work as a structural element... ";
				if ((p == '}' &&   c == '{')  // }{
					|| (p == 'a' &&   c == '{')  // a{
					|| (p == '{' &&   c == ',')  // {,
					|| (p == ',' && !(c == '{'))) // ,, ,}
				{ // Doesn't work as a structural element.
				  // Increment failures and continue within this loop.
					// cout << "No!\n";
					failures[i]++;
				}
				else // Works as a structural element.
				{
					// Modify the number of open braces.
					openBraces += (c == '{' ? 1 : (c == '}' ? -1 : 0));

					// Check that the number of open braces has not gone -ve.
					if (openBraces < 0)
					{
						// cout << "No. Braces have gone negative.\n";
						// Undo our change.
						openBraces++;
						// increment failures.
						failures[i]++;
					}
					// Check if this is the last run through, as braces only matter at this point.
					if (i == len - 1)
					{
						if (openBraces != 0)
						{
							// Braces don't match, fail.
							// cout << "No. Last element and braces don't match, failing.\n";
							// increment failures.
							failures[i]++;
						}
						else
						{
							solution[i] = c;
							// cout << "Yes!\n"; // No op.
						}
						if (input[i] == ',')
						{

							// Braces don't match, fail.
							// cout << "No. Last element cannot be ','. Failing.\n";
							// increment failures.
							failures[i]++;
						}
						else
						{
							solution[i] = c;
							// cout << "Yes!\n"; // No op.
						}

					}
					else // No issues with braces. Change the solution string, incase it was overwritten by atom being possible.
					{
						solution[i] = c;
						// cout << "Yes!\n"; // No op.
					}
				}
			}

			if (failures[i] == 2) // Didn't work as an atom or a structural element.
			{
				// cout << "Didn't work as an atom or structural element.\n";
				if (i == 1) // Was this our first element.
				{
					// For 1st element: if both atom and structural failed then quit reporting not a set.
					return false;
				}
				else
				{
					// Not 1st element, need to go back to previous element and reset failure count.

					// Reset failures for this element.
					failures[i] = 0;
					// Increment failures for previous element.
					failures[i - 1]++;
					// Go back 2, as for loop will increment this by 1 when we call continue.
					i -= 2;
					// Retry.
					continue;
				}
			}
		}
		// cout << "Solution: " << solution << "\n";
		return true;
	}
	else // Not in correct form, return false.
	{
		result = false;
	}

	return result;
}
