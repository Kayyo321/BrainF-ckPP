#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <fstream>
#include <unordered_map>

using namespace std;

/// <summary>
/// This function takes all of the code from the code path, and works based of the commands in it.
/// </summary>
/// <param name="code"></param>
/// <returns></returns>
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

	int readChar = 0;
	int stage = 0;

	bool literal = false;
	bool lookout = false;

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

		#pragma region MainBrainFuckCode
		switch (instruction) {
			case '+':
				if (readChar != 1) {
					tape[cellIndex] += 1;

					multiplier = 1;
				}
				break;
			case '-':
				if (readChar != 1) {
					tape[cellIndex] -= 1;

					multiplier = 1;
				}
				break;
			case '<':
				if (readChar != 1) {
					cellIndex -= 1;

					multiplier = 1;
				}
				break;
			case '>':
				if (readChar != 1) {
					cellIndex += 1;
			
					if (cellIndex == tape.size()) {
						tape.push_back(0);
					}
				}

				multiplier = 1;
				break;
			case '.':
				if (readChar != 1) {
					if (literal) {
						cout << (int)tape[cellIndex];
					}
					else {
						cout << tape[cellIndex];
					}
				}
				break;
			case ',':
				if (readChar != 1) {
					if (userInput.empty()) {
						cin >> userInput;
						userInput.push_back('\n');
					}
					tape[cellIndex] = userInput[0];
					userInput.erase(0, 1);
				}
				break;
			case '[':
				if (readChar != 1) {
					if (!tape[cellIndex]) {
						ip = loopTable[ip];
					}
				}
				break;
			case ']':
				if (readChar != 1) {
					if (tape[cellIndex]) {
						ip = loopTable[ip];
					}
				}
				break;
		}
		#pragma endregion

		#pragma region BrainFuck++Code
		switch (instruction) {
			case '^': // Square the current cell.
				if (readChar != 1) {
					tape[cellIndex] = (tape[cellIndex] * tape[cellIndex]);

					multiplier = 1;
				}
				break;
			case '*': // add a new line.
				if (readChar != 1) cout << endl;
				break;
			case '/': // make next prints literal, meaning they will print out the cell values instead of the ascii values.
				if (readChar != 1) literal = !literal;
				break;
			case '#':
				if (readChar == 1) readChar = 0;
				
				if (readChar == 0) readChar = 1;
				break;
			case '$': // clear the screen.
				if (readChar != 1)
					system("CLS");
				break;
			case '\\': // ignore the next character.
				if (readChar != 1)
					readChar = 1;

				ip++;
				break;
			case '&': // move values from point a, to point b.
				if (readChar != 1) lookout = true;
				break;
			default:
				if (isdigit(instruction) && readChar != 1) {
					multiplier = instruction;
				}
				break;

#pragma region Move Statements
			case '{':
				readChar = 1;

				if (lookout) {
					if (stage == 0) stage = 1;
				}
				break;
			case '}':
				if (lookout) {
					if (stage == 2) {
						stage = 0;
						
						int moveBy = 0;

						string a = "";
						int b = 0;

						for (char& c : tmp) {
							if (c != ';' && stage == 0) {
								a += c;
							}

							if (c != ';' && stage == 1) {
								b += (int)c;
							}

							if (c == ';') stage = 1;
						}

						stage = 0;

						for (char& c : a) {
							switch (c) {
								case '<':
									moveBy--;
									break;
								case '>':
									moveBy++;
									break;
							}
						}

						tape[cellIndex + moveBy] = b;

						tmp = "";
						readChar = 0;
					}
				}
				break;
#pragma endregion

		}
		#pragma endregion

		if (stage == 2) tmp += instruction;

		if (stage == 1) stage = 2;

		ip++;

		if (readChar == 1) readChar = 0;
	}

	return 0;
}
