#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <list>

using namespace std;

// Struct that represents the state of the water in the jugs.
struct State {
    int a, b, c;
    vector<string> directions;

    State(int _a, int _b, int _c) : a(_a), b(_b), c(_c) { }

    // String representation of state in tuple form.
    string toString()
    {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }

    //pushes the string S back onto the directions vector
    void add(string S)
    {
      directions.push_back(S);
    }

    //prints the contents of the vector directions
    void print(State capacity)
    {
    	cout << "Initial state. " << State(0,0,capacity.c).toString();
    	if(!directions.empty())
    	{
    		cout << endl;
    	}
    	for(vector<string>::iterator it = directions.begin(); it != directions.end(); ++it)
    	{
    		cout<< *it << endl;
    	}
    }
};






//creates a state for every possible permutation of the waterjugs based on the current layout
//when called by the poured function
State pour(int i , State Current, State Capacity)
{
	State Temporary = Current;
	int Poured = 0;
	ostringstream path;
	//because this function is called by the function poured, it has 6 cases that it will use depending on
	//the value of i that it is given
	switch(i)
	{
		case 0:
			while(Temporary.a != Capacity.a && Temporary.c != 0)
			{
				Poured++;
				Temporary.a = Temporary.a + 1;
				Temporary.c = Temporary.c - 1;
			}
			if(Poured != 1)
			{
				path << "Pour " << Poured << " gallons from C to A. " << Temporary.toString();
			}
			else
			{
				path << "Pour " << Poured << " gallon from C to A. " << Temporary.toString();
			}
			break;
		case 1:
			while(Temporary.a != Capacity.a && Temporary.b != 0)
			{
				Poured++;
				Temporary.a = Temporary.a + 1;
				Temporary.b = Temporary.b - 1;
			}
			if(Poured != 1)
			{
				path << "Pour " << Poured << " gallons from B to A. " << Temporary.toString();
			}
			else
			{
				path << "Pour " << Poured << " gallon from B to A. " << Temporary.toString();
			}
			break;
		case 2:
			while(Temporary.b != Capacity.b && Temporary.c != 0)
			{
					Poured++;
					Temporary.b +=1;
					Temporary.c -= 1;
			}
			if(Poured != 1)
			{
				path << "Pour " << Poured << " gallons from C to B. " << Temporary.toString();
			}
			else
			{
				path << "Pour " << Poured << " gallon from C to B. " << Temporary.toString();
			}
			break;
		case 3:
			while(Temporary.b != Capacity.b && Temporary.a != 0)
			{
				Poured++;
				Temporary.b  = Temporary.b + 1;
				Temporary.a = Temporary.a - 1;
			}
			if(Poured != 1)
			{
				path << "Pour " << Poured << " gallons from A to B. " << Temporary.toString();
			}
			else
			{
				path << "Pour " << Poured << " gallon from A to B. " << Temporary.toString();
			}
			break;
		case 4:
			while(Temporary.c != Capacity.c && Temporary.b != 0)
			{
				Poured++;
				Temporary.c = Temporary.c + 1;
				Temporary.b = Temporary.b - 1;
			}
			if(Poured != 1)
			{
				path << "Pour " << Poured << " gallons from B to C. " << Temporary.toString();
			}
			else
			{
				path << "Pour " << Poured << " gallon from B to C. " << Temporary.toString();
			}
			break;
		case 5:
			while(Temporary.c != Capacity.c && Temporary.a != 0)
			{
				Poured++;
				Temporary.c = Temporary.c + 1;
				Temporary.a = Temporary.a - 1;
			}
			if(Poured != 1)
			{
			path << "Pour " << Poured << " gallons from A to C. " << Temporary.toString();
			}
			else
			{
				path << "Pour " << Poured << " gallon from A to C. " << Temporary.toString();
			}
			break;
	}
	Temporary.add(path.str());
	return Temporary;
}

//calls the pour function 6 times and adds the results to the Adjacent vector
vector<State> poured(State front, State capacity)
	{
	vector<State> Adjacent;
	for(int i = 0; i < 6; ++i)
	{
		State adj = pour(i,front,capacity);
		Adjacent.push_back(adj);
	}
	return Adjacent;
}


