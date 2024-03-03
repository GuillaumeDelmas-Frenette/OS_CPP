#ifndef SHELLMEMORY_H
#define SHELLMEMORY_H

#include <vector>
#include <string>
using namespace std;


class MemoryEntry{
    private:
        string var;
        string value;
        
    public:
    const string getVar();
    void setVar(string var);
    const string getValue();
    void setValue(string value);
};

class ShellMemory {
private:
    int size;
    vector<MemoryEntry> memory;
    ShellMemory(int size);
public:
    void setValue(string var, string value);
    string getValue(string var);
    static ShellMemory& getInstance();
};

#endif
