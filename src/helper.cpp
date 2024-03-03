#include <string>
using namespace std;

bool strCaseCompare(const string& str1, const string& str2) {
    string str1Lower = str1;
	string str2Lower = str2;
	transform(str1Lower.begin(), str1Lower.end(), str1Lower.begin(), ::tolower);
	transform(str2Lower.begin(), str2Lower.end(), str2Lower.begin(), ::tolower);
    return str1Lower == str2Lower;
}