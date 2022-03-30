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
	size_t cellIndex = 0;
	size_t loopBeginningIndex;

	string program = code;
	string userInput;
	string tmp;

	unordered_map<size_t, size_t> loopTable;

	int stage = 0;

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
			tape[cellIndex] += 1;
			break;
		case '-':
			tape[cellIndex] -= 1;
			break;
		case '<':
			cellIndex--;
			break;
		case '>':
			cellIndex++;
			if (cellIndex == tape.size()) {
				tape.push_back(0);
			}
			break;
		case '.':
			cout << tape[cellIndex];
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
		case '(':
			if (stage == 0) stage++;
			break;
		case ')':
			if (stage == 2) {
				stage = 0;

				for (int i = 0; i < tmp.length(); i++)
				{
					tape[cellIndex] = (int)tmp[i];
				}

				tmp = "";
			}
			break;
		}

		if (stage == 2) {
			tmp += instruction;
		}

		if (stage == 1) stage++;

		ip++;
	}

	delete &ip;
	delete &code;
	delete &tape;
	delete &cellIndex;
	delete &userInput;
	delete &tmp;
	delete &loopTable;
	delete &stage;
	delete &instruction;
	delete &loopBeginningIndex;
	delete &loopStack;

	return 0;
}