//Performs a breadth first search to solve the waterjug puzzle
void BreadthFirstSearch(State Start, State End, State capacity)
{
	queue<State> Queue;
	Queue.push(Start);
	bool **VisitedAlready = new bool*[capacity.a +1];
	for (int i = 0; i < capacity.a +1; ++i)
	{
	    VisitedAlready[i] = new bool[capacity.b+1];
	    fill(VisitedAlready[i], VisitedAlready[i] + capacity.b +1, false);
	}
	if (Start.a == End.a && Start.b == End.b)
	{
		 Start.print(capacity);
		 return;
	}
	VisitedAlready[Start.a][Start.b] = true;
	while(!Queue.empty())
	{
		State front = Queue.front();
		vector<State> adjacent = poured(front, capacity);
		 for (vector<State>::iterator it = adjacent.begin(); it != adjacent.end(); ++it)
		 {
			 	front = *it;
			 	if (front.a == End.a && front.b == End.b)
			 	{
			 		front.print(capacity);
			 		return;
			 	}
				if(!VisitedAlready[front.a][front.b])
				{
					VisitedAlready[front.a][front.b] = true;
					Queue.push(front);
				}
			}
			Queue.pop();
		}
	for (int i = 0; i <= capacity.a; ++i)
	{
		    delete [] VisitedAlready[i];
	}
	delete [] VisitedAlready;
	cout << "No solution.";
}



//main function of the program
int main(int argc, char *argv[])
{
	if ( argc != 7) {
		cerr << "Usage: " << argv[0] << " <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
		return 0;
	}
	string First, Second, Third, Fourth, Fifth, Sixth;
	istringstream iss;
	iss.str(argv[1]);
	int capacityA, capacityB, capacityC, goalA, goalB, goalC;
	if ( !(iss >> capacityA) || capacityA < 0 )
	{
		cerr << "Error: Invalid capacity '" << argv[1] << "' for jug A."  << endl;
		return 1;
	}
	if (capacityA == 0) {
		cerr << "Error: Invalid capacity '0' for jug A."  << endl;
		return 1;
	}
	iss.clear();
	iss.str(argv[2]);
	if ( !(iss >> capacityB) || capacityB < 0 ) {
		cerr << "Error: Invalid capacity '" << argv[2] << "' for jug B."  << endl;
		return 1;
	}
	if (capacityB == 0) {
		cerr << "Error: Invalid capacity '0' for jug B."  << endl;
		return 1;
	}
	iss.clear();
	iss.str(argv[3]);
	if ( !(iss >> capacityC) || capacityC < 0 ) {
		cerr << "Error: Invalid capacity '" << argv[3] << "' for jug C."  << endl;
		return 1;
	}
	if (capacityC == 0) {
		cerr << "Error: Invalid capacity '0' for jug C."  << endl;
		return 1;
	}
	iss.clear();
	iss.str(argv[4]);
	if ( !(iss >> goalA) || goalA < 0) {
		cerr << "Error: Invalid goal '" << argv[4] << "' for jug A."  << endl;
		return 1;
	}
	iss.clear();
	iss.str(argv[5]);
	if ( !(iss >> goalB) || goalB < 0 ) {
		cerr << "Error: Invalid goal '" << argv[5] << "' for jug B."  << endl;
		return 1;
	}
	iss.clear();
	iss.str(argv[6]);
	if ( !(iss >> goalC) || goalC < 0) {
		cerr << "Error: Invalid goal '" << argv[6] << "' for jug C."  << endl;
		return 1;
	}
	if(goalC > capacityC) {
		cerr << "Error: Goal cannot exceed capacity of jug C." << endl;
		return 1;
	}
	if(goalB > capacityB) {
		cerr << "Error: Goal cannot exceed capacity of jug B." << endl;
		return 1;
	}
	if(goalA > capacityA) {
		cerr << "Error: Goal cannot exceed capacity of jug A." << endl;
		return 1;
	}
	if(goalA + goalB + goalC != capacityC ) {
		cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
		return 1;
	}
	if(goalC == capacityC) {
		cout << "Initial state. (0, 0, " << argv[3] << ")" << endl;
		return 1;
	}
	BreadthFirstSearch(State( 0, 0, capacityC), State(goalA, goalB, goalC), State(capacityA, capacityB, capacityC));
	return 0;

}




