#include "Hash.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>

using namespace std;
double evaluateFile(istream& ins);
void readWeightFile();
void readFormulaFile();
Hash hashes;

int main(){
	string x;
	readWeightFile();
	readFormulaFile();
	cout << "Enter 'q' TO EXIT" << endl;
	cin >> x;
	if (x == "q"){
		return EXIT_SUCCESS;
	}
	return EXIT_SUCCESS;
}

void readWeightFile(){
	ifstream input;
	string fileName;
	cout << "Name of atomic weight file:(remember to add .txt to the end)" << endl;
	getline(cin, fileName);
	input.open(fileName);
	if (input.fail()){
		cout << "Could not open file." << endl;
		exit(0);
	}
	while (!input.eof()){
		string line;
		getline(input, line);
		istringstream buf(line);
		vector<string> tokens;
		for (string toke; buf >> toke;){
			tokens.push_back(toke);
		}
		hashes.insert(tokens[1], atof(tokens[2].c_str()));
	}
	input.close();
	cout << "Table Initiated" << endl;
}
void readFormulaFile(){
	ifstream input;
	string fileName;
	cout << "Name of formula file:(remember to add .txt to the end)" << endl;
	getline(cin, fileName);
	input.open(fileName);
	if (input.fail()){
		cout << "Couldn't open file." << endl;
		exit(0);
	}
	while (input && input.peek() != EOF){
		double w = evaluateFile(input);
		cout << " " << w << endl;
		input.ignore();
	}
	input.close();
}

double evaluateFile(istream& ins){
	const char RIGHT_PARENTHESIS = ')';
	const char LEFT_PARENTHESIS = '(';
	double weight = 0;
	double subWeight = 0;
	string symbol = "";
	int mult = 1;

	while (ins && ins.peek() != '\n'){
		if (ins.peek() == LEFT_PARENTHESIS){
			if (symbol != "") {
				weight += hashes[symbol] * mult;
			}
			ins.ignore();
			mult = 1;
			symbol = "";
			cout << LEFT_PARENTHESIS;
			weight += evaluateFile(ins);
		}
		else if (ins.peek() == RIGHT_PARENTHESIS) {
			ins.ignore();
			weight += hashes[symbol] * mult;
			if (isdigit(ins.peek())){
				ins >> mult;
				weight *= mult;
				cout << RIGHT_PARENTHESIS << mult;
			}
			else {
				cout << RIGHT_PARENTHESIS;
			}
			return weight;
		}
		else if (isdigit(ins.peek())){
			ins >> mult;
			cout << mult;
		}
		else{
			char s;
			ins >> s;
			cout << s;
			if (isupper(s)) {
				if (symbol != "") {
					weight += hashes[symbol] * mult;
				}
				mult = 1;
				symbol = s;
			}
			else {
				symbol += s;
			}
		}
	}
	if (symbol != ""){
		weight += hashes[symbol] * mult;
	}
	return weight;
}
