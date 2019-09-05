/*
 * sieve.cpp
 *
 *  Created on: Jan 31, 2017
 *      Author: Qiuan Wu
 */

/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Qiuan Wu
 * Date        : Jan 31, 2017
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit) : is_prime_(new bool[limit + 1]), limit_(limit) {
        sieve();
    }

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    inline int num_primes() const {
        return num_primes_;
    }

    void display_primes() const {
        // TODO: write code to display the primes in the format specified in the
        // requirements document.
    	const int max_prime_width = num_digits(max_prime_), primes_per_row = 80 / (max_prime_width + 1);
        int * primeindex = new int[num_primes_];
   	    int countP = 0;
    	//Count the number of primes in the limit, save the value in primeindex
   		for(int i = 2; i <=limit_; i++){
   			if(is_prime_[i] == true){
  				primeindex[countP] = i;
  				countP++;
    		}
   		}
   		//If the number of prime <= primes for each row, do the normal printing
   		if (countP <= primes_per_row){
   			for(int i = 0; i < countP;i++){
   				cout << primeindex[i];
   				if(i != (countP - 1))
  				{
   					cout << " ";
    			}
   			}
   		}
   		//If not, print the primes on multiple lines
   		else{
  			int NumEachLine = 0;
    		for(int i = 0; i < countP; i++){
   				int Space = max_prime_width - num_digits(primeindex[i]) + 1;
  				if(NumEachLine == 0){
    				for(int j = 1; j < Space; j++){
    					cout << " ";
   					}
   				}
   				else{
   					for(int j = 1; j <= Space; j++){
    					cout << " ";
   					}
    			}
    			cout << primeindex[i];
    			NumEachLine++;
    			if(NumEachLine == primes_per_row){
    				NumEachLine = 0;
   					cout << "\n";
   				}
   			}
   		}
    }


private:
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    int count_num_primes() const {
        // TODO: write code to count the number of primes found
    	int numP = 0;
    	for (int i = 2; i < limit_; i++){
    		if(is_prime_[i] == true){
    			numP++;
    		}
    	}
    	return numP;
    }

    int num_digits(int num) const {
        // TODO: write code to determine how many digits are in an integer
        // Hint: No strings are needed. Keep dividing by 10.
    	int L = 0;
    	while (num >= 1){
    		num /= 10;
    		L ++;
    	}
    	return L;
    }

    void sieve() {
        // TODO: write sieve algorithm
    	for(int i = 2; i <= limit_; i++){
    	    is_prime_[i] = true;
    	}
    	for (int i = 2; i <= sqrt(limit_); i++){
    		if (is_prime_[i] == true){
    			for (int j = i * i; j <= limit_; j += i)
    				is_prime_[j] = false;
    		}
    	}
    	for (int k = 2; k <= limit_; k++){
    		if (is_prime_[k] == true){
    			num_primes_++;
    			max_prime_ = k;
    		}
    	}
    }
};

int main(void) {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.
    else {
    	PrimesSieve P(limit);

    	cout << endl << "Number of primes found: " << P.num_primes() << endl;
    	cout << "Primes up to " << limit << ":" << endl;
    	P.display_primes();
    	return 0;
    }

}



