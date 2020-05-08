#include "Dictionary.h"
Dictionary::Dictionary(){}
Dictionary::Dictionary(string word, string speech, string definition):
  word(word), poS(speech), defn(definition) {}
string Dictionary::getWord() const {
  return this->word;
}
string Dictionary::getPoS() const {
  return this->poS;
}
string Dictionary::getDefn() const{
  return this->defn;
}
void Dictionary::setWord(string Word) {
  word = Word;
}
