// Hash.h
// Kellan Cerveny and Jake Yoon
// Priebe 312
// 30 April 2020

#ifndef INCLUDE_HASH_H
#define INCLUDE_HASH_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sys/types.h>
#include <dirent.h>
#include <cerrno>
#include <vector>
#include <string>
#include <queue>

using namespace std;

// Stores the key:value pairs in the hash table
class Node{
private:
    string value; // File value
    Node *next;
public:
    Node();
    Node(string fileValue); // key (file of origination), value (hashed value from the file text sequence)

    string get_value(); // Gets file value stored in node
    Node* get_next(); // Easier to traverse LL for evaluation
    void set_value(string newValue);
    void set_next(Node* nextNode);
};


// The hash table is an array of linked lists
// Collisions will add a node to the end of a list
class Hash_Table
{
private:
    struct hashNode {
        float value; //Index of the file
        hashNode* next;
    };
    unsigned long size; // HOW DO WE DETERMINE WHAT IS AN APPROPRIATE SIZE FOR THE TABLE?
    vector<hashNode*> array;

public:

    Hash_Table(unsigned int sequenceLength); // must be constructed using calculated size

    unsigned long get_size();
    vector<int> get_values(int index); // NOT SURE IF THIS FUNCTION IS NECESSARY

    unsigned long hash_function(queue<string> stringSequence); // Function to hash words (may not be djb2)
    void addNode(unsigned long hashVal, unsigned int fileIndex); // Adds new node on the tail

    void printHash();
    ~Hash_Table();
};

#endif
