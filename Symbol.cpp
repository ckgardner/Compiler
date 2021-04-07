#include "Symbol.h"

bool SymbolTableClass::Exists(const std::string & s){
    // cout << "Symbol table vec size: " << vec.size() << '\n';
    for(int i=0;i<vec.size();i++){
        if(vec[i].mLabel == s){
            return true;
        }
    }
    return false;
}

void SymbolTableClass::AddEntry(const std::string & s){
    Variable var;
    var.mLabel = s;
    if(Exists(s)){
        exit(-1);
    }else{
        vec.push_back(var);
    }
}

int SymbolTableClass::GetValue(const std::string & s){
    if(Exists(s) == false){
        printf("Value does not exist: ");
        exit(-1);
    }else{
        int i = GetIndex(s);
        return vec[i].mValue;
    }
}

void SymbolTableClass::SetValue(const std::string & s, int v){
    // cout << "set value " << v << " on " << s << '\n';
    if(Exists(s) == false){
        printf("Value does not exist: ");
        exit(EXIT_FAILURE);
    }else{
        int i = GetIndex(s);
        vec[i].mValue = v;
    }
}

int SymbolTableClass::GetIndex(const std::string & s){
    for(int i=0;i<vec.size();i++){
        if(vec[i].mLabel == s){
            return i;
        }
    }
    return -1;
}

int SymbolTableClass::GetCount(){
    return vec.size();
}