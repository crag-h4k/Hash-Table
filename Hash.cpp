#pragma once

#include "Hash.h"
Hash::Hash(){
	clear();
}

void Hash::clear(){
	for (int i = 0; i < tableSize; i++) { //tableSize max length we let the hash table index get to
		if (data[i].getSize()){
			data[i].destroyList();
		}
	}
}
void Hash::insert(string name, double weight){
	int index = hash(name);
	++used;
	data[index].append(weight, name);
}
Node* Hash::retrieve(string name){
	int index = hash(name);
	return data[index].findValue(name);
}

double Hash::operator[](string name){
	Node* temp = retrieve(name);
	if (temp){
		return temp->weight;
	}
	return 0;
}
