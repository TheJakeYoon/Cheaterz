// fileread.h
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
#include "Hash.h"

using namespace std;


int getdir (string dir, vector<string> &files);

void hashFile(const string directory,const string fileName,unsigned int fileIndex, const int seqLen, Hash_Table &hash_table);

void hashFiles(string dir, vector<string> files, int seqLen, Hash_Table &hash_table);

void printCollisions(vector<vector<int>> collMatrix);

void populateMatrix(Hash_Table &hashTable, vector<vector<int>> &frequencies);

void printFrequencies(const int occurrences, vector<vector<int>> collisionsMatrix, vector<string> files);

