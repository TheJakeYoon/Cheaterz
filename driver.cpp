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

// Prints all consecutive sequences of length N in a given .txt file
void printSequence(string directory, string fileName, int seqLen){
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
    // Print all words in the queue
    while(!strQ.empty()){
        cout << strQ.front() << " ";
        strQ.pop();
    }

}


int main(int argc, char* argv[]){
    cout << "Argc: " << argc << endl;
    cout << argv[0] << endl;
    cout << argv[1] << endl;
    cout << argv[2] << endl;
    cout << argv[3] << endl;


    // Prints the names of all of the files in the directory "dir" (from string argument)
    string dir = string(argv[1]); //argument when run, directory holding the text files
    vector<string> files = vector<string>();
    getdir(dir,files);
    cout << "Files in directory: " << dir << endl;
    for (unsigned int i = 0;i < files.size();i++) {
        cout << i << ": " << files[i] << endl;
    }

    // Open and read from contents of file
    dir.append("\\"); // Append directory delimiter (escaped)

    printSequence(dir, files[2], 10);

	return 0;
}
