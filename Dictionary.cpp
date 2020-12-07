//Project 3 Main

#include <iostream>
#include <fstream>
#include <sstream> 
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <chrono>
#include <thread>
#include "Dictionary.h"
using namespace std;
using namespace this_thread; // sleep_for, sleep_until
using namespace chrono; // nanoseconds, system_clock, seconds

//read dictionary and add to Heap
void readFiletoHeap() {
    ifstream file("DictionaryFull.csv");
    file.open("DictionaryFull.csv", ios::in);
    string line, word, partOfSpeech, definition;
    while (getline(file, line)) {
        stringstream s(line);
        getline(s, word, ',');
        getline(s, partOfSpeech, ',');
        getline(s, definition, ',');
        //heap.addNode(word,partOfSpeech,definition);
    }
    file.close();
}

//read dictionary and add to AVL Tree
void readFiletoTree() {
    fstream file;
    file.open("DictionaryFull.csv", ios::in);
    string line, word, partOfSpeech, definition;
    while (getline(file, line)) {
        stringstream s(line);
        getline(s, word, ',');
        getline(s, partOfSpeech, ',');
        getline(s, definition, ',');
        //tree.addNode(word,partOfSpeech,definition);
    }
    file.close();
}

void spellChecker(string mode) {
    string spellCheck = "";
    cout << "Type '\\Back' to return to the Main Menu";
    cout << "\nEnter your input for spellchecking:" << endl;
    cin >> spellCheck;
    /*
    spellCheckWord(mode, spellCheck)
    if word found, print that word was spelled correctly
    else, print provide possible correction(s)
    */
}

void spellChecker(string mode, string input) {
    /*
    spellCheckWord(mode, input)
    print possible correction(s)
    */
}

string findDefinitionHeap(string word) {
    string def = "DNE";
    //def = heap.definition
    //return def
}

//these should be class functions
string findDefinitionTree(string word) {
    string def = "DNE";
    //def = tree.definition
    //return def
}

void timeComp(float timeHeap, float timeTree) {

}

int main() {
    auto start = high_resolution_clock::now();
    readFiletoHeap();
    auto stop = high_resolution_clock::now();
    auto heapDuration = duration_cast<microseconds>(stop - start); 
    cout << heapDuration.count() << " microseconds to create the heap dictionary." << endl;
    auto start = high_resolution_clock::now();
    readFiletoTree();
    auto stop = high_resolution_clock::now();
    auto treeDuration = duration_cast<microseconds>(stop - start); 
    cout << treeDuration.count() << " microseconds to create the tree dictionary." << endl;
    if (treeDuration.count() < heapDuration.count()) {
        cout << "Tree is " << ((heapDuration.count()-treeDuration.count())/heapDuration.count())*100 << "% faster to create." << endl;
    } else {
        cout << "Heap is " << ((treeDuration.count()-heapDuration.count())/treeDuration.count())*100 << "% faster to create." << endl;
    }
    string mode = "Heap";
    string input = "";
    while(input != "\\Exit") {
        cout << "Welcome to the Language Master's Dictionary and Spell Checker!";
        cout << "\nCurrent Mode: " << mode;
        cout << "\nType “\\Help Me” for more information"; //#1
        cout << "\nBegin typing to search for a word or definition:" << endl; //#8
        cin >> input;
        if (input == "\\Help Me") { 
            cout << "Instructions for using Dictionary and Spell Checker:";
            cout << "\n\tType '[a word]' to check if it is a word and find the definition"; //#8
            cout << "\n\tType '\\Spell Checker' to enter words, sentences, or longer"; //#2
            cout << "\n\tType '1' for Heap dictionary mode"; //#3
            cout << "\n\tType '2' for AVL Tree dictionary mode"; //#4
            cout << "\n\tType '3' for a comparison mode of Heap and AVL Tree Structures"; //#5
            cout << "\n\tType '\\Exit' to exit the program anytime" << endl; //#7
        } else if (input == "\\Spell Checker") {
            spellChecker(mode);
        } else if (input == "1") {
            if (mode == input) {
               cout << "It is already in Heap mode!" << endl; 
            } else {
                mode = "Heap";
                cout << "Changing mode to Heap"; 
                sleep_for(nanoseconds(50));
                cout << "."; 
                sleep_for(nanoseconds(50));
                cout << "."; 
                sleep_for(nanoseconds(50));
                cout << "."; 
                sleep_for(nanoseconds(50));
            }
        } else if (input == "2") {
            if (mode == input) {
               cout << "It is already in AVL Tree mode!" << endl; 
            } else {
                mode = "AVL";
                cout << "Changing mode to AVL"; 
                sleep_for(nanoseconds(50));
                cout << "."; 
                sleep_for(nanoseconds(50));
                cout << "."; 
                sleep_for(nanoseconds(50));
                cout << "."; 
                sleep_for(nanoseconds(50));
            }
        } else if (input == "3") {
            if (mode == input) {
               cout << "It is already in Comparison mode!" << endl; 
            } else {
                mode = "Comparison";
                cout << "Changing mode to Comparison"; 
                sleep_for(nanoseconds(50));
                cout << "."; 
                sleep_for(nanoseconds(50));
                cout << "."; 
                sleep_for(nanoseconds(50));
                cout << "."; 
                sleep_for(nanoseconds(50));
            }
        } else if (input == "\\Exit") {
            return 0;
        } else {
            string def = "DNE";
            if (mode == "Heap" || mode == "Comparison") {
                auto start = high_resolution_clock::now();
                def = findDefinitionHeap(input); //**simple, returns definition
                auto stop = high_resolution_clock::now();
                auto findDefDurationHeap = duration_cast<microseconds>(stop - start); 
            } else if (mode == "Tree" || mode == "Comparison") {
                //find using tree *comparison will run both
                auto start = high_resolution_clock::now();
                def = findDefinitionTree(input); //**simple, returns definition
                auto stop = high_resolution_clock::now();
                auto findDefDurationTree = duration_cast<microseconds>(stop - start); 
            }
        
            if (def == "DNE") {
                char ans;
                cout << "Your input, '" << input << "', was not found. It took " << findDefDuration.count() << " microseconds. Would you like to enter Spell Checker mode? (Y/N)" << endl;
                cin >> ans;
                if (ans == 'Y') {
                    //spellChecker(mode, input);
            } else {
                cout << input << ": " << def << endl;
                if (mode == "Heap" || mode == "Comparison") {
                    cout << "It took " << findDefDurationHeap.count() << " microseconds to find the defintion using Heap mode." << endl;
                    auto findDefDurationHeap = duration_cast<microseconds>(stop - start); 
                } else if (mode == "Tree" || mode == "Comparison") {
                    cout << "It took " << findDefDurationTree.count() << " microseconds to find the defintion using Tree mode." << endl;
                }
                if (mode == "Comparison") {

                }
                
            }


        }
    }
    return 0;
}
