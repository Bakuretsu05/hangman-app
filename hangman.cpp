#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <algorithm>
using namespace std;

enum gameState{WIN, LOSE, PLAYING};
gameState status;
string hangmanPics[7] = {" ", 
                         " O", 
                         " O\n |", 
                         " O\n/|", 
                         " O\n/|\\", 
                         " O\n/|\\\n/", 
                         " O\n/|\\\n/ \\"};
int wrong;
string word, guess;
vector<string> displayedWord, triedChar;
vector<int> occurence;

int countWords(){
    string temp;
    int count;

    ifstream myFileCount("words.txt");
    while(getline(myFileCount, temp)) count++;
    myFileCount.close();
    return count;
}

bool isWin(){
    for(auto i = displayedWord.begin(); i != displayedWord.end(); i++){
        if(*i == "_") return false;
    }
    return true;
}

void setup(){
    status = PLAYING;
    wrong = 0;

    ifstream myFile("words.txt");

    // picks a random word in "words.txt"
    srand(time(NULL)); // Seed the time
    int randNum = rand() % countWords() + 1;
    for(int i = 0; i < randNum; i++){
        getline(myFile, word);
    }

    // setup the underline
    for(int i = 0; i < word.size(); i++){
        displayedWord.push_back("_");
    }

    myFile.close();
}

void drawAndInput(){
    system("cls");
    cout << "____________Hangman Game____________" << endl;
    cout << "-> Tried Character: ";
    for(auto i = triedChar.begin(); i != triedChar.end(); i++){
        cout << *i << ", ";
    }

    cout << endl << hangmanPics[wrong] << endl << endl;
    
    for(auto i = displayedWord.begin(); i != displayedWord.end(); i++){
        cout << *i << " ";
    }

    cout << endl << "Please guess a letter: "; cin >> guess;
}

void logic(){
    if(word.find(guess) != string::npos){
        occurence.clear();
        int found;
        int startPos = 0;
        while(true){
            found = word.find(guess, startPos);
            if(found >= 0){
                occurence.push_back(found);
                startPos = found + 1;
            }
            else break;
        }
        for (auto i = occurence.begin(); i != occurence.end(); ++i){
            displayedWord[*i] = word[*i];
        }
    }
    else {
        wrong++;

        // confirm if char has not existed yet before pushing
        if(find(triedChar.begin(), triedChar.end(), guess) == triedChar.end()) 
            triedChar.push_back(guess);
    }

    if(wrong >= (sizeof(hangmanPics)/sizeof(hangmanPics[0]))) status == LOSE;
    if(isWin()) status = WIN;
}

int main(){
    setup();
    while(status == PLAYING){
        drawAndInput();
        logic();
    }

    if(status == WIN){
        cout << "grats, flite could do it faster tho" << endl;
        cout << "the word was \"" << word << "\"" << endl;
        system("pause");
    }
    else {
        cout << "The man is dead, flite couldve solved that" << endl;
        system("pause");
    }

    return 0;
}