/*
 * rpmult.cpp
 *
 *  Created on: Mar 10, 2017
 *      Author: Qiuan Wu
 *      Pledge: I pledge my honor that I have abided by the Stevens Honor System.
 */

#include <locale>
#include <iostream>
#include <cctype>
#include <string>
#include <sstream>


using namespace std;

unsigned long russian_peasant_multiplication(unsigned int m, unsigned int n){
	long result = 0;
	long p, q;
	if (n < m){
		q = n;
		p = m;
	}
	else{
		q = m;
		p = n;
	}

	while (q > 0){
		if (q & 1){
			result = result + p;
		}

		p = p << 1;
		q = q >> 1;
	}
	return result;
}


int main(int argc, char * const argv[]) {
	int x, y;
	istringstream iss;
	if (argc <= 0){
		cout << "Usage: "<< argv[0] <<  " <integer m> <integer n>" << endl;
		return 1;
	}
	if (argc != 3){
		cout << "Usage: "<< argv[0] <<  " <integer m> <integer n>" << endl;
		return 1;
	}
	iss.str(argv[1]);
	if(!(iss >> x) || x<0 || x > 2147483648){
		cout <<"Error: The first argument is not a valid nonnegative integer." << endl;
		return 1;
	}
	iss.clear();
	iss.str(argv[2]);
	if(!(iss >> y) || y < 0 || y > 2147483648){
		cout <<"Error: The second argument is not a valid nonnegative integer." << endl;
		return 1;
	}
	else{
		cout << x << " x " << y << " = " << russian_peasant_multiplication(x, y);
		return 0;
	}

}
