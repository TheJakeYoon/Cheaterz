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


using namespace std;

// Opens a directory path, makes a vector containing all of the file names inside the dir
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

int main(int argc, char* argv[]){
    cout << "Argc: " << argc << endl;
    cout << argv[0] << endl;
    cout << argv[1] << endl;
    cout << argv[2] << endl;
    cout << argv[3] << endl;

    int sequenceLength = atoi(argv[2]); // Length of the sequence
    int occurrences = atoi(argv[3]); // Threshold for minimum number of overlapping occurrences


    // Prints the names of all of the files in the directory "dir" (from string argument)
    string dir = string(argv[1]); //argument when run, directory holding the text files
    vector<string> files = vector<string>();
    getdir(dir,files);

    cout << "Files in directory: " << dir << endl;
    dir.append("\\"); // Append directory delimiter (escaped)

    for (unsigned int i = 0;i < files.size();i++) {
        cout << i << ": " << files[i] << endl;
        printSequence(dir, files[i], sequenceLength);
    }


//    printSequence(dir, files[2], sequenceLength); // Prints only the first length 6 sequence of words in files[2]
//    printSequences(dir, files[2], 10); // Prints ALL sequences of length 10 in files

	return 0;
}
