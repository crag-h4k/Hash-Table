#pragma once
#include <string>
using namespace std;

struct Node
{
	int data;
	Node *next;
	double weight;
	string name;
	Node(double w, string n){
		weight = w;
		name = n;
		next = nullptr;
	}
};
