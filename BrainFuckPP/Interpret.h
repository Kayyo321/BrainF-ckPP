#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <fstream>
#include <unordered_map>

using namespace std;

int interpret(string code) {
	vector<unsigned char> tape = { 0 };

	size_t ip = 0;
	size_t multiplier = 1;
	size_t cellIndex = 0;
	size_t loopBeginningIndex;

	string program = code;
	string userInput;
	string tmp;

	unordered_map<size_t, size_t> loopTable;

	int stage = 0;

	bool literal = false;

	char instruction;
	stack<size_t> loopStack;
	for (size_t ip = 0; ip < program.size(); ip++) {
		instruction = program[ip];
		if (instruction == '[') {
			loopStack.push(ip);
		}
		else if (instruction == ']') {
			loopBeginningIndex = loopStack.top();
			loopStack.pop();
			loopTable[loopBeginningIndex] = ip;
			loopTable[ip] = loopBeginningIndex;
		}
	}

	while (ip < program.size()) {
		instruction = program[ip];

		switch (instruction) {
		case '+':
			tape[cellIndex] += multiplier;
			break;
		case '-':
			tape[cellIndex] -= multiplier;
			break;
		case '<':
			cellIndex -= multiplier;
			break;
		case '>':
			cellIndex += multiplier;
			if (cellIndex == tape.size()) {
				tape.push_back(0);
			}
			break;
		case '.':
			if (literal) {
				cout << (int)tape[cellIndex];
			}
			else {
				cout << tape[cellIndex];
			}
			break;
		case ',':
			if (userInput.empty()) {
				cin >> userInput;
				userInput.push_back('\n');
			}
			tape[cellIndex] = userInput[0];
			userInput.erase(0, 1);
			break;
		case '[':
			if (!tape[cellIndex]) {
				ip = loopTable[ip];
			}
			break;
		case ']':
			if (tape[cellIndex]) {
				ip = loopTable[ip];
			}
			break;
		case '/':
			literal = !literal;
			break;
		}

		if (stage == 2) {
			tmp += instruction;
		}

		if (stage == 1) stage++;

		ip++;
		multiplier = 1;
	}

	return 0;
}
