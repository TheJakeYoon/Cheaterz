// Hash.cpp
// Kellan Cerveny and Jake Yoon
// Priebe 312
// 30 April 2020

#include "Hash.h"
#include <iostream>
#include <cstdlib>

using namespace std;

// HASH_TABLE CLASS FUNCTIONS
Hash_Table::Hash_Table(unsigned int tableSize) {
    size = tableSize; // tableSize needs to be correctly calculated in advance
    vector<Node*> table(tableSize);// Set all pointers in the array to NULL to show they are unused
    array = table;
}

unsigned int Hash_Table::get_size() {
    return this->size;
}

Node* Hash_Table::get_value(int index) {
    return this->array[index];
}

// Function: returns the addition of ASCII values of each char in a string
// Input: string
unsigned int StringToASCII(string word){
    int strLen = word.length();
    unsigned int ascii = 0;
    for (int i = 0; i < strLen; ++i) {
        ascii += word[i];
    }
    return ascii;
}

// Function: Accepts a sequence of strings, and hashes to return the index to store the **originating file name**
// Input: Sequence of N words from input file
// Output: returns the index that the filename will be stored in
unsigned long int Hash_Table::hash_function(queue<string> stringSequence) {
    int qLen = stringSequence.size();
    unsigned long int hashVal = 0;
    string current;

    // Multiply the ASCII value of each word by a weight (N, N-1, ... , 1)
    for (int i = qLen; i >= 0; i--) {
        current = stringSequence.front(); // pull front word out of queue
        stringSequence.pop(); // Pop this value off queue
        hashVal += i * StringToASCII(current);
    }

    // Modulo the hashVal by a prime number to determine placement in Hash_Table
    hashVal = hashVal % 599; // UNCLEAR IF THIS IS APPROPRIATE, MAY NEED TO VARIABLIZE
    return hashVal;
}

// THIS FUNCTION MAY BE INSUFFICIENT FOR MILESTONE III
// Prints out the files from which each hash came
void Hash_Table::printHash() {
    Node* currentNode = NULL;
    Node* nextNode = NULL;
    bool newLineFlag;

    for (unsigned int i = 0; i < this->size; ++i) {
        newLineFlag = false; // Flag down initially
        currentNode = array[i];
        while (currentNode != NULL){
            newLineFlag = true; // Put the flag up
            nextNode = currentNode->get_next();
            cout << currentNode->get_value() << ", ";
            currentNode = nextNode;
        }
        if (newLineFlag) cout << endl; // Prints carriage return when we have file vals
    }
}

// Delete all Node objects in the table
Hash_Table::~Hash_Table() {
    Node* currentNode = NULL;
    Node* nextNode = NULL; // Used to delete all nodes in LL

    for (unsigned int i = 0; i < this->size; ++i) {
        currentNode = array[i];
        // Loop through the LL to delete all the nodes
        while (currentNode != NULL){
            nextNode = currentNode->get_next();
            delete(currentNode);
            currentNode = nextNode;
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