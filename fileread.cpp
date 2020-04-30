// fileread.cpp
// Kellan Cerveny and Jake Yoon
// Priebe 312
// 30 April 2020

#include <iostream>
#include <sys/types.h>
#include <fstream>
#include <cstdlib>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <queue>
#include "fileread.h"

using namespace std;

/* This is a collection of helper functions that:
 * - Reads the input of all .txt files in a directory
 * - Creates sequences of length N based on terminal command
 * - Populates the hash table with entries from text sequences of each file
 * - Calculates the number of collisions/coocurrences of phrases between files
 * - Outputs the files with a high number of collisions in a table
 */

// Opens a directory path, makes and populates a vector containing all of the file names inside the dir
// Files 0 and 1 are . and .. respectively (current directory, parent directory)
int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}


// Helper function for hashSequences (all n-length)
void hashQueue(queue<string> seqQ){
    // Print all words in first queue
    queue<string> newQ = seqQ;
    while(!newQ.empty()){
        cout << newQ.front() << " ";
        newQ.pop();
    }
    cout << endl;
}

// hashes ALL consecutive sequences of length N from a given .txt file
// Adds hashes to hash table
// Input: directory where .txt files held, length of sequence to hash, hash table by reference
void hashFile(const string directory,const string fileName,const int seqLen, Hash_Table hash_table){

    ifstream file;
    string toOpen = directory; // Need to loop through all the file names in "files" variable
    toOpen.append(fileName);
    file.open(toOpen);
    if (!file.is_open()) return; // Failure to open the file

    string word; // receives words from file one at a time
    queue<string> strQ; // Holds queue of words taken from file
    unsigned long int hashValue;

    int index = 0; // Populate the queue with seqLen values (length of queue)
    while (file >> word && index < seqLen){
        strQ.push(word);
        index ++;
    }

    hashValue = hash_table.hash_function(strQ); // return hash value of string queue
    hash_table.addNode(hashValue, fileName); // Makes a new node in hash table with hashValue, stores fileName

    //Finish all other variations from the file
    while (file >> word){
        strQ.pop(); // Get rid of string at the front of the queue
        strQ.push(word); // Add next read-in string to back
        hashValue = hash_table.hash_function(strQ); // return hash value of string queue
        hash_table.addNode(hashValue, fileName); // Makes a new node in hash table with hashValue, stores fileName
    }
}

//Function: hashes all N-length sequences of words from all text files in the given directory
//Input: directory files are stored in, vector of all file names, length of sequence we are searching for, hash table we deposit the results in
void hashFiles(string dir, vector<string> files, int seqLen, Hash_Table hash_table){

    cout << "Files in directory: " << dir << endl; // DEBUGGING STATEMENT ####################################
    string direct = dir;
    direct.append("\\"); // Append directory delimiter (escaped) for fopen() later

    // Hash sequences of length N in all files in dir
    for (unsigned int i = 0;i < files.size();i++) {
        cout << i << ": " << files[i] << endl;
        hashFile(direct, files[i], seqLen, hash_table);
    }

    cout << "All files have been hashed." << endl;
}

