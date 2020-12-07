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
#include <math.h>
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

//compares time between using heap and tree
void timeComp(microseconds timeHeap, microseconds timeTree) {
	if (timeHeap.count() < timeTree.count()) {
		cout << "Tree is " << ((timeHeap.count()-timeTree.count())/timeHeap.count())*100 << "% faster." << endl;
	} else {
		cout << "Heap is " << ((timeTree.count()-timeHeap.count())/timeTree.count())*100 << "% faster." << endl;
	}
}


spell checker submenu
	runs continuously until \back
	similar to definition finder

void spellChecker(string mode) {
	string spellCheck = "";
	while (spellCheck != "\\Back") {
		cout << "Type '\\Back' to return to the Main Menu";
		cout << "\nEnter your input for spellchecking:" << endl;
		cin >> spellCheck;
		if (spellCheck == "\\Back") {
			return;
		}
		string correction = spellCheck;
		microseconds spellCheckDurationHeap, spellCheckDurationTree;
		if (mode == "Heap" || mode == "Comparison") {
			auto start = high_resolution_clock::now();
			//correction = spellCheckHeap(spellCheck)
			auto stop = high_resolution_clock::now();
			spellCheckDurationHeap = duration_cast<microseconds>(stop - start);
		}
		else if (mode == "Tree" || mode == "Comparison") {
			auto start = high_resolution_clock::now();
			//correction = spellCheckTree(spellCheck)
			auto stop = high_resolution_clock::now();
			spellCheckDurationTree = duration_cast<microseconds>(stop - start);
		}
		if (correction == spellCheck) {
			cout << "Your input, '" << spellCheck << "', is spelled correctly." << endl;
		}
		else {
			cout << "Correct spelling: " << correction << endl;
		}

		if (mode == "Heap" || mode == "Comparison") {
			cout << "It took " << spellCheckDurationHeap.count() << " microseconds using Heap mode." << endl;
		}
		else if (mode == "Tree" || mode == "Comparison") {
			cout << "It took " << spellCheckDurationTree.count() << " microseconds using Tree mode." << endl;
		}
		if (mode == "Comparison") {
			timeComp(spellCheckDurationHeap, spellCheckDurationTree);
		}
	}
	return;
}

//these should be class functions
string spellCheckHeap(string word) {
	string def = "DNE";
	//def = heap.definition
	//return def
}
string spellCheckTree(string word) {
	string def = "DNE";
	//def = tree.definition
	//return def
}

//spell checker without the submenu
//has different logic at the correction output stage?
void spellChecker(string mode, string input) {
	string correction = input;
	microseconds spellCheckDurationHeap, spellCheckDurationTree;
	if (mode == "Heap" || mode == "Comparison") {
		auto start = high_resolution_clock::now();
		//correction = spellCheckHeap(input)
		auto stop = high_resolution_clock::now();
		spellCheckDurationHeap = duration_cast<microseconds>(stop - start);
	}
	else if (mode == "Tree" || mode == "Comparison") {
		auto start = high_resolution_clock::now();
		//correction = spellCheckTree(input)
		auto stop = high_resolution_clock::now();
		spellCheckDurationTree = duration_cast<microseconds>(stop - start);
	}
	cout << "Correct spelling: " << correction << endl;

	if (mode == "Heap" || mode == "Comparison") {
		cout << "It took " << spellCheckDurationHeap.count() << " microseconds using Heap mode." << endl;
	}
	else if (mode == "Tree" || mode == "Comparison") {
		cout << "It took " << spellCheckDurationTree.count() << " microseconds using Tree mode." << endl;
	}
	if (mode == "Comparison") {
		timeComp(spellCheckDurationHeap, spellCheckDurationTree);
	}
}

//these should be class functions
string findDefinitionHeap(string word) {
	string def = "DNE";
	//def = heap.definition
	//return def
}
string findDefinitionTree(string word) {
	string def = "DNE";
	//def = tree.definition
	//return def
}

string definitionFinder(string mode, string input) {
	string def = "DNE";
	microseconds findDefDurationHeap, findDefDurationTree;
	if (mode == "Heap" || mode == "Comparison") {
		auto start = high_resolution_clock::now();
		def = findDefinitionHeap(input); //**simple, returns definition
		auto stop = high_resolution_clock::now();
		findDefDurationHeap = duration_cast<microseconds>(stop - start);
	}
	else if (mode == "Tree" || mode == "Comparison") {
		//find using tree *comparison will run both
		auto start = high_resolution_clock::now();
		def = findDefinitionTree(input); //**simple, returns definition
		auto stop = high_resolution_clock::now();
		findDefDurationTree = duration_cast<microseconds>(stop - start);
	}

	if (def == "DNE") {//if word does not exit
		char ans;
		cout << "Your input, '" << input << "', was not found." << endl;

		if (mode == "Heap" || mode == "Comparison") {
			cout << "It took " << findDefDurationHeap.count() << " microseconds using Heap mode." << endl;
		}
		else if (mode == "Tree" || mode == "Comparison") {
			cout << "It took " << findDefDurationTree.count() << " microseconds using Tree mode." << endl;
		}
		if (mode == "Comparison") {
			timeComp(findDefDurationHeap, findDefDurationTree);
		}
		cout << "Would you like to enter Spell Checker mode? (Y/N)" << endl;
		cin >> ans;
		if (ans == 'Y') {
			spellChecker(mode, input);
		}
	}
	else {//if word exists
		cout << def << endl;
		if (mode == "Heap" || mode == "Comparison") {
			cout << "It took " << findDefDurationHeap.count() << " microseconds to find the defintion using Heap mode." << endl;
		}
		else if (mode == "Tree" || mode == "Comparison") {
			cout << "It took " << findDefDurationTree.count() << " microseconds to find the defintion using Tree mode." << endl;
		}
		if (mode == "Comparison") {
			timeComp(findDefDurationHeap, findDefDurationTree);
		}
	}
}

int main() {
	//reads file and adds to Data Structures, tracking time it takes
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
	timeComp(heapDuration, treeDuration);

	string mode = "Heap";
	string input = "";
	while (input != "\\Exit") {
		cout << "\nWelcome to the Language Master's Dictionary and Spell Checker!";
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
		}
		else if (input == "\\Spell Checker") {
			spellChecker(mode);//enter spell checker mode
		}
		else if (input == "1") {//change to heap mode
			if (mode == input) {
				cout << "It is already in Heap mode!" << endl;
			}
			else {
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
		}
		else if (input == "2") {//change to tree mode
			if (mode == input) {
				cout << "It is already in AVL Tree mode!" << endl;
			}
			else {
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
		}
		else if (input == "3") {//change to comparison mode
			if (mode == input) {
				cout << "It is already in Comparison mode!" << endl;
			}
			else {
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
		}
		else if (input == "\\Exit") {//exit program
			return 0;
		}
		else {//finds definition
			definitionFinder(mode, input);
		}
	}
	return 0;
}
