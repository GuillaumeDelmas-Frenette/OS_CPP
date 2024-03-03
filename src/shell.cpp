
#include "interpreter.h"
#include "shellmemory.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

int MAX_USER_INPUT = 1000;
int parseInput(string ui);

int main(int argc, char *argv[]) {
	printf("%s\n", "Shell version 1.2 Created March 2024");
	help();
	ShellMemory& shellMemory = ShellMemory::getInstance();
	int errorCode = 0;					// zero means no error, default

    char prompt = '$';  				// Shell prompt
	string userInput;					// user's input stored here
	while(1){
		cout << prompt << ' ';
		getline(cin, userInput);
		errorCode = parseInput(userInput);
		if (errorCode == -1) exit(99);
	}
	return 0;
}

int parseInput(string ui){
	int errorCode = 0;
	vector<string> words;
	stringstream ss(ui);
	string word;
	int w=0;
	while(ss >> word){
		words.push_back(word);
		w++;
	}
	errorCode = interpreter(words, w);
	return errorCode;
}