// Driver for Cheaters program
// Kellan Cerveny and Jake Yoon
// Priebe 312 4/19/2020

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sys/types.h>
#include <dirent.h>
#include <cerrno>
#include <vector>
#include <string>
#include <queue>

#include "Hash.h"
#include "fileread.h"

using namespace std;


// argv[1] -> string, directory path
// argv[2] -> int, length of sequence
// argv[3] -> int, number of overlapping occurrences between files
int main(int argc, char* argv[]){

    //int sequenceLength = atoi(argv[2]); // Length of the sequence
    int sequenceLength = 6;
    //int occurrences = atoi(argv[3]); // Threshold for minimum number of overlapping occurrences
    int occurrences = 200;
    //string dir = argv[1]; //argument when run, directory holding the text files
    string dir = "../sm_doc_set/";

    vector<string> files = vector<string>(); // Vector where we store the names of all files in "dir"
    getdir(dir,files); //Populates the "files" vector with names of files in directory "dir"

    Hash_Table table(6); // How do we determine the size of the table?

    hashFiles(dir, files, sequenceLength, table); // hashes all N-length sequences of words from all text files in the given directory
    //table.printHash(); // DEBUGGING TOOL

    // MILESTONE III
    // Identify suspicious cases based on hash table (use a 2D array to store count of similarities)
    // Print pairs of suspicious files in order
    // Produce meaningful output on small set of documents (~25)
    // Write a README for this program
    // Extra Credit: make solution stable for large/medium sets of documents

    vector<vector<int>> collisionMatrix(files.size(), vector<int> (files.size(), 0));
    populateMatrix(table, collisionMatrix);
    printCollisions(collisionMatrix); // DEBUGGING TOOL

    printFrequencies(occurrences, collisionMatrix, files);

    printSortedFrequencies(occurrences, collisionMatrix, files);
	return 0;
}
