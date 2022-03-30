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
			if (stage != 1) {
				tape[cellIndex] += 1;

				multiplier = 1;
			}
			break;
		case '-':
			if (stage != 1) {
				tape[cellIndex] -= 1;

				multiplier = 1;
			}
			break;
		case '<':
			if (stage != 1) {
				cellIndex -= 1;

				multiplier = 1;
			}
			break;
		case '>':
			if (stage != 1) {
				cellIndex += 1;
			
				if (cellIndex == tape.size()) {
					tape.push_back(0);
				}
			}

			multiplier = 1;
			break;
		case '.':
			if (stage != 1) {
				if (literal) {
					cout << (int)tape[cellIndex];
				}
				else {
					cout << tape[cellIndex];
				}
			}
			break;
		case ',':
			if (stage != 1) {
				if (userInput.empty()) {
					cin >> userInput;
					userInput.push_back('\n');
				}
				tape[cellIndex] = userInput[0];
				userInput.erase(0, 1);
			}
			break;
		case '[':
			if (stage != 1) {
				if (!tape[cellIndex]) {
					ip = loopTable[ip];
				}
			}
			break;
		case ']':
			if (stage != 1) {
				if (tape[cellIndex]) {
					ip = loopTable[ip];
				}
			}
			break;
		case '/':
			if (stage != 1) literal = !literal;
			break;
		case '#':
			if (stage == 0) stage = 1;

			if (stage == 1) stage = 0;
			break;
		default:
			if (isdigit(instruction) && stage != 1) {
				multiplier = instruction;
			}
			break;
		}

		ip++;
	}

	return 0;
}
