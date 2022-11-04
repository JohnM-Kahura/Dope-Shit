#include "TrieNode.h"

TrieNode::TrieNode()

{

alphabet = nullptr;

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

// Get the index of the node that references the next character.

// Since we always start at the root node which is simply a placeholder,

// we always start looking for our value on the next node.

char nextCharacter = value.at(0);

int alphabetIndex = index(nextCharacter);

if (alphabetIndex == INVALID_CHARACTER) {

// The given word has an unsupported character, so we can't insert this word.

cout << "Invalid word detected! Only lowercase characters a-z are supported by this trie!" << endl;

return;

}

TrieNode* nextLetterNode = this->alphabet[alphabetIndex];

if (nextLetterNode->value != nextCharacter) {

// If the next node already has it's value set, it means it's already been inserted into this subtree,

// so we only want to increment the node count parameter if the node is completely new.

nextLetterNode->value = nextCharacter;

count++;

}

if (value.length() > 1) {

// The value parameter will only have one character left when we're done,

// so only recurse if we have more than one character.

// Take a substring of the parameter, removing the first character, and call insert on our next letter node.

string leftovers = value.substr(1, value.length());

nextLetterNode->insert(leftovers, count);

}

}

bool TrieNode::find(string value)

{

if (this->alphabet == nullptr) {

// If we haven't even inserted anything, there's nothing to find.

return false;

}

if (value.length() == 0) {

// When the value parameter has no characters left, we're at the end of the word,

// so the current node needs to have an END_OF_WORD pointer at the end of its array

// for this to be a true word.

return this->alphabet[END_OF_WORD_INDEX]->value == END_OF_WORD;

}

// Get the next node to look at,

// and slice off the first character to use for the recursive method call.

char nextCharacter = value.at(0);

int alphabetIndex = index(nextCharacter);

TrieNode* nextLetterNode = this->alphabet[alphabetIndex];

string leftovers = value.substr(1, value.length());

if (nextLetterNode->getValue() != nextCharacter) {

// The only thing this catches is if the next node hasn't been initialized,

// which means it has never been inserted into the Trie.

// A trie node should only ever have no value or the character that matches its index in the array.

return false;

}

else {

// Recursively call find on the next node, with the sliced off string.

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
