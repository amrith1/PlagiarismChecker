//Created by Amrith Lotlikar
//APL746
//with code given by Dr.Priebe




#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include "hash.h"
#include <fstream>
#include <queue>
#include <cstring>
#include <cstdlib>
#include <stdlib.h>


using namespace std;
/*function... might want it in some class?*/

struct collisionRecord{
    int file_one;
    int file_two;
    int collisions;
};

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

void handleFile(int **collisions, HashTable &hashTable, int words, ifstream &file, int fileNumber){
    string phrase[words];
    int first_word = words - 1;
    string nextWord;
    for(int i = 0; i < words - 1; i++){
        if(file >> nextWord){
            phrase[i] = nextWord;
        }
        else{
            return;
        }
    }
    while(file>>nextWord){
        phrase[first_word] = nextWord;
        first_word = (first_word + 1) % words;
        string hashPhrase;
        for(int i = first_word; i < first_word + words; i++){
            hashPhrase += phrase[i % words];
            hashPhrase += " ";
        }
        vector<int> response = hashTable.addEntry(hashPhrase, fileNumber);
        for(int j = 0; j < response.size(); j++){
            collisions[response[j]][fileNumber]++;
        }
    }
}

int main(int argc, char* argv[]) {
    int words = atoi(argv[2]);
    int standard = atoi(argv[3]);
    string dir = string(argv[1]);
    vector<string> files = vector<string>();
    getdir(dir,files);
    int **collisions = new int* [files.size()];
    for(int i = 0; i < files.size(); i++){
        collisions[i] = new int[files.size()];
        for(int j = 0; j < files.size(); j++){
            collisions[i][j] = 0;
        }
    }
    HashTable hashTable;
    for (int i = 2; i < files.size(); i++) {
        string filename = dir + "/" + files[i];
        ifstream file(filename.c_str());
        handleFile(collisions, hashTable, words, file, i);
        file.close();
    }


    collisionRecord record[files.size() * files.size()];
    for(int i = 0; i < files.size(); i++){
        for(int j = 0; j < files.size(); j++){
            if(i < 2 || j < 2 || i >= j){
                record[i *files.size() + j].collisions = -10000;
            }
            else{
                record[i *files.size() + j].file_one = i;
                record[i *files.size() + j].file_two = j;
                record[i *files.size() + j].collisions = collisions[i][j];
            }
        }
    }
    for(int i = 0; i < files.size()* files.size(); i++){
        for(int j = 0; j < files.size() * files.size() - 1; j++){
            if (record[j].collisions < record[j + 1].collisions){
                collisionRecord holder = record[j];
                record[j] = record[j+1];
                record[j+1] = holder;
            }
        }
    }
    for(int i = 0; i < files.size() * files.size(); i++){
        if(record[i].collisions > standard){
            cout << record[i].collisions << ": " << files[record[i].file_one] << "., " << files[record[i].file_two]<< endl;
        }
        else break;
    }

    return 0;
}