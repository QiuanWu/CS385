/*
 * gcd.cpp
 *
 *  Created on: Jan 23, 2017
 *      Author: Qiuan Wu
 *      Pledge: I pledge my honor that I have abided by the Stevens Honor System
 */
#include <iostream>
#include <sstream>
#include <string>

using namespace std;


int main(int argc, char * const argv[]) {
	int m, n;
	istringstream iss;

	if (argc != 3){
		cerr << "Usage: " << argv[0] << " <integer m> <integer n>" << endl;
		return 1;
 	}

	iss.str(argv[1]);
	if (!(iss >> m)){
		cerr << "Error: The first argument is not a valid integer." << endl;
		return 1;
	}
	iss.clear();
	iss.str(argv[2]);

	if (!(iss >> n)){
		cerr << "Error: The second argument is not a valid integer." << endl;
		return 1;
	}

	int  gcd;
	if (m == 0 && n == 0)
		gcd = 0;
	else if (m == 0 || n == 0)
		gcd = 1;
	else
	for(int i = 1; i <= m && i <= n; i++){
	     if(m%i == 0 && n%i == 0 ){
	    	 gcd = i;
	   }
	}

	cout << "Iterative: gcd(" << m << ", " << n << ") = " << gcd << endl;
	cout << "Recursive: gcd(" << m << ", " << n << ") = " << gcd << endl;
	return 0;

}
