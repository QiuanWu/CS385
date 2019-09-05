/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Qiuan Wu
 * Version     : 1.0
 * Date        : 03/24/2017
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototyspe.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    // TODO
	long count = 0;
	for (long i = 0; i < length; i++){
		for (long j = i + 1; j < length; j++){
			if (array[i] > array[j]){
				count += 1;
			}
		}
	}
	return count;

}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */

static long mergesort(int array[], int scratch[], int low, int high) {
    // TODO
	long count = 0;
	long mid = (low + high)/2 + 1;
	long left = low; //counter for left array
	long right = mid; //counter for right array
	long temp = low; //counter for temp array

	while ((left <= mid) && (right <= high)){
		if (array[left] <= array[right]){
			scratch[temp] = array[left];
			left++;
		}
		else{
			scratch[temp] = array[right];
			right++;
			count += (mid - left);
		}
		temp++;
	}
	if (left == mid){
		for (int i = right; i <= high; i++){
			scratch[temp] = array[i];
			temp ++;
		}
	}
	else{
		for (int i = left; i <= mid; i++){
			scratch[temp] = array[i];
			temp ++;
		}
	}

	for (int i = low; i <= high; i++){
		array[i] = scratch[i];
	}

	return count;

}

long count_inversions_fast_helper(int array[], int scratch[], int low, int high){
	int mid = 0; //(low + high) /2;
	int count = 0;
	if (low < high){
	    mid = (low + high) / 2;
		count += count_inversions_fast_helper(array, scratch, low, mid);
		count += count_inversions_fast_helper(array, scratch, mid + 1, high);
		count += mergesort(array, scratch, low, high);
	}
	return count;
}

long count_inversions_fast(int array[], int length) {
    // TODO
    // Hint: Use mergesort!
	int *scratch = new int [length];
	//int low = 0;
	//int high = length - 1;
	return count_inversions_fast_helper(array, scratch, 0, length - 1);
}



int main(int argc, char *argv[]) {
	// TODO: parse command-line argument
	if (argc > 2) {
		cerr << "Usage: ./inversioncounter [slow]";
		return 1;
	}
	if (argc == 2 && (strcmp(argv[1], "slow") != 0) ) {
		cerr << "Error: Unrecognized option '" << argv[1] << "'.";
		return 1;
	}

	cout << "Enter sequence of integers, each followed by a space: " << flush;
	istringstream iss;
	int value, size = 0,  index = 0;
	vector<int> values;
	string str;
	str.reserve(11);
	char c;
	while (true) {
		c = getchar();
		const bool eoln = c == '\r' || c == '\n';
		if (isspace(c) || eoln) {
			if (str.length() > 0) {
				iss.str(str);
				if (iss >> value) {
					values.push_back(value);
					size++;
				} else {
					cerr << "Error: Non-integer value '" << str
							<< "' received at index " << index << "." << endl;
					return 1;
				}

				iss.clear();
				++index;
			}
			if (eoln) {
				break;
			}
			str.clear();
		} else {
			str += c;
		}
	}
	// TODO: produce output
	long count;

	if (size == 0) {
		cerr << "Error: Sequence of integers not received." << endl;
		return 1;
	}
	if (argc == 2) {
		count = count_inversions_slow(&values[0], size);
	} else {
		count = count_inversions_fast(&values[0], size);
	}
	cout << "Number of inversions: " << count << endl;
	return 0;
}
