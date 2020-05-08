#pragma once
#include <string>
#include <iostream>
using namespace std;
class Dictionary {
  private :
    string word{""};
    string poS{""};
    string defn{""};
  public :
    Dictionary();
    Dictionary(string,string,string);
    string getWord() const;
    string getPoS() const;
    string getDefn() const;
    void setWord(string);
};