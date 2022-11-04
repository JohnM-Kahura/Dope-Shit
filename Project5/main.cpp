#include <iostream>

#include <algorithm>

#pragma once

#include <string>

#include <vector>

#include <iostream>
#include <fstream>
#include <sstream>
#define ALPHABET_SIZE 27

#define END_OF_WORD_INDEX 26

#define END_OF_WORD '$'

#define EMPTY_NODE 0

#define INVALID_CHARACTER -1

using namespace std;

class TrieNode

{

private:

TrieNode** alphabet;

char value;

public:

TrieNode();

~TrieNode();

TrieNode** getAlphabet();

bool wordEnd();

void setValue(char);

char getValue();

TrieNode* getChild(char);

int index(char);

void initializeAlphabet();

void insert(string, int&);

bool find(string);

void traverse(vector<string>& results, string prefix);

};
TrieNode::TrieNode()

{

alphabet = nullptr; // sets the alphapet to null

value = EMPTY_NODE;

}

TrieNode::~TrieNode()

{

if (alphabet) {

delete[] this->alphabet;

}

}

TrieNode** TrieNode::getAlphabet()

{

return this->alphabet;

}

TrieNode* TrieNode::getChild(char character) {

int nextIndex = index(character);

if (this->alphabet == nullptr) {

return nullptr;

}

TrieNode* node = this->alphabet[nextIndex];

if (node->value == EMPTY_NODE) {

return nullptr;

}

return node;

}

bool TrieNode::wordEnd() {

return this->alphabet[END_OF_WORD_INDEX]->value == END_OF_WORD;

}

int TrieNode::index(char c)

{

if (c == '$') {

return 26;

}

else {

int index = int(c - 'a');

if (index < 0 || index > ALPHABET_SIZE - 1) {

return INVALID_CHARACTER;

}

else {

return index;

}

}

}

void TrieNode::initializeAlphabet()

{

alphabet = new TrieNode*[ALPHABET_SIZE];

for (int i = 0; i < ALPHABET_SIZE; i++) {

alphabet[i] = new TrieNode();

}

}

void TrieNode::insert(string value, int& count)

{

if (this->alphabet == nullptr) {

// We can't instantiate our array of TrieNodes in the constructor or we'll get a stack overflow.

// Initialize it on an insert if it hasn't already been done.

this->initializeAlphabet();

}


//value check is done on the next node
char nextCharacter = value.at(0);

int alphabetIndex = index(nextCharacter);

if (alphabetIndex == INVALID_CHARACTER) {


// case where the word provided has unkown characters the following id printed to the screen
cout << "The words provided are not supported please try  again!" << endl;

return;

}

TrieNode* nextLetterNode = this->alphabet[alphabetIndex];

if (nextLetterNode->value != nextCharacter) {

// If the next node already has it's value set

nextLetterNode->value = nextCharacter;

count++;

}

if (value.length() > 1) {



string leftovers = value.substr(1, value.length());

nextLetterNode->insert(leftovers, count);

}

}

bool TrieNode::find(string value)

{

if (this->alphabet == nullptr) {



return false;

}

if (value.length() == 0) {


return this->alphabet[END_OF_WORD_INDEX]->value == END_OF_WORD;

}



char nextCharacter = value.at(0);

int alphabetIndex = index(nextCharacter);

TrieNode* nextLetterNode = this->alphabet[alphabetIndex];

string leftovers = value.substr(1, value.length());

if (nextLetterNode->getValue() != nextCharacter) {



return false;

}

else {

// recursive call to find the netx node

return nextLetterNode->find(leftovers);

}

}

void TrieNode::setValue(char value)

{

this->value = value;

}

char TrieNode::getValue()

{

return value;

}

void TrieNode::traverse(vector<string>& results, string prefix) {

if (this->alphabet == nullptr) {

// We have no nodes so there's nothing to do here.

return;

}

if (this->wordEnd()) {

// We have a $ pointer, so we need to add the string up to us to the vector.

results.push_back(prefix + this->value);

}

for (int i = 0; i < ALPHABET_SIZE - 1; i++) {

// We go to ALPHABET_SIZE - 1 to skip the END_OF_WORD index.

TrieNode* currentNode = this->alphabet[i];

if (currentNode->value != EMPTY_NODE) {

// If we have a node for this letter, call traverse on it.

currentNode->traverse(results, prefix + this->value);

}

}

}

class Trie

