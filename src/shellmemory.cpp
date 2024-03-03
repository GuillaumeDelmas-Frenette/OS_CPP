
#include <string>
#include "shellmemory.h"
#include "helper.h"
#include <iostream>
using namespace std;

const string MemoryEntry::getVar() {
    return var;
}

void MemoryEntry::setVar(string var) {
    this->var = var;
}

const string MemoryEntry::getValue() {
    return value;
}

void MemoryEntry::setValue(string value) {
    this->value = value;
}

ShellMemory::ShellMemory(int size) {
    this->size = size;
    memory.resize(size);
    for (int i = 0; i < size; i++) {
        memory[i].setVar("none");
        memory[i].setValue("none");
    }
}

ShellMemory& ShellMemory::getInstance() {
    static ShellMemory instance(1000);
    return instance;
}

void ShellMemory::setValue(string var, string value){
    int i;

    for (i=0; i<this->size; i++){
        if (strCaseCompare(this->memory[i].getVar(), var)){
            memory[i].setValue(value);
            return;
        }
    }
    for (i=0; i<this->size; i++){
        if(strCaseCompare(this->memory[i].getVar(), "none")){
            memory[i].setVar(var);
            memory[i].setValue(value);
            return;
        }
    }
    return;
}

string ShellMemory::getValue(string var){
    int i;
    for (i=0; i<this->size; i++){
        if(strCaseCompare(memory[i].getVar(), var)){
            return memory[i].getValue();
        }
    }
    return "Variable does not exist";
}