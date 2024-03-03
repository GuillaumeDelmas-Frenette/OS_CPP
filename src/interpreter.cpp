#include "shell.h"
#include "interpreter.h"
#include "shellmemory.h"
#include "helper.h"
#include <iostream>
#include <fstream>
using namespace std;

int MAX_ARGS_SIZE = 3;

int badcommand(){
	printf("%s\n", "Unknown Command");
	return 1;
}

int badcommandFileDoesNotExist(){
	printf("%s\n", "Bad command: File not found");
	return 3;
}

int help();
int quit();
int set(string var, string value);
int print(string var);
int run(string filename);

int interpreter(vector<string> command_args, int args_size){
	int i;
	if (args_size < 1 || args_size > MAX_ARGS_SIZE){
		return badcommand();
	}
	
	if (strCaseCompare(command_args[0], "help")){
		if(args_size != 1) return badcommand();
		return help();
	}

	else if(strCaseCompare(command_args[0], "quit")){
		if(args_size != 1) return badcommand();
		return quit();
	}

	else if(strCaseCompare(command_args[0], "set")){
		if (args_size !=3) return badcommand();
		return set(command_args[1], command_args[2]);
	}

	else if(strCaseCompare(command_args[0], "print")){
		if(args_size != 2) return badcommand();
		return print(command_args[1]);
	}

	else if(strCaseCompare(command_args[0], "run")){
		if(args_size != 2) return badcommand();
		return run(command_args[1]);
	}

	return badcommand();
}

int help(){
	char help_string[] = "COMMAND			DESCRIPTION\n \
help			Displays all the commands\n \
quit			Exits / terminates the shell with “Bye!”\n \
set VAR STRING		Assigns a value to shell memory\n \
print VAR		Displays the STRING assigned to VAR\n \
run SCRIPT.TXT		Executes the file SCRIPT.TXT\n ";
	cout << help_string ;
    cout << "\n";
	return 0;
}

int quit(){
	cout << "Bye!\n";
	exit(0);
}

int set(string var, string value){
	ShellMemory::getInstance().setValue(var, value);
	return 0;
}

int print(string var){
	cout << ShellMemory::getInstance().getValue(var) << "\n";
	return 0;
}

int run(string filename){
	int errCode=0;
	ifstream inputFile(filename);
	if (inputFile.is_open()) {
		string line;
		while(getline(inputFile, line)){
			errCode = parseInput(line);
		}
	} else {
		return badcommandFileDoesNotExist();
	}

	inputFile.close();
	return errCode;
}