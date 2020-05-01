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

void hashQueue(queue<string> seqQ);

void hashFile(const string directory,const string fileName,const int seqLen, Hash_Table &hash_table);

void hashFiles(string dir, vector<string> files, int seqLen, Hash_Table &hash_table);


