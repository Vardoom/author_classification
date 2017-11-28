#ifndef BLOCK_H
#define BLOCK_H
#include <iostream>
#include <vector>

using namespace std;

class Block
{
public:

    long id;
    vector<char> textUnit;

    vector<int> charFrequency;
    vector<int> wordFrequency;
    int wordCount;
    int sentenceCount;

    Block();
    Block(long number, vector<char> text);

    void updateWordCount();
    void updateSentenceCount();
    void updateCharFrequency();
    void updateWordFrequency();

};

#endif // BLOCK_H
