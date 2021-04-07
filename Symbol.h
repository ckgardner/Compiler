#ifndef SYMBOL
#define SYMBOL
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class SymbolTableClass {

public:
    bool Exists(const std::string & s);
    void AddEntry(const std::string & s);
    int GetValue(const std::string & s);
    void SetValue(const std::string & s, int v);
    int GetIndex(const std::string & s);
    int GetCount();

    
private:
    struct Variable{
        string mLabel;
        int mValue;
    };
    vector<Variable> vec;
};

#endif // SYMBOL