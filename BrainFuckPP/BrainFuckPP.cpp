#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <windows.h>

#include "Interpret.h"

using namespace std;

string getFileExt(const string& str) {

	size_t i = str.rfind('.', str.length());
	if (i != string::npos) {
		return(str.substr(i + 1, str.length() - i));
	}

	return("");
}

/// <summary>
/// This main function calls the interpret() function based on the path inputed by the user.
/// </summary>
/// <returns></returns>
int main() {
	HANDLE curConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	string program;
	string path;
	string tmp;

	fstream file;

	SetConsoleTextAttribute(curConsole, 15);

	cout << "Enter BrainFuck++ Code-Path : ";
	cin >> path;

	if (getFileExt(path) != ".bpp") {
		cout << "[ ";

		SetConsoleTextAttribute(curConsole, 12);

		cout << "WARNING";

		SetConsoleTextAttribute(curConsole, 15);

		cout << " ] ";

		SetConsoleTextAttribute(curConsole, 6);

		cout << "The File Extension Is Not In .bpp Format, Which Can Cause Confusion With Bigger Applications. Reccomended to change the file extension to .bpp" << endl;

		SetConsoleTextAttribute(curConsole, 15);
	}

	file.open(path, ios::in); // read

	if (file.is_open()) {
		string line;

		while (getline(file, line)) { // gets each line, and puts it in the tmp variable
			tmp += line;
		}

		interpret(tmp);

		file.close();
	}

	return 0;
}
