#pragma once

#include <string>

#include <vector>

#include <iostream>

#include <fstream>

#include <sstream>

#include "TrieNode.h"

using namespace std;

class Trie

{

private:

TrieNode* root;

int numberWords;

int numberNodes;

public:

Trie();

~Trie();

/* Return the number of words in this trie.

Best-case time complexity: T(1)

Worst-case time complexity: T(1)

*/

int count();

/* Return the number of nodes in this trie.

Best-case time complexity: T(1)

Worst-case time complexity: T(1)

*/

int getSize();

/* Return the root node of the Trie.

Best-case time complexity: T(1)

Worst-case time complexity: T(1)

*/

TrieNode* getRoot();

/* Insert a given word into the trie, and increment the number of words and number of nodes counters.

Best-case time complexity: T??

Worst-case time complexity: T??

Where n is the number of characters in the string given.

*/

bool insert(string);

/* Determine if a given word exists in the trie.

Best-case time complexity: T??

Worst-case time complexity: T??

Where n is the number of characters in the string given.

*/

bool find(string);

/* Return a vector of complete words that match the given string.

Best-case time complexity: T??

Worst-case time complexity: T??

Where n is the number of characters in the string given.

*/

vector<string> complete(string);

/* Return the number of words that match the given string (I.E the count of the vector returned by complete).

This is implemented by calling complete with the given string, and calling count on the resultant vector.

Best-case time complexity: T??

Worst-case time complexity: T??

Where n is the number of characters in the string given.

*/

int completeCount(string);

/* Read in a list of words to insert into our trie from a file pointed to by the given string.

Each line in the file is parsed as one word for the trie.

Best-case time complexity: T??

Worst-case time complexity: T??

Where n is the number of lines in the file.

*/

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

// The file doesn't exist.

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

// We couldn't find the value given, so there are no completions available.

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