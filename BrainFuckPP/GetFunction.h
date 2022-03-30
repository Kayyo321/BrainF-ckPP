#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <fstream>
#include <unordered_map>

using namespace std;

string getFunction(string program) {
	vector<unsigned char> tape = { 0 };
	size_t cell_index = 0;

	string user_input;
	string tmp;

	string tmpName;
	string tmpContents;

	unordered_map<size_t, size_t> loop_table;

	int stage = 0;
	int funcStage = 0;

	char instruction{};
	size_t loop_beginning_index;
	stack<size_t> loop_stack;
	for (size_t ip = 0; ip < program.size(); ip++) {
		instruction = program[ip];
		if (instruction == '[') {
			loop_stack.push(ip);
		}
		else if (instruction == ']') {
			loop_beginning_index = loop_stack.top();
			loop_stack.pop();
			loop_table[loop_beginning_index] = ip;
			loop_table[ip] = loop_beginning_index;
		}
	}

	size_t ip = 0;

	switch (instruction) {
		case '(':
			if (stage == 0) stage++;
			break;
		case ')':
			if (stage == 2) stage = 0;
			tmpName = tmp;
			tmp = "";
			break;
		case '{':
			if (funcStage == 0) funcStage++;
			break;
		case '}':
			if (funcStage == 2) funcStage = 0;
			tmpContents = tmp;

			cout << tmpContents << endl;

			tmp = "";
			break;
	}

	if (stage == 1) {
		stage++;
	}
	else if (stage == 2) {
		tmp += instruction;
	}

	if (funcStage == 1) {
		funcStage++;
	}
	else if (funcStage == 2) {
		tmp += instruction;
	}

	return tmpContents;
}