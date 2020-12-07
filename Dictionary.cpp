//Project 3 Main

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <math.h>
#include "Dictionary.h"
using namespace std;
using namespace this_thread; // sleep_for, sleep_until
using namespace chrono; // nanoseconds, system_clock, seconds

//read dictionary and add to Trie
Node* readFiletoTrie(Node* root) {
	ifstream file("DictionaryFull.csv");
	file.open("DictionaryFull.csv", ios::in);
	string line, word, partOfSpeech, definition;
	while (getline(file, line)) {
		stringstream s(line);
		getline(s, word, ',');
		getline(s, partOfSpeech, ',');
		getline(s, definition);
		//insertTrie(root, word,partOfSpeech,definition);
	}
	file.close();
	return root;
}

//read dictionary and add to AVL AVL
Node* readFiletoAVL(Node* root) {
	fstream file;
	file.open("DictionaryFull.csv", ios::in);
	string line, word, partOfSpeech, definition;
	while (getline(file, line)) {
		stringstream s(line);
		getline(s, word, ',');
		word.erase(remove(word.begin(),word.end(),'\"'),word.end());

		getline(s, partOfSpeech, ',');
		partOfSpeech.erase(remove(partOfSpeech.begin(),partOfSpeech.end(),'\"'),partOfSpeech.end());

		getline(s, definition);
		definition.erase(remove(definition.begin(),definition.end(),'\"'),definition.end());
		root = insert(root, word, partOfSpeech, definition);
	}
	file.close();
	return root;
}

//compares time between using Trie and AVL
void timeComp(microseconds timeTrie, microseconds timeAVL) {
	if (timeTrie.count() > timeAVL.count()) {
		cout << "The AVL Tree is " << ((timeTrie.count()-timeAVL.count())/timeTrie.count())*100 << "% faster." << endl;
	} else {
		cout << "The Trie is " << ((timeAVL.count()-timeTrie.count())/timeAVL.count())*100 << "% faster." << endl;
	}
}

/*
spell checker submenu
	runs continuously until \back
	similar to definition finder
*/
void spellChecker(Node* root, string mode) {
	string spellCheck = "";
	while (spellCheck != "#Back" || spellCheck != "#back") {
		cout << "\nWeclome to the Spell Checker Submenu!";
		cout << "\n\tType '#Back' to return to the Main Menu";
		cout << "\n\tEnter your input for spellchecking:" << endl;
		cin >> spellCheck;
		if (spellCheck == "#Back" || spellCheck == "#back") {
			return;
		}
		string correction = spellCheck;
		microseconds spellCheckDurationTrie, spellCheckDurationAVL;
		if (mode == "Trie" || mode == "Comparison") {
			auto start = high_resolution_clock::now();
			correction = spellCheckTrie(spellCheck);
			auto stop = high_resolution_clock::now();
			spellCheckDurationTrie = duration_cast<microseconds>(stop - start);
		}
		else if (mode == "AVL" || mode == "Comparison") {
			auto start2 = high_resolution_clock::now();
			correction = spellCheckAVL(root, spellCheck);
			auto stop2 = high_resolution_clock::now();
			spellCheckDurationAVL = duration_cast<microseconds>(stop2 - start2);
		}
		if (correction == spellCheck) {
			cout << "Your input, '" << spellCheck << "', is spelled correctly." << endl;
		}
		else {
			cout << "Correct spelling: " << correction << endl;
		}

		if (mode == "Trie" || mode == "Comparison") {
			cout << "It took " << spellCheckDurationTrie.count() << " microseconds using Trie mode." << endl;
		}
		else if (mode == "AVL" || mode == "Comparison") {
			cout << "It took " << spellCheckDurationAVL.count() << " microseconds using AVL mode." << endl;
		}
		if (mode == "Comparison") {
			timeComp(spellCheckDurationTrie, spellCheckDurationAVL);
		}
	}
	return;
}

//spell checker without the submenu
//has different logic at the correction output stage?
void spellChecker(Node* root, string mode, string input) {
	string correction = input;
	microseconds spellCheckDurationTrie, spellCheckDurationAVL;
	if (mode == "Trie" || mode == "Comparison") {
		auto start = high_resolution_clock::now();
		correction = spellCheckTrie(input);
		auto stop = high_resolution_clock::now();
		spellCheckDurationTrie = duration_cast<microseconds>(stop - start);
	}
	else if (mode == "AVL" || mode == "Comparison") {
		auto start2 = high_resolution_clock::now();
		correction = spellCheckAVL(root, input);
		auto stop2 = high_resolution_clock::now();
		spellCheckDurationAVL = duration_cast<microseconds>(stop2 - start2);
	}
	cout << "Correct spelling: " << correction << endl;

	if (mode == "Trie" || mode == "Comparison") {
		cout << "It took " << spellCheckDurationTrie.count() << " microseconds using Trie mode." << endl;
	}
	else if (mode == "AVL" || mode == "Comparison") {
		cout << "It took " << spellCheckDurationAVL.count() << " microseconds using AVL mode." << endl;
	}
	if (mode == "Comparison") {
		timeComp(spellCheckDurationTrie, spellCheckDurationAVL);
	}
}

void definitionFinder(Node* root, string mode, string input) {
	string def = "DNE";
	cout << root->word << endl;
	microseconds findDefDurationTrie, findDefDurationAVL;
	if (mode == "Trie" || mode == "Comparison") {
		auto start = high_resolution_clock::now();
		def = findDefinitionTrie(input); //**simple, returns definition
		auto stop = high_resolution_clock::now();
		findDefDurationTrie = duration_cast<microseconds>(stop - start);
	}
	else if (mode == "AVL" || mode == "Comparison") {
		//find using AVL *comparison will run both
		auto start2 = high_resolution_clock::now();
		cout << "timing function starts" << endl;
		def = findDefinitionAVL(root, input); //**simple, returns definition
		auto stop2 = high_resolution_clock::now();
		findDefDurationAVL = duration_cast<microseconds>(stop2 - start2);
	}

	if (def == "DNE") {//if word does not exist
		char ans;
		cout << "Your input, '" << input << "', was not found." << endl;

		if (mode == "Trie" || mode == "Comparison") {
			cout << "It took " << findDefDurationTrie.count() << " microseconds using Trie mode." << endl;
		}
		else if (mode == "AVL" || mode == "Comparison") {
			cout << "It took " << findDefDurationAVL.count() << " microseconds using AVL mode." << endl;
		}
		if (mode == "Comparison") {
			timeComp(findDefDurationTrie, findDefDurationAVL);
		}
		cout << "Would you like to enter Spell Checker mode? (Y/N)" << endl;
		cin >> ans;
		if (ans == 'Y' || ans == 'y') {
			spellChecker(root, mode, input);
		}
	}
	else {//if word exists
		cout << def << endl;
		if (mode == "Trie" || mode == "Comparison") {
			cout << "It took " << findDefDurationTrie.count() << " microseconds to find the defintion using Trie mode." << endl;
		}
		else if (mode == "AVL" || mode == "Comparison") {
			cout << "It took " << findDefDurationAVL.count() << " microseconds to find the defintion using AVL mode." << endl;
		}
		if (mode == "Comparison") {
			timeComp(findDefDurationTrie, findDefDurationAVL);
		}
	}
}

int main() {
	Node* rootAVL = NULL;
	Node* rootTrie = NULL;
	//reads file and adds to Data Structures, tracking time it takes
	auto start = high_resolution_clock::now();
	rootTrie = readFiletoTrie(rootTrie);
	auto stop = high_resolution_clock::now();
	auto TrieDuration = duration_cast<microseconds>(stop - start);
	cout << TrieDuration.count()/1000000.0 << " seconds to create the Trie dictionary." << endl;
	auto start2 = high_resolution_clock::now();
	rootAVL = readFiletoAVL(rootAVL);
	auto stop2 = high_resolution_clock::now();
	auto AVLDuration = duration_cast<microseconds>(stop2 - start2);
	cout << AVLDuration.count()/1000000.0 << " seconds to create the AVL dictionary." << endl;
	timeComp(TrieDuration, AVLDuration);
	cout << "root: " << rootAVL->word << " - " << rootAVL->definition << endl;
	string mode = "Trie";
	string input = "";
	while (input != "#Exit") {
		cout << "\nWelcome to the Language Master's Dictionary and Spell Checker!";
		cout << "\n\tCurrent Mode: " << mode;
		cout << "\n\tType “#Help” for more information"; //#1
		cout << "\n\tBegin typing to search for a word or definition:" << endl; //#8
		cin >> input;
		if (input == "#Help" || input == "#help") {
			cout << "\nInstructions for using Dictionary and Spell Checker:";
			cout << "\n\tType '[a word]' to check if it is a word and find the definition"; //#8
			cout << "\n\tType '#SpellChecker' to enter words, sentences, or longer"; //#2
			cout << "\n\tType '1' for Trie dictionary mode"; //#3
			cout << "\n\tType '2' for AVL AVL dictionary mode"; //#4
			cout << "\n\tType '3' for a comparison mode of Trie and AVL AVL Structures"; //#5
			cout << "\n\tType '#Exit' to exit the program anytime" << endl; //#7
		}
		else if (input == "#SpellChecker" || input == "#spellchecker" || input == "#Spellchecker" || input == "#spellChecker") {
			spellChecker(rootAVL, mode);//enter spell checker mode
		}
		else if (input == "1") {//change to Trie mode
			if (mode == "Trie") {
				cout << "It is already in Trie mode!" << endl;
			}
			else {
				mode = "Trie";
				cout << "Changing mode to Trie";
				fflush(stdout);
				sleep_for(milliseconds(500));
				cout << ".";
				fflush(stdout);
				sleep_for(milliseconds(500));
				cout << ".";
				fflush(stdout);
				sleep_for(milliseconds(500));
				cout << ".\n";
			}
		}
		else if (input == "2") {//change to AVL mode
			if (mode == "AVL") {
				cout << "It is already in AVL AVL mode!" << endl;
			}
			else {
				mode = "AVL";
				cout << "Changing mode to AVL";
				fflush(stdout);
				sleep_for(milliseconds(500));
				cout << ".";
				fflush(stdout);
				sleep_for(milliseconds(500));
				cout << ".";
				fflush(stdout);
				sleep_for(milliseconds(500));
				cout << ".\n";
			}
		}
		else if (input == "3") {//change to comparison mode
			if (mode == "Comparison") {
				cout << "It is already in Comparison mode!" << endl;
			}
			else {
				mode = "Comparison";
				cout << "Changing mode to Comparison";
				fflush(stdout);
				sleep_for(milliseconds(500));
				cout << ".";
				fflush(stdout);
				sleep_for(milliseconds(500));
				cout << ".";
				fflush(stdout);
				sleep_for(milliseconds(500));
				cout << ".\n";
			}
		}
		else if (input == "#Exit" || input == "#exit") {//exit program
			return 0;
		}
		else {//finds definition
			definitionFinder(rootAVL, mode, input);
		}
	}
	return 0;
}
