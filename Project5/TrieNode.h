#pragma once

#include <string>

#include <iostream>

#include <vector>

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