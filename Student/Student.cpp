/*
 * Student.cpp
 *
 *  Created on: Jan 27, 2017
 *      Author: Qiuan Wu
 *      Pledge: I pledge my honor that I have abided by the Stevens Honor System.
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

class Student {
public:
	Student(string f, string l, float g, int i) :
			first_(f), last_(l), gpa_(g), id_(i) {
	}

	void set_first(string f) {
		first_ = f;
	}

	string get_first() {
		return first_;
	}

	string full_name() const {
		return first_ + last_;
	}

	int id() const {
		return id_;
	}

	float gpa() const {
		return gpa_;
	}

	void print_info() const {
		cout << first_ << " "<< last_ << ", GPA: " << fixed <<  setprecision(2) << gpa_ << ", ID: " << id_  << endl;
	}
private:
	string first_;
	string last_;
	float gpa_;
	int id_;
};

void print_students(const vector<Student> &students) {
	// Same way we iterated through the vector in the previous function, except
	// calling print_info() for each student
	for (vector<Student>::const_iterator it = students.begin();
			it != students.end(); ++it) {
		it->print_info();
	}
}

vector<Student> find_failing_students(const vector<Student> &students) {
	vector<Student> failing_students;
	for (vector<Student>::const_iterator it = students.begin();
			it != students.end(); ++it) {
		if (it->gpa() < 1.0) {
			failing_students.push_back(*it);
		}
	}
	return failing_students;
}

/**
* Allows the user to enter information for multiple students, then
* find those students whose GPA is below 1.0 and prints them to the
* screen.
*/
int main() {
	string first_name, last_name;
	float gpa;
	int id;
	char repeat;
	vector<Student> students;

	do {
		cout << "Enter student's first name: ";
		cin >> first_name;
		cout << "Enter student's last name: ";
		cin >> last_name;
		gpa = -1;
		while (gpa < 0 || gpa > 4) {
			cout << "Enter student's GPA (0.0-4.0): ";
			cin >> gpa;
		}
		cout << "Enter student's ID: ";
		cin >> id;
		students.push_back(Student(first_name, last_name, gpa, id));
		cout << "Add another student to database (Y/N)? ";
		cin >> repeat;
	} while (repeat == 'Y' || repeat == 'y');

	cout << endl << "All students:" << endl;
	print_students(students);

	cout << endl << "Failing students:";

	// TODO
	// Print a space and th333333e word 'None' on the same line if no students are
	// failing.
	// Otherwise, print each failing student on a separate line.
	if (find_failing_students(students).empty()) {
		cout << " None" << endl;
	} else {
		cout << endl;
		print_students(find_failing_students(students));
	}
	return 0;
}

