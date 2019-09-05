/*
 * cs385.cpp
 *
 *  Created on: Jan 23, 2017
 *      Author: Class2019
 *      cd c: > /directory > make > ./CS385 > bash (filename) >make clean
 *      run -> run configuration -> argument -> input
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
		cerr << "You Suck! M need to be an integer." << endl;
		return 1;
	}
	iss.clear();
	iss.str(argv[2]);

	if (!(iss >> n)){
		cerr << "You Suck! N need to be an integer." << endl;
		return 1;
	}

	if (n > m){
		cout << "max(" << n << ", " << m << ") =" << n << endl;
	}else{
		cout << "max(" << n << ", " << m << ") =" << m << endl;
	}
	return 0;



	string s;
	cin >> s;
	cout <<"Hello world!" << s << endl;
	return 0;
}





int useRecursion(int x, int y)
{
    if (y != 0)
       return useRecursion(y, x % y);
    else
       return x;
}

int useLoop(int x, int y){
	while(x != y)
	    {
	        if(x > y)
	            x -= y;
	        else
	            y -= x;
	    }
	return x;
}

int main(){
	cout << useRecursion(6, 9) << endl;
}


