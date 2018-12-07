//
// Created by Amrith Lotlikar on 12/6/2018.
//APL746
//with code given by Dr.Priebe
//

#ifndef CHEATERS_HASH_H
#define CHEATERS_HASH_H
#include <string>
#include <vector>

using namespace std;

class HashTable{
private:
    struct hashNode{
        int fileNumber;
        hashNode *next;
    };
    static const int HASH_SIZE = 156257;
    static const int ASCII_WEIGHT = 256;
    hashNode* table[HASH_SIZE];
    int hash(string word);
    vector<hashNode*> nodes;
public:
    vector<int> addEntry(string word, int fileNumber);
    HashTable();
    ~HashTable();
};

HashTable::HashTable() {
    for(int i = 0; i < HASH_SIZE; i++){
        table[i] = NULL;
    }
}
HashTable::~HashTable() {
    for(int i = nodes.size() - 1; i > 0; i--){
        delete nodes[i];
    }
}

int HashTable::hash(string word) {
    int value = 0;
    for(int i = 0; i < word.length(); i++){
        char letter = word.at(i);
        if(int(letter) > 0){
            value *= ASCII_WEIGHT;
            value += int(letter);
            value %= HASH_SIZE;
        }
    }
    return value;

}

vector<int> HashTable::addEntry(string word, int fileNumber) {
    vector<int> collisions;
    hashNode *node = new hashNode;
    node -> fileNumber = fileNumber;
    node -> next = NULL;
    int hash = this->hash(word);
    if(table[hash] == NULL){
        table[hash] = node;
    }
    else{
        hashNode *tracker = table[hash];
        collisions.push_back(tracker->fileNumber);
        while(tracker->next != NULL){
            tracker = tracker->next;
            collisions.push_back(tracker->fileNumber);
        }
        tracker -> next = node;
    }

    nodes.push_back(node);
    return collisions;
}
#endif //CHEATERS_HASH_H
