#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <fstream>
#include <unordered_map>

using namespace std;

int interpret(string code) {
	string program = code;

	size_t ip = 0;

	vector<string> variablesContent = {};
	vector<string> toRun = {};
	vector<unsigned char> tape = { 0 };
	
	vector<string> variables = {};

	size_t cell_index = 0;

	string user_input;
	string tmp;

	unordered_map<size_t, size_t> loop_table;

	int stage = 0;

	char instruction;
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

	ip = 0;

	while (ip < program.size()) {
		instruction = program[ip];

		switch (instruction) {
		case '+':
			tape[cell_index] += 1;
			break;
		case '-':
			tape[cell_index] -= 1;
			break;
		case '<':
			cell_index--;
			break;
		case '>':
			cell_index++;
			if (cell_index == tape.size()) {
				tape.push_back(0);
			}
			break;
		case '.':
			cout << tape[cell_index];
			break;
		case ',':
			if (user_input.empty()) {
				cin >> user_input;
				user_input.push_back('\n');
			}
			tape[cell_index] = user_input[0];
			user_input.erase(0, 1);
			break;
		case '[':
			if (!tape[cell_index]) {
				ip = loop_table[ip];
			}
			break;
		case ']':
			if (tape[cell_index]) {
				ip = loop_table[ip];
			}
			break;
		case '(':
			if (stage == 0) stage++;
			break;
		case ')':
			if (stage == 2) stage = 0;
			
			variables.push_back(tmp);

			tmp = "";
			break;
		case '{':
			if (stage == 0) stage++;
			break;
		case '}':
			if (stage == 2) stage = 0;

			variablesContent.push_back(tmp);

			tmp = "";
			break;
		}

		if (stage == 1) {
			stage++;
		}
		else if (stage == 2) {
			tmp += instruction;
		}

		ip++;
	}

	return 0;
}
