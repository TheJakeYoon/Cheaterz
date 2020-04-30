// Hash.h
// Kellan Cerveny and Jake Yoon
// Priebe 312
// 30 April 2020

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

// Milestone II
// Produce a list (in order) of all the pairs of files sharing more than the argv[3] sequences in common
// Write a README discussing what the program does, how to use it, what works, bugs and other features to know while looking at the code

/* TODOs
 * 1. Create a function for hashing N word sequences in a file
 * 2. Loop through all files, testing for collisions
 * 3. Read through the hash table, make a list of all documents sharing sequences
 * 4. Analyze list, and print output based on the parameter set from argv[3]
 */


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
    unsigned int size; // HOW DO WE DETERMINE WHAT IS AN APPROPRIATE SIZE FOR THE TABLE?
    vector<Node*> array;
public:
    Hash_Table(unsigned int tableSize); // must be constructed using calculated size

    unsigned int get_size();
    Node* get_value(int index); // NOT SURE IF THIS FUNCTION IS NECESSARY

    unsigned long int hash_function(queue<string> stringSequence); // Function to hash words (may not be djb2)
    void addNode(unsigned long int hashVal, string fileName); // Adds new node on the tail

    void printHash();
    ~Hash_Table();
};


