// Hash.cpp
// Kellan Cerveny and Jake Yoon
// Priebe 312
// 30 April 2020

#include "Hash.h"
#include "math.h"
#include <iostream>
#include <cstdlib>

using namespace std;

// HASH_TABLE CLASS FUNCTIONS
// ###########################################################################
Hash_Table::Hash_Table(unsigned int sequenceLength) {
    unsigned long hashtablecount = 42949672;
    for(int i = 0; i < sequenceLength; i++){
        //hashtablecount += pow(29.0, sequenceLength);
    }
    size = hashtablecount; // tableSize needs to be correctly calculated in advance
    vector<hashNode*> table(hashtablecount);// Set all pointers in the array to NULL to show they are unused
    array = table;
}

unsigned long Hash_Table::get_size() {
    return this->size;
}

// UNTESTED AND UNWORKING
// Get
vector<int> Hash_Table::get_values(int tableIndex) {
    vector<int> fileIndices; // Vector of indices of files with hash at tableIndex
    hashNode* entry = this->array[tableIndex];
    //cout << "Entry value " << &array[tableIndex]->value << endl;
    while (entry != NULL){
        fileIndices.push_back(entry->value);
        entry = entry->next;
    }
    return fileIndices;
}


// Function: returns the addition of ASCII values of each char in a string
// Input: string
unsigned int StringToASCII(string word){
    int strLen = word.length();
    unsigned int ascii = 0;
    for (int i = 0; i < strLen; ++i) {
        if(word[i] >= 65 && word[i] <= 90){
            ascii += (word[i]-64) * pow(26, i);
        }
        else if((word[i] >= 97 && word[i] <= 122)){
            ascii += (word[i]-96) * pow(26, i);
        }
    }
    return ascii;
}

// Function: Accepts a sequence of strings, and hashes to return the index to store the **originating file name**
// Input: Sequence of N words from input file
// Output: returns the index that the filename will be stored in
unsigned long Hash_Table::hash_function(queue<string> stringSequence) {
    int qLen = stringSequence.size();
    unsigned long hashVal = 0;
    string current;

    // Multiply the ASCII value of each word by a weight (N, N-1, ... , 1)
    for (int i = qLen; i > 0; i--) {
        current = stringSequence.front(); // pull front word out of queue
        stringSequence.pop(); // Pop this value off queue
        hashVal += (pow(29.0, (i-1)) * StringToASCII(current));
    }

    // Modulo the hashVal by a prime number to determine placement in Hash_Table
    hashVal = hashVal % 42949672; // UNCLEAR IF THIS IS APPROPRIATE, MAY NEED TO VARIABLIZE
    return hashVal;
}

void Hash_Table::addNode(unsigned long hashKey, unsigned int fileIndex) {
    // Create a new value node in the array
    hashNode* currentNode = this->array[hashKey];
    hashNode* newNode = new hashNode;
    newNode->value = fileIndex;
    newNode->next = NULL;
    //cout << "CurrentNode hashkey " << this->array[hashKey] << " newNodevalue " << newNode->value << endl;
    if (this->array[hashKey] == NULL) this->array[hashKey] = newNode;
    else{
        while(currentNode->next != NULL){
            currentNode = currentNode->next;
        }
        currentNode->next = newNode;
    }
}

// UNTESTED ############################################
// THIS FUNCTION MAY BE INSUFFICIENT FOR MILESTONE III
// Prints out the files from which each hash came
void Hash_Table::printHash() {
    hashNode* temp = NULL;
    //bool newLineFlag;

    for (int i = 0; i < this->size; ++i) {
        cout << "INDEX " << i << "| ";
        temp = this->array[i];
        while (temp != NULL){
            cout << temp->value << ", ";
            temp = temp->next;
        }
        cout << endl; // Prints carriage return when we have file vals
    }
}

// Delete all Node objects in the table
Hash_Table::~Hash_Table() {
    hashNode* current = NULL;
    hashNode* next = NULL;

    for (unsigned int i = 0; i < this->size; ++i) {
        current = array[i];
        // Loop through the LL to delete all the nodes
        while (current != NULL){
            next = current->next;
            delete(current);
            current = next;
        }
    }
}

// #############################################################################
// NODE OBJECT FUNCTIONS

// Creates a Node object with no file value
// File value can be added later using Node::set_value()
Node::Node() {
    this->value = ""; // Empty string
    this->next = NULL; // Assume new node will be at the end of LL
}

// Creates a new node object
// Input: creates a node containing a file value (hashed value determines position in table)
Node::Node(string fileValue) {
    this->value = fileValue; //
    this->next = NULL; // We are adding to the end of a LL
}

// Returns the file value stored in a node
string Node::get_value() {
    return this->value;
}

// Gets the pointer to the next node in LL
// Returns NULL if calling node is the last in the linked list
Node* Node::get_next() {
    return this->next; // TEST TO SEE IF THIS WORKS
}

void Node::set_value(string newValue) {
    this->value = newValue;
}

void Node::set_next(Node* nextNode) {
    this->next = nextNode;
}