
#include "interpreter.h"
#include "shellmemory.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <unistd.h>
#include <fstream>
using namespace std;

int MAX_USER_INPUT = 1000;
int parseInput(string ui);

int main(int argc, char *argv[]) {
	printf("%s\n", "Shell version 1.2 Created March 2024");
	help();
	ShellMemory& shellMemory = ShellMemory::getInstance();
	int errorCode = 0;					// zero means no error, default

	string userInput;					// user's input stored here
	char prompt = '$';  				// Shell prompt
	while(1){
		if (isatty(fileno(stdin))){
			cout << prompt << ' ';
		}
		if (cin.eof()){
			cin.clear();
			freopen("/dev/tty","r", stdin);
			continue;
		}
		getline(cin, userInput);
		errorCode = parseInput(userInput);
		if (errorCode == -1) exit(99);
	}
	return 0;
}

int parseInput(string ui){
	int errorCode = 0;
	vector<string> command;
	stringstream ss(ui);
	string word;
	int w=0;
	while(ss >> word){
		w++;

		//If ";" is encoutered, execute command and start a new one
		if (word[word.length()-1] == ';'){
			command.push_back(word.substr(0, word.length()-1));
			errorCode = interpreter(command, w);
			if (errorCode != 0) return errorCode;
			command.clear();
			w=0;
			
		//Else, just add the current word to the command
		} else {
			command.push_back(word);
		}
	}
	errorCode = interpreter(command, w);
	return errorCode;
}