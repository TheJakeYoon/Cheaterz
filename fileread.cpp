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
    // need to remove . and ..
    files.erase(files.begin(), files.begin() + 2);
    closedir(dp);
    return 0;
}

// hashes ALL consecutive sequences of length N from a given .txt file
// Adds hashes to hash table
// Input: directory where .txt files held, name of file to open, index of file to be stored, length of sequence to hash, hash table by reference
void hashFile(string directory,string fileName, unsigned int fileIndex, int seqLen, Hash_Table &hash_table){

    ifstream file;
    string toOpen = directory; // Need to loop through all the file names in "files" variable
    toOpen.append(fileName);
    file.open(toOpen);
    if (!file.is_open()){
        cout << "Unable to open file: " << toOpen << endl;
        return; // Default return current and parent directory
    }
    string word; // receives words from file one at a time
    queue<string> strQ; // Holds queue of words taken from file
    unsigned long int hashValue;

    int index = 0; // Populate the queue with seqLen values (length of queue)
    while (file >> word && index < seqLen){
        strQ.push(word);
        index ++;
    }
    //printQueue(strQ); // DEBUGGING TOOL
    hashValue = hash_table.hash_function(strQ); // return hash value of string queue
    //cout << "HashValue     " << hashValue << "      ";
    hash_table.addNode(hashValue, fileIndex); // Makes a new node in hash table with hashValue, stores fileName
    //cout << hast_table.at(hash_table.get_values(fileIndex)) << endl;
    //Finish all other variations from the file
    while (file >> word){
        strQ.pop(); // Get rid of string at the front of the queue
        strQ.push(word); // Add next read-in string to back
        hashValue = hash_table.hash_function(strQ); // return hash value of string queue
        hash_table.addNode(hashValue, fileIndex); // Makes a new node in hash table with hashValue, stores fileName
    }
}

//Function: hashes all N-length sequences of words from all text files in the given directory
//Input: directory files are stored in, vector of all file names, length of sequence we are searching for, hash table we deposit the results in
void hashFiles(string dir, vector<string> files, int seqLen, Hash_Table& hash_table){
    string direct = dir;
    //direct.append("\\"); // Append directory delimiter (escaped) for fopen() later

    //cout << direct << endl;
    //cout << files.size() << endl;
    // Hash sequences of length N in all files in dir
    for (unsigned int i = 0;i < files.size();i++) {
        //cout << i << ": " << files[i] << endl; // DEBUGGING: Outputs file name and index
        hashFile(direct, files[i], i, seqLen, hash_table);
    }
}


// Function: DEBUGGING TOOL, shows matrix collisions
// Input: matrix with frequencies of collisions between files
void printCollisions(vector<vector<int>> collMatrix){
    cout << "   ";
    for (int i = 0; i < collMatrix.size(); ++i) {
        cout << i << " ";
    }
    cout << endl;
    for (int j = 0; j < collMatrix.size(); ++j) {
        cout << "__";
    }
    cout << endl;
    for (int k = 0; k < collMatrix.size(); ++k) {
        cout << k << "| ";
        for (int i = 0; i < collMatrix.size(); ++i) {
            cout << collMatrix[k][i] << " ";
        }
        cout << endl;
    }


}


// Function: iterates through hash table, adds file collisions to matrix
// Input: hash table holding collisions, size of NxN matrix to show file overlap,NxN matrix with number of collisions between files
// Output:
void populateMatrix(Hash_Table &hashTable, vector<vector<int>> &frequencies){
    vector<int> collisions;
    int row;
    int col;

    // Iterate through the hash table, plot frequencies of overlap
    for (int i = 0; i < (42949672); ++i) {
        // When hash table is not empty, add fileIndex values to matrix
        if(!hashTable.get_values(i).empty()){
            collisions = hashTable.get_values(i);

            //For each file index, add collisions with following indices
            for (int j = 0; j < collisions.size(); ++j) {
                row = collisions[j];
                for (int k = j; k < collisions.size(); ++k) {
                    col = collisions[k]; //column for collision

                    // DO WE NEED TO REMOVE REPEAT COLLISIONS WITH OTHER FILES?
                    if (collisions[j] != collisions[k]){
                        //cout << collisions[j] << " " << collisions[k] << endl;
                        frequencies[row][col] ++; //Add a collision between two files
                    }
                }
            }

        }
    }
//    printCollisions(frequencies); // Displays file collisions in a matrix
}


// Function: Create an N*N matrix, populate with frequencies of colliding sequences between files
// Input: vector of files, hash table holding overlap occurrences,
void printFrequencies(const int occurrences, vector<vector<int>> collisionsMatrix, vector<string> files){
    for (unsigned int i = 0; i < collisionsMatrix.size(); ++i) {
        for (unsigned int j = i; j < collisionsMatrix.size(); ++j) {

            if (collisionsMatrix[i][j] >= occurrences){
                // Print: #, file1, file2
                cout << collisionsMatrix[i][j] << ": ";
                cout << files[i] << ", ";
                cout << files[j] << endl;
            }
        }
    }
}
// ******************************************
// Print Sorted Array Using MergeSort

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}
void printSortedFrequencies(const int occurrences, vector<vector<int>> collisionsMatrix, vector<string> files){

    int sortedArray[(collisionsMatrix.size()*collisionsMatrix.size())/2];
    int size = 0;
    for (unsigned int i = 0; i < collisionsMatrix.size(); ++i) {
        for (unsigned int j = i; j < collisionsMatrix.size(); ++j) {

            if (collisionsMatrix[i][j] >= occurrences){
                sortedArray[size] = collisionsMatrix[i][j];
                size++;

            }
        }
    }

    //MergeSort

    size--;
    mergeSort(sortedArray, 0, size);
    cout << "Sorted Array" << endl;
    while(size > 0){
        for (int i = 0; i < collisionsMatrix.size(); ++i) {
            for (int j = i; j < collisionsMatrix.size(); ++j) {
                    if (collisionsMatrix[i][j] == sortedArray[size] && sortedArray[size] > occurrences) {
                        cout << sortedArray[size];
                        cout << ": " << files[i] << ", " << files[j] << endl;
                        size--;
                    }
                }
            }
        }
}

