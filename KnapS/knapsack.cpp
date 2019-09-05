/*
 * knapsack.cpp
 *
 *  Created on: Apr 24, 2017
 *      Author: Qiuan Wu
 *      Pledge: I pledge my honor that I have abided by the Stevens Honor System
 */
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
    unsigned int item_number, weight, value;
    string description;

    explicit Item(const unsigned int item_number,
                  const unsigned int weight,
                  const unsigned int value,
                  const string &description) :
    item_number(item_number),
    weight(weight),
    value(value),
    description(description) { }

    friend std::ostream& operator<<(std::ostream& os, const Item &item) {
        os << "Item " << item.item_number << ": " << item.description
        << " (" << item.weight
        << (item.weight == 1 ? " pound" : " pounds") << ", $"
        << item.value << ")";
        os.flush();
        return os;
    }
};


class Knapsack {

public:
    explicit Knapsack(const string &filename): filename_(filename), input_file_(filename.c_str()) {
        if (!input_file_) {
            ostringstream oss;
            oss << "Cannot open file '" << filename << "'." << endl;
            throw runtime_error(oss.str());
        }
        input_file_.exceptions(ifstream::badbit);
        parse_file();
    }
    // generate the array
    void solver(unsigned int capacity) {
        size_t rows = items_.size() + 1;
        size_t columns = capacity + 1;

        vector<unsigned int> initialized_row (columns);

        for (size_t row = 1; row <= rows; row++) {
            values.push_back(initialized_row);
        }

        for (size_t i = 1; i < rows; i++) {
            Item current_item = items_[i - 1];
            for (size_t j = 1; j < columns; j++) {
                if (current_item.weight <= j) {
                    values[i][j] = max(values[i - 1][j], values[i - 1][j - current_item.weight] + current_item.value);
                } else {
                    values[i][j] = values[i - 1][j];
                }
            }
        }
        generate_solution(capacity);
    }
    // return all items
    vector<Item> items() {
        return items_;
    }
    // return solution
    vector<Item> solution() {
        return solution_;
    }


private:
    string filename_;
    ifstream input_file_;
    vector<Item> items_;
    vector<Item> solution_;
    vector<vector<unsigned int> > values;

    // Parse the input file. Construct items vector
    void parse_file() {
        string line;
        istringstream iss;
        try {
            unsigned int line_number = 1;
            while (getline(input_file_, line)) {
                vector<string> temp;
                temp.clear();
                size_t start_pos = 0;
                size_t end_pos = 0;
                while ((end_pos = line.find(",", start_pos)) != string::npos) {
                    temp.push_back(line.substr(start_pos, end_pos - start_pos));
                    start_pos = end_pos + 1;
                }
                temp.push_back(line.substr(start_pos, line.size()));
                if (temp.size() != 3) {
                    ostringstream oss;
                    oss << "Line number "<< line_number <<" does not contain 3 fields." << endl;
                    throw runtime_error(oss.str());
                }
                int weight;
                istringstream weight_stream(temp[1]);
                if (!(weight_stream >> weight) || weight <= 0) {
                    ostringstream oss;
                    oss << "Invalid weight '"<< weight_stream.str() <<"' on line number "<< line_number <<"." << endl;
                    throw runtime_error(oss.str());
                }
                int value;
                istringstream value_stream(temp[2]);
                if (!(value_stream >> value) || value <= 0) {
                    ostringstream oss;
                    oss << "Invalid value '"<< value_stream.str() <<"' on line number "<< line_number <<"." << endl;
                    throw runtime_error(oss.str());
                }

                Item current_item = Item(line_number, weight, value, temp[0]);
                items_.push_back(current_item);

                ++line_number;
            }
            input_file_.close();
        } catch (const ifstream::failure &f) {
            ostringstream oss;
            oss << "An I/O error occurred reading '" << filename_ << "'.";
            throw runtime_error(oss.str());
        }
    }
    // back track
    void generate_solution(int capacity) {
        size_t i = size_t(items_.size());
        size_t j = capacity;
        while (values[i][j] != 0) {
            if (values[i][j] == values[i - 1][j]) {
                i--;
            } else {
                solution_.push_back(items_[i - 1]);
                j -= items_[i - 1].weight;
                i--;
            }
        }
        reverse(solution_.begin(), solution_.end());
    }

};

void print_t(vector<Item> items) {
    unsigned int total_weight = 0;
    unsigned int total_value = 0;
    for (vector<Item>::iterator it = items.begin(); it != items.end(); it++) {
        total_weight += it->weight;
        total_value += it->value;
    }
    if (total_weight == 1){
    	cout << "Total weight: " << total_weight << ( total_weight > 1 ? " pounds" : " pound" );
    }
    else{
    	cout << "Total weight: " << total_weight << ( total_weight > 1 ? " pounds" : " pounds" );
    }
    cout << endl << "Total value : $" << total_value << endl;;
}

void print_i(vector<Item> items) {
	if (items.size()== 0){
		cout << " None" << endl;
	}
	else{
		for (vector<Item>::iterator it = items.begin(); it != items.end(); it++) {
			cout << "   Item " << it->item_number << ": " ;
			cout << it->description << " (";
			cout << it->weight << ((it->weight == 1) ? " pound, $" : " pounds, $");
			cout << it->value << ")" << endl ;
		}
	}
}


int main(int argc, char * const argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <capacity> <filename>" << endl;
        exit(1);
    }
    int capacity;
    istringstream iss(argv[1]);
    if (!(iss >> capacity) || capacity <= 0) {
        cerr << "Error: Bad value '" << argv[1] << "' for capacity." << endl;
        exit(1);
    }
    // print the result
    Knapsack * knapsack;
    try {
        knapsack = new Knapsack(argv[2]);
        knapsack->solver(capacity);
        cout << "Candidate items to place in knapsack:" << endl;
        print_i(knapsack->items());
        cout << "Capacity: " << capacity << ( capacity > 1 ? " pounds" : " pound" );
        cout << endl << "Items to place in knapsack:" << endl;
        print_i(knapsack->solution());
        print_t(knapsack->solution());
        delete knapsack;
    }
    catch (const exception &e) {
        cerr << "Error: " << e.what();
        exit(1);
    }

    return 0;
}
