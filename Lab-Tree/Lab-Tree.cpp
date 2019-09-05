/*
 * Lab-Tree.cpp
 *
 *  Created on: Mar 31, 2017
 *      Author: Class2019
 */
#include <iostream>
#include <sstream>

using namespace std;

struct Node {
    Node *parent, *left, *right;
    int level, data;

    Node(int level, int data) :
            parent(NULL), left(NULL), right(NULL),
            level(level), data(data) { }

    Node(Node *parent, int level, int data) :
            parent(parent), left(NULL), right(NULL),
            level(level), data(data) { }
};

bool contains_tree(Node *t1, Node *t2){
	if (t1 == NULL && t2 == NULL){
		return true;
	}

	if (t1 == NULL && t2 != NULL){
		return false;
	}
	if(t1->data == t2->data){
		return contains_tree(t1->left, t2->left) || contains_tree(t1->right, t2->right);
	}
	else{
		return contains_tree(t1->left, t2) || contains_tree(t1->right, t2);
	}
}

////////////////////////////////////////////////////////
long left_right_binary_exp(int a, unsigned int n){
	if (n == 0){
		return 1;
	}
	int i = n, num_bits = 0;
	while (i > 0){
		i >>= 1;
		++ num_bits;
	}
	long product = a;
	for (i = num_bits - 2; i >= 0; i--){
		product *= product;
		if ((n >> i) & 1){
			product *= a;
		}

	}
	return product;
}
/////////////////////////////////////////////////////////


int main(){
	Node* nodes[7];
	nodes[0] = NULL;
	nodes[1] = new Node(1, 1);
	nodes[2] = new Node(nodes[1], 2, 2);
	nodes[3] = new Node(nodes[1], 2, 3);
	nodes[4] = new Node(nodes[2], 3, 4);
	nodes[5] = new Node(nodes[2], 3, 5);
	nodes[6] = new Node(nodes[5], 4, 6);

	Node* nodes2[3];
	nodes2[0] = NULL;
    nodes2[1] = new Node(1, 1);
	nodes2[2] = new Node(nodes2[1], 2, 2);


	if (contains_tree(nodes[6], nodes2[2])){
		cout <<"Yes"<< endl;
	}
	else{
		cout <<"No" << endl;
	}
	return 0;
}