{

private:

TrieNode* root;

int numberWords;

int numberNodes;

public:

Trie();

~Trie();



int count();



int getSize();



TrieNode* getRoot();



bool insert(string);



bool find(string);


vector<string> complete(string);



int completeCount(string);



bool read(string);

};
Trie::Trie()

{

root = new TrieNode();

numberWords = 0;

numberNodes = 0;

}

Trie::~Trie()

{

delete root;

}

int Trie::count()

{

return numberWords;

}

int Trie::getSize()

{

return numberNodes;

}

bool Trie::insert(string value)

{

if (this->find(value)) {

return false;

}

this->root->insert(value + "$", this->numberNodes);

numberWords++;

return true;

}

bool Trie::find(string value)

{

return this->root->find(value);

}

int Trie::completeCount(string value)

{

return this->complete(value).size();

}

bool Trie::read(string filename) {

ifstream infile(filename);

if (!infile.good()) {



return false;

}

string line;

while (getline(infile, line)) {

this->insert(line);

}

}

vector<string> Trie::complete(string value)

{

TrieNode* nextNode = this->root;

for (int i = 0; i < value.length(); i++) {

char nextCharacter = value.at(i);

if (nextNode->getChild(nextCharacter) == nullptr) {


return vector<string>();

}

nextNode = nextNode->getChild(nextCharacter);

}

vector<string> results = vector<string>();

nextNode->traverse(results, value.substr(0, value.length() - 1));

return results;

}

TrieNode* Trie::getRoot()

{

return root;

}

bool testInsert() {

Trie myTrie;

if (!myTrie.insert("test")) {

cout << "Trie::insert fails to insert a new node when the trie is empty." << endl;

return false;

}

else if (!myTrie.find("test")) {

cout << "Trie::insert fails to find the inserted node in the trie." << endl;

return false;

}

else if (myTrie.insert("test")) {

cout << "Trie::insert succeeds on inserting duplicate nodes." << endl;

return false;

}

return true;

}

bool testSizeAndCount() {

Trie myTrie;

myTrie.insert("test");

myTrie.insert("testing");

myTrie.insert("woo");

myTrie.insert("woo");

myTrie.insert("wooo");

myTrie.insert("hoo");

if (myTrie.getSize() != 19) {

// Expected count is 5 more than the expected letter nodes to account for end of word $ nodes.

cout << "Trie::getSize does not return the proper number of nodes" << endl;

return false;

}

else if (myTrie.count() != 5) {

cout << "Trie::count() does not return the proper number of words" << endl;

return false;

}

return true;

}

bool testComplete() {

Trie myTrie;

vector<string> results = myTrie.complete("unfound");

if (results.size() != 0) {

cout << "Trie::complete returns a vector with something in it when no words exist in the trie" << endl;

return false;

}

myTrie.insert("test");

myTrie.insert("testing");

myTrie.insert("testingtesting");

myTrie.insert("testers");

myTrie.insert("unrelated");

results = myTrie.complete("tes");

if (results.size() != 4) {

cout << "Trie::complete does not return the proper number of elements" << endl;

return false;

}

myTrie.insert("testingtesting");

myTrie.insert("unrelatedtwo");

results = myTrie.complete("testin");

if (results.size() != 2) {

cout << "Trie::complete does not return the proper number of elements after inserting more elements" << endl;

return false;

}

}

void checkTestSuccess(bool success, int& passes, int& failures) {

if (success) {

cout << ".";

passes++;

}

else {

failures++;

}

}

int main()

{

int passes = 0;

int failures = 0;

checkTestSuccess(testInsert(), passes, failures);

checkTestSuccess(testSizeAndCount(), passes, failures);

checkTestSuccess(testComplete(), passes, failures);

cout << endl;

if (failures > 0) {

cout << "Testcase finished with failures" << endl;

cout << "Succeful tests: " << passes << endl;

cout << "Failed Tests : " << failures << endl;

}

else {

cout << "PASSED" << endl;

cout << "Tests Ran: " << passes << endl;

}

Trie myTrie;

myTrie.read(".\\wordlist.txt");

cout << "Try to enter a word prefix -->To exit press Enter key<---->: ";

string input;

while (getline(cin, input)) {

if (input == "") {

break;

}

vector<string> completions = myTrie.complete(input);

if (completions.size() == 0) {

cout << "Could not do the completions.Please try again" << endl;

} else {

cout << "Output ie completions: " << endl << "--------------" << endl;

for (string completion : completions) {

cout << completion << endl;

}

}

cout << "Try to enter a word prefix -->To exit press Enter key<---->: ";

}

system("pause");

return 0;

}