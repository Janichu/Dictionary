#include "Dictionary.h"
#include <fstream>
#include <vector>
void start(vector <Dictionary *>);
bool compare(string,string);
bool checkDupe(Dictionary *, Dictionary *);
int main() {
  vector <Dictionary *> dict;
  string line;
  cout << "! Opening data file... ./Data.CS.SFSU.txt" << endl
      << "! Loading data..." << endl;
  fstream fin;
  fin.open("Data.CS.SFSU.txt", ios::in);
  //reads from the txt file line by line
  while(getline(fin,line)){
    //variable s to find the index at which specific symbols separate 
    //the word, part of speech, and definition
    int s = line.find("|");
    //variable w for storing the word
    string w = line.substr(0,s);
    while (s != string::npos){
      line = line.substr(s+1,line.length() - s - 1);
      s = line.find(" -=>> ");
      //variable p for storing the part of speech
      string p = line.substr(0,s);
      line = line.substr(s+6, line.length() - 6 - s);
      s = line.find(".");
      //variable d for storying the definition
      string d = line.substr(0,s + 1);
      line = line.substr(s+1,line.length() - s - 1);
      s = line.find("|");
      //dynamically allocate memory
      Dictionary * di = new Dictionary{w,p,d};
      dict.push_back(di);
    }
  }  
  for (int i{0}; i < dict.size(); i++){
    string s{""};
    s = dict[i]->getWord();
    s[0] = toupper(s[0]);
    dict[i]->setWord(s);
  }
  cout << "! Loading completed..." << endl;
  fin.close();
  cout << "! Closing data file... ./Data.CS.SFSU.txt" << endl;
  start(dict);
  //delete objects in memory so no memory leak
  for (int i {0}; i < dict.size(); i++){
    delete dict[i];
    dict[i] = nullptr;
  }
  return 0;
}
void start (vector <Dictionary *> dict) {
  cout << endl << "----- DICTIONARY 340 C++ -----" << endl << endl;
  string search {"Search: "};
  string line {"       |"};
  string space {"        "};
  string nFound {"<Not found>"};
  string wPOS {"<2nd argument must be a part of speech or \"distinct\">"};
  string end {"-----THANK YOU-----"};
  bool notQ = true;

  while(notQ){
    vector <string> values;
    vector <string> preps {"adjective", "noun", "verb", "adverb", "interjection",
      "conjunction", "preposition", "pronoun"};
    bool distinct = false;  
    bool prep;
    string input;  
    cout << search;
    getline(cin,input);
    string word = "";
    for (int i {0}; i < input.length(); i++){
      if (i == input.length() -1 && input[i] != ' '){
        word = word + input[i];
        values.push_back(word);
      }
      else if (input[i] == ' '){
        values.push_back(word);
        word = "";
      }
      else {
        word = word + input[i];
      }
    }
    for (int i {0}; i < values.size(); i++){
      string temp = values[i];
      for (int j {1}; j < values[i].length(); j++){
        temp[j] = tolower(temp[j]);
      }
    }

    if (values[0] == "!q" || values[0] == "!Q"){
      notQ = false;
      break;
    }
    cout << line << endl;

    if (values.size() == 3){
      if (compare(values[2], "distinct")){
        int count {0};
        for (int i{0}; i < preps.size(); i++){
          if (values[1] == preps[i]){
            prep = true;
            break;
          }
          else prep = false;
        }
        if (!prep){
          cout << space << wPOS << endl << line << endl;
          continue;
        }
        vector <Dictionary *> temp;
        for (int i{0}; i < dict.size(); i++){
          if (compare(values[0],dict[i]->getWord()) &&
            compare(values[1],dict[i]->getPoS())){
            temp.push_back(dict[i]);
            for (int j{0}; j < temp.size() - 1; j++){
              if (temp.size() > 1 && checkDupe(dict[i],temp[j])){
                temp.pop_back();
                break;
              }
            }
          }
        }
        if(temp.size() == 0){
          cout << space << nFound << endl;
        }
        for (int i{0}; i < temp.size(); i++){
          cout << space << temp[i]->getWord() << " [" << temp[i]->getPoS() << "] : "
            << temp[i]->getDefn() << endl;
        }
        cout << line << endl;
      }
      else {
        int count {0};
        for (int i{0}; i < preps.size(); i++){
          if (values[1] == preps[i]){
            prep = true;
            break;
          }
          else prep = false;
        }
        if (!prep){
          cout << space << wPOS << endl << line << endl;
          continue;
        }
        for (int i{0}; i < dict.size(); i++){
          if (compare(values[0],dict[i]->getWord()) &&
            compare(values[1],dict[i]->getPoS())){
            cout << space << dict[i]->getWord() << " [" << dict[i]->getPoS() << "] : "
              <<dict[i]->getDefn() << endl;
            count++;
          }
          else if (i == dict.size() -1 && count == 0){
            cout << space << nFound << endl;
          }
        }
        cout << line << endl;
      }

    }
    else if (values.size() == 2){
      if (compare(values[1], "distinct")){
        vector <Dictionary *> temp;
        for (int i{0}; i < dict.size(); i++){
          if (compare(values[0],dict[i]->getWord())){
            temp.push_back(dict[i]);
            for (int j{0}; j < temp.size() -1; j++){
              if (temp.size() > 1 && checkDupe(dict[i],temp[j])){
                temp.pop_back();
                break;
              }
            }
          }
        }
        for (int i{0}; i < temp.size(); i++){
          cout << space << temp[i]->getWord() << " [" << temp[i]->getPoS() << "] : "
            << temp[i]->getDefn() << endl;
        }
        cout << line << endl;
      }
      else {
        int count{0};
        for (int i{0}; i < preps.size(); i++){
          if (values[1] == preps[i]){
            prep = true;
            break;
          }
          else prep = false;
        }
        if (!prep){
          cout << space << wPOS << endl << line << endl;
          continue;
        }
        for (int i{0}; i < dict.size(); i++){
          if (compare(values[0],dict[i]->getWord()) &&
            compare(values[1],dict[i]->getPoS())){
            cout << space << dict[i]->getWord() << " [" << dict[i]->getPoS() << "] : "
              <<dict[i]->getDefn() << endl;
            count++;
          }
          else if (i == dict.size() -1 && count == 0){
            cout << space << nFound << endl;
          }
        }
        cout << line << endl;
      }
    }
    else if (values.size() == 1){
      int count {0};
      for (int i{0}; i < dict.size(); i++){
        if (compare(values[0],dict[i]->getWord())){
          cout << space << dict[i]->getWord() << " [" << dict[i]->getPoS() << "] : "
            <<dict[i]->getDefn() << endl;
          count++;
        }
        else if (i == dict.size() -1 &&  count == 0){
          cout << space << nFound << endl;
        }
      }
      cout << line << endl;
    }
  }
  cout << endl << end << endl;
}
bool compare(string s1,string s2){
  if (s1.length() != s2.length()) return false;
  for (int i{0}; i < s1.length(); i++){
    if (tolower(s1[i]) != tolower(s2[i])) return false;
  }
  return true;
}
bool checkDupe(Dictionary * dict1, Dictionary * dict2){
  string p1 = dict1->getPoS();
  string d1 = dict1->getDefn();
  string p2 = dict2->getPoS();
  string d2 = dict2->getDefn();
  if (compare(p1,p2) && compare(d1,d2)) return true;
  else return false;
}
