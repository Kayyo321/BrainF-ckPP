#include <iostream>
#include <string>
#include <fstream>

#include "Interpret.h"

using namespace std;

int main() {
	string program;
	string path;
	string tmp;

	fstream file;

	cout << "Enter BrainFuck++ Code-Path : ";
	cin >> path;

	file.open(path, ios::in); // read

	if (file.is_open()) {
		string line;

		while (getline(file, line)) { // gets each line, and puts it in the tmp variable
			tmp += line;
		}

		interpret(tmp);

		file.close();
	}
}
