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
int wrong;
string word, guess;
vector<string> displayedWord, triedChar;
vector<int> occurence;

void drawHangman(int state){
    if (state == 0){
        cout << " +--------+      " << endl;
        cout << " |        |      " << endl;
        cout << " |        |      " << endl;
        cout << " |               " << endl;
        cout << " |               " << endl;
        cout << " |               " << endl;
        cout << " |               " << endl;
        cout << " |               " << endl;
        cout << " |               " << endl;
        cout << " |               " << endl;
        cout << " #==============#" << endl;
    }
    else if (state == 1){
        cout << " +--------+      " << endl;
        cout << " |        |      " << endl;
        cout << " |        |      " << endl;
        cout << " |        0      " << endl;
        cout << " |               " << endl;
        cout << " |               " << endl;
        cout << " |               " << endl;
        cout << " |               " << endl;
        cout << " |               " << endl;
        cout << " |               " << endl;
        cout << " #==============#" << endl;
    }
    else if (state == 2){
        cout << " +--------+      " << endl;
        cout << " |        |      " << endl;
        cout << " |        |      " << endl;
        cout << " |        0      " << endl;
        cout << " |        |      " << endl;
        cout << " |        |      " << endl;
        cout << " |               " << endl;
        cout << " |               " << endl;
        cout << " |               " << endl;
        cout << " |               " << endl;
        cout << " #==============#" << endl;
    }

    else if (state == 3){
        cout << " +--------+      " << endl;
        cout << " |        |      " << endl;
        cout << " |        |      " << endl;
        cout << " |        0      " << endl;
        cout << " |       /|      " << endl;
        cout << " |        |      " << endl;
        cout << " |               " << endl;
        cout << " |               " << endl;
        cout << " |               " << endl;
        cout << " |               " << endl;
        cout << " #==============#" << endl;
    }

    else if (state == 4){
        cout << " +--------+      " << endl;
        cout << " |        |      " << endl;
        cout << " |        |      " << endl;
        cout << " |        0      " << endl;
        cout << " |       /|\\    " << endl;
        cout << " |        |      " << endl;
        cout << " |               " << endl;
        cout << " |               " << endl;
        cout << " |               " << endl;
        cout << " |               " << endl;
        cout << " #==============#" << endl;
    }

    else if (state == 5){
        cout << " +--------+      " << endl;
        cout << " |        |      " << endl;
        cout << " |        |      " << endl;
        cout << " |        0      " << endl;
        cout << " |       /|\\    " << endl;
        cout << " |        |      " << endl;
        cout << " |       /       " << endl;
        cout << " |               " << endl;
        cout << " |               " << endl;
        cout << " |               " << endl;
        cout << " #==============#" << endl;
    }

    else if (state == 6){
        cout << " +--------+      " << endl;
        cout << " |        |      " << endl;
        cout << " |        |      " << endl;
        cout << " |        0      " << endl;
        cout << " |       /|\\    " << endl;
        cout << " |        |      " << endl;
        cout << " |       / \\    " << endl;
        cout << " |               " << endl;
        cout << " |               " << endl;
        cout << " |               " << endl;
        cout << " #==============#" << endl;
    }
}


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
        if(word[i] == ' ') displayedWord.push_back(" ");
        else displayedWord.push_back("_");
    }

    myFile.close();
}

void drawGUI(){
    system("cls");
    cout << "____________Hangman Game____________" << endl;
    cout << "-> Tried Character: ";
    for(auto i = triedChar.begin(); i != triedChar.end(); i++){
        cout << *i << ", ";
    }
    cout << endl << endl;
    drawHangman(wrong);
    cout << endl;
    
    for(auto i = displayedWord.begin(); i != displayedWord.end(); i++){
        cout << *i;
    }

    if(status == PLAYING){
        cout << endl << "Guess a letter: "; 
        cin >> guess;
    }
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

    if(wrong == 6){
        status = LOSE;
        drawGUI();
    }
    if(isWin()){
        status = WIN;
        drawGUI();
    }
}

int main(){
    setup();
    while(status == PLAYING){
        drawGUI();
        logic();
    }

    if(status == WIN){
        cout << endl << "You WON!!!" << endl;
        system("pause");
    }
    else {
        cout << endl << "The man is dead, You Lost..." << endl;
        cout << "The word was \"" << word << "\"." << endl;
        system("pause");
    }

    return 0;
}