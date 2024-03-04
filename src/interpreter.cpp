#include "shell.h"
#include "interpreter.h"
#include "shellmemory.h"
#include "helper.h"
#include <iostream>
#include <fstream>
#include <filesystem>
using namespace std;
namespace fs = filesystem;

int MAX_ARGS_SIZE = 7;

int badcommand(){
	printf("%s\n", "Unknown Command");
	return 1;
}

int badcommand(string err){
	cout << err;
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
int echo(string value);
int ls();
int mkdir(string dirName);
int touch(string fileName);
int cd(string dirName);

int interpreter(vector<string> command_args, int args_size){
	int i;
	if (args_size > MAX_ARGS_SIZE){
		return badcommand("Bad command: Too many tokens\n");
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
		if (args_size > 7){
			return badcommand("Bad command: Too many tokens\n");
		}
		string value;
		for (i = 2; i < args_size - 1; i++){
			value = value.append(command_args[i]);
			value = value.append(" ");
		}
		value.append(command_args[i]);
		return set(command_args[1], value);
	}

	else if(strCaseCompare(command_args[0], "print")){
		if(args_size != 2) return badcommand();
		return print(command_args[1]);
	}

	else if(strCaseCompare(command_args[0], "run")){
		if(args_size != 2) return badcommand();
		return run(command_args[1]);
	}

	else if (strCaseCompare(command_args[0], "echo")){
		if(args_size != 2) return badcommand();
		return echo(command_args[1]);
	}

	else if (strCaseCompare(command_args[0], "my_ls")){
		if (args_size > 1){
			return badcommand();
		}
		return ls();
	}

	else if (strCaseCompare(command_args[0], "my_mkdir")){
		if (args_size > 2){
			return badcommand();
		}
		string dirName = command_args[1];
		if (dirName[0] == '$'){
			dirName = ShellMemory::getInstance().getValue(dirName.substr(1));
			if (containsMultipleWords(dirName)){
				return badcommand("Bad command: my_mkdir\n");
			}
		}
		return mkdir(dirName);
	}

	else if (strCaseCompare(command_args[0], "my_touch")){
		if (args_size > 2){
			return badcommand();
		}
		return touch(command_args[1]);
	}
	
	else if (strCaseCompare(command_args[0], "my_cd")){
		if (args_size > 2){
			return badcommand();
		}
		if (fs::is_directory(command_args[1])){
			return cd(command_args[1]);
		}
		else return badcommand("Bad command: my_cd\n");
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

int echo(string value){
	if (value[0] == '$'){
		return print(value.substr(1));
	}
	else {
		cout << value << "\n";
	}
	return 0;
}

int mkdir(string dirName){
	try {
		fs::create_directory(dirName);
	}
	catch (const exception& e){}
	return 0;
}

int cd(string dirName){
	fs::current_path(dirName);
	return 0;
}

int touch(string filename){
	ofstream outFile(filename);
	outFile.close();
	return 0;
}

int ls(){
	vector<string> filenames;
	for (const auto& entry : fs::directory_iterator(fs::current_path())){
		string filename = entry.path().filename();
		if (filename[0] == '"'){
			filename = filename.substr(1, filename.length()-3);
		}
		filenames.push_back(filename);
	}
	sort(filenames.begin(), filenames.end());
	for (const auto& filename : filenames){
		cout << filename << "\n";
	}
	return 0;
}