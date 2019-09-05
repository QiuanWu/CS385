/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Qiuan Wu
 * Date        : 02/15/2017
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

using namespace std;

vector< vector<int> > ways;
vector<int> result;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.

	if (num_stairs <= 0){
		ways.push_back(result);
	}
	else{
		for (int i = 1; i <= 3; i++){
			if (num_stairs >= i){
			result.push_back(i);
			get_ways(num_stairs - i);
			result.pop_back();
			}
		}
	}
	return ways;
}


void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
	if(ways.size() == 1){
			cout << "1 way to climb ";
	}
	else{
		cout << ways.size() << " ways to climb ";
	}
	if(ways.at(0).size() == 1){
		cout << "1 stair." << endl;
	}
	else{
		cout << ways.at(0).size() << " stairs." << endl;
	}

	for (unsigned int i = 0; i < ways.size(); i++) {
			if (ways.size()>= 10){
				cout << setw(2)<< i + 1 << ". " << "[";
 			}
			else{
				cout << setw(1) << i + 1 << ". " << "[";
			}
	        for (unsigned int j = 0; j < ways[i].size(); j++) {
	            if (j != ways[i].size()-1)
	                cout << ways[i][j] << ", ";
	            else
	                cout << ways[i][j];
	        }
	        cout << "]" << endl;
	}
}


int main(int argc, char * const argv[]) {

	if(argc <= 0 || argc != 2)
		{
			cout << "Usage: ./stairclimber <number of stairs>";
			return 0;
		}

		string str = argv[1];
		if(!isdigit(str.at(0)) || argv[0] == 0)
		{
			cout << "Error: Number of stairs must be a positive integer.";
			return 0;
		}

		display_ways(get_ways(atoi(argv[1])));
		return 0;

}




