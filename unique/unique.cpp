/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Qiuan Wu
 * Date        : 02/09/2017
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <locale>
#include <iostream>
#include <cctype>
#include <string>


using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
	for(unsigned int i=0; i < s.length(); i++){
		if(islower(s[i]) == false){
			return false;
		}
	}
	return true;
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
    // You may use only a single int for storage and work with bitwise
    // and bitshifting operators.
    // No credit will be given for other solutions.
	unsigned int value = 1;
	unsigned int bit = 0;
	if (s.length() == 1){
		return true;
	}
	for (unsigned int i = 0; i < s.length(); i++){
		value <<= s[i] - 97;
		if ((value&bit) == value){
			return false;
		}
		else{
			bit = bit|value;
			value = 1;
		}
	}
	return true;
}


int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.

	if (argc == 1){
		cerr << "Usage: " << argv[0] << " <string>" << endl;
		return 1;
	}

	if (argc > 2){
		cerr << "Usage: " << argv[0] << " <string>" << endl;
		return 1;
	}


	if (is_all_lowercase(argv[1]) == false){
		cout << "Error: String must contain only lowercase letters." << endl;
		return 1;
	}

	if (all_unique_letters(argv[1]) == false){
		cout << "Duplicate letters found." << endl;
		return 1;
	}

	else{
		cout << "All letters are unique." << endl;
		return 0;
	}
}



