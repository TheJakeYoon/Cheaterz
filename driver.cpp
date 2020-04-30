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
#include "fileread.cpp"

using namespace std;

// reads file and outputs one word at a time
void readFile(string directory, string fileName)
{
    ifstream file;
    string toOpen = directory.append(fileName); // Variablized both particular file and directory
    file.open (toOpen);
    if (!file.is_open()) return;

    string word;
    while (file >> word)
    {
        cout<< word << '\n';
    }
}

// Prints first consecutive sequence of length N in a given .txt file
void printSequence(string directory, string fileName, int seqLen){
    ifstream file;
    string toOpen = directory.append(fileName);
    file.open(toOpen);
    if (!file.is_open()) return; // Failure to open the file

    string word; // receives words from file one at a time
    queue<string> strQ; // Holds queue of words taken from file

    int index = 0; // Creates our full-length queue
    while (file >> word && index < seqLen){
        strQ.push(word);
        index ++;
    }
    while(!strQ.empty()){
        cout << strQ.front() << " ";
        strQ.pop();
    }
    cout << endl;

}

// Helper function for printSequenceS (all n-length)
void printQueue(queue<string> seqQ){
    // Print all words in first queue
    queue<string> newQ = seqQ;
    while(!newQ.empty()){
        cout << newQ.front() << " ";
        newQ.pop();
    }
    cout << endl;
}

// Prints ALL consecutive sequences of length N from a given .txt file
void printSequences(string directory, string fileName, int seqLen){
    ifstream file;
    string toOpen = directory.append(fileName);
    file.open(toOpen);
    if (!file.is_open()) return; // Failure to open the file

    string word; // receives words from file one at a time
    queue<string> strQ; // Holds queue of words taken from file

    int index = 0;
    while (file >> word && index < seqLen){
        strQ.push(word);
        index ++;
    }
    printQueue(strQ);

    //Finish all other variations from the file
    while (file >> word){
        strQ.pop(); // Get rid of string at the front of the queue
        strQ.push(word); // Add next read-in string to back
        printQueue(strQ); // Print the new sequence
    }

}



// argv[1] -> string, directory path
// argv[2] -> int, length of sequence
// argv[3] -> int, number of overlapping occurrences between files

int main(int argc, char* argv[]){

    int sequenceLength = atoi(argv[2]); // Length of the sequence
    int occurrences = atoi(argv[3]); // Threshold for minimum number of overlapping occurrences
    string dir = string(argv[1]); //argument when run, directory holding the text files

    vector<string> files = vector<string>(); // Vector where we store the names of all files in "dir"
    getdir(dir,files); //Populates the "files" vector with names of files in directory "dir"

    Hash_Table table(25 * 25); // How do we determine the size of the table?
//    cout << table.get_value(2) << " Table at 2" << endl;

    hashFiles(dir, files, sequenceLength, table); // hashes all N-length sequences of words from all text files in the given directory












//    printSequence(dir, files[2], sequenceLength); // Prints only the first length 6 sequence of words in files[2]
//    printSequences(dir, files[2], 10); // Prints ALL sequences of length 10 in files

	return 0;
}
