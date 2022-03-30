#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <fstream>
#include <unordered_map>

using namespace std;

int interpret(std::string program) {
	vector<unsigned char> tape = { 0 };
	size_t cell_index = 0;

	string user_input;
	unordered_map<size_t, size_t> loop_table;

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

	size_t ip = 0;

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
			std::cout << tape[cell_index];
			break;
		case ',':
			if (user_input.empty()) {
				std::cin >> user_input;
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
		}

		ip++;
	}

	return 0;
}
