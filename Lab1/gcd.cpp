/*
 * Lab1.cpp
 *
 *  Created on: Jan 23, 2017
 *      Author: Qiuan Wu
 */
#include <iostream>
using namespace std;

int userecursion(int x, int y)
{
    if (y != 0)
       return userecursion(y, x % y);
    else
       return x;
}

int useloop(int x, int y){
	while(x != y)
	    {
	        if(x > y)
	            x -= y;
	        else
	            x -= y;
	    }
	return x;
}

int main(){
	cout << userecursion(6, 9);
	cout << useloop(6, 9);
}
