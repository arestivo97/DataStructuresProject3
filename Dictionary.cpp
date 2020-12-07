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
void readFiletoTree(Node* root) {
    fstream file;
    file.open("DictionaryFull.csv", ios::in);
    string line, word, partOfSpeech, definition;
    while (getline(file, line)) {
        stringstream s(line);
        getline(s, word, ',');
        getline(s, partOfSpeech, ',');
        getline(s, definition, ',');
        root = insert(root, word, partOfSpeech, definition);
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

/*
spell checker submenu
    runs continuously until \back
    similar to definition finder
*/
void spellChecker(string mode, Node* root) {
    string spellCheck = "";
    while(spellCheck != "\\Back") {
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
        } else if (mode == "Tree" || mode == "Comparison") {
            auto start = high_resolution_clock::now();
            correction = spellCheckTree(root, spellCheck)
            auto stop = high_resolution_clock::now();
            spellCheckDurationTree = duration_cast<microseconds>(stop - start); 
        }
        if (correction == spellCheck) {
            cout << "Your input, '" << spellCheck << "', is spelled correctly." << endl;
        } else {
            cout << "Correct spelling: " << correction << endl;
        }

        if (mode == "Heap" || mode == "Comparison") {
            cout << "It took " << spellCheckDurationHeap.count() << " microseconds using Heap mode." << endl;
        } else if (mode == "Tree" || mode == "Comparison") {
            cout << "It took " << spellCheckDurationTree.count() << " microseconds using Tree mode." << endl;
        }
        if (mode == "Comparison") {
            timeComp(spellCheckDurationHeap,spellCheckDurationTree);
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

string spellCheckTree(Node* current, string word) {
    vector<string> wordList;
	vector<string>* ptrWordList = &wordList;
	printInorder(current, ptrWordList);
	string suggestedWord;
	int switchKey = 0;
	for (unsigned int i = 0; i < wordList.size(); i++) {
		if (wordList[i] > findWord && switchKey == 0) {
			suggestedWord = wordList[i];
			switchKey = 1;
		}
	}
	cout << endl;
	return suggestedWord;
}

//This printInorder creates a vector of all the nodes in the tree in a inorder manner
void printInorder(Node* head, vector<string>* ptrWL) {
	if (head == NULL)
		cout << "";
	else {
		printInorder(head->left, ptrWL);
		ptrWL->push_back(head->word);
		printInorder(head->right, ptrWL);
	}
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
    } else if (mode == "Tree" || mode == "Comparison") {
        auto start = high_resolution_clock::now();
        //correction = spellCheckTree(input)
        auto stop = high_resolution_clock::now();
        spellCheckDurationTree = duration_cast<microseconds>(stop - start); 
    }
    cout << "Correct spelling: " << correction << endl;

    if (mode == "Heap" || mode == "Comparison") {
        cout << "It took " << spellCheckDurationHeap.count() << " microseconds using Heap mode." << endl;
    } else if (mode == "Tree" || mode == "Comparison") {
        cout << "It took " << spellCheckDurationTree.count() << " microseconds using Tree mode." << endl;
    }
    if (mode == "Comparison") {
        timeComp(spellCheckDurationHeap,spellCheckDurationTree);
    }
}

//these should be class functions
string findDefinitionHeap(string word) {
    string def = "DNE";
    //def = heap.definition
    //return def
}
string findDefinitionTree(Node* current, string search_word) {
    if (current == NULL) {
		return "DNE";
	}
	else {
		if (current->word == search_word)
			return current->definition;
		else if (current->word > search_word)
			return findDefinitionTree(current->left, search_word);
		else if (current->word < search_word)
			return findDefinitionTree(current->right, search_word);
	}
	return "DNE";
}

string definitionFinder(string mode, string input, Node* root) {
    string def = "DNE";
    microseconds findDefDurationHeap, findDefDurationTree;
    if (mode == "Heap" || mode == "Comparison") {
        auto start = high_resolution_clock::now();
        def = findDefinitionHeap(input); //**simple, returns definition
        auto stop = high_resolution_clock::now();
        findDefDurationHeap = duration_cast<microseconds>(stop - start); 
    } else if (mode == "Tree" || mode == "Comparison") {
        //find using tree *comparison will run both
        auto start = high_resolution_clock::now();
        def = findDefinitionTree(root, input); //**simple, returns definition
        auto stop = high_resolution_clock::now();
        findDefDurationTree = duration_cast<microseconds>(stop - start); 
    }

    if (def == "DNE") {//if word does not exit
        char ans;
        cout << "Your input, '" << input << "', was not found." << endl;

        if (mode == "Heap" || mode == "Comparison") {
            cout << "It took " << findDefDurationHeap.count() << " microseconds using Heap mode." << endl;
        } else if (mode == "Tree" || mode == "Comparison") {
            cout << "It took " << findDefDurationTree.count() << " microseconds using Tree mode." << endl;
        }
        if (mode == "Comparison") {
            timeComp(findDefDurationHeap,findDefDurationTree);
        }
        cout << "Would you like to enter Spell Checker mode? (Y/N)" << endl;
        cin >> ans;
        if (ans == 'Y') {
            spellChecker(mode, input);
        }
    } else {//if word exists
        cout << def << endl;
        if (mode == "Heap" || mode == "Comparison") {
            cout << "It took " << findDefDurationHeap.count() << " microseconds to find the defintion using Heap mode." << endl;
        } else if (mode == "Tree" || mode == "Comparison") {
            cout << "It took " << findDefDurationTree.count() << " microseconds to find the defintion using Tree mode." << endl;
        }
        if (mode == "Comparison") {
            timeComp(findDefDurationHeap,findDefDurationTree);
        }
    }
}

//AVL Tree Methods
//This the Node class that will serve as the basis
//for what a Node is and its elements.
class Node {
public:
	string word;
	string partOfSpeech;
	string definition;
	int height;
	Node* left;
	Node* right;
};

//Basic functionality: Determines which of the two is greater
//AVL Tree functionality: Determines if the the left or right
//subtree of the root Node is bigger. This is used to determine
//the overall height of the tree.
int max(int first, int second) {
	if (first > second)
		return first;
	else
		return second;
}

//Returns the height value of the inputed Node
int getHeight(Node* temp) {
	if (temp == NULL)
		return 0;
	return temp->height;
}

//The constructor for what an AVL Node will look like
Node* createAvlNode(string input_word, string input_partOfSpeech,string input_definition) {
	Node* node = new Node();
	node->left = NULL;
	node->right = NULL;
	node->word = input_word;
	node->partOfSpeech = input_partOfSpeech;
	node->definition = input_definition;
	node->height = 1;
	return node;
}

//The process by which a Node will be rotated to the left
Node* rotateLeft(Node *node){
	//Set and do left rotation
	Node* grandchild = node->right->left;
	Node* newParent = node->right;
	newParent->left = node;
	node->right = grandchild;

	//Update the height variable
	node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
	newParent->height = max(getHeight(newParent->left), getHeight(newParent->right)) + 1;

	//Return the new parent
	return newParent;
}

//The process by which a Node will be rotated to the right
Node* rotateRight(Node *node){
	//Set and do right rotation
	Node* grandchild = node->left->right;
	Node* newParent = node->left;
	newParent->right = node;
	node->left = grandchild;

	//Update the height variable
	node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
	newParent->height = max(getHeight(newParent->left), getHeight(newParent->right)) + 1;

	//Return the new parent
	return newParent;
}

int balanceFactor(Node* temp) {
	if (temp == NULL)
		return 0;
	return getHeight(temp->left) - getHeight(temp->right);
}

//The process of how a Node is inserted into an AVL Tree
//Could include a condition to combine definitions if the word is repeated?
Node* insert(Node* node, string input_word, string input_partOfSpeech,string input_definition) {
	//Preform recursive insertion
	if (node == NULL) {
		Node* temp_node = createAvlNode(input_word, input_partOfSpeech, input_definition);
		cout << "successful" << endl;
		return temp_node;
	}
	if (input_word < node->word)
		node->left = insert(node->left, input_word, input_partOfSpeech, input_definition);
	else if (input_word > node->word)
		node->right = insert(node->right, input_word, input_partOfSpeech, input_definition);
	else {
		cout << "unsuccessful" << endl;
		return node;
	}

	//Edit the height of the node in order to determine balance factor
	node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

	//Determine the balance factor to see if rotations are necessary
	int balance_factor = balanceFactor(node);

	//Rotation cases
	//Left Left
	if (balance_factor > 1 && input_word < node->left->word)
		return rotateRight(node);
	//Right Right
	if (balance_factor < -1 && input_word > node->right->word)
		return rotateLeft(node);
	//Left Right
	if (balance_factor > 1 && input_word > node->left->word) {
		node->left = rotateLeft(node->left);
		return rotateRight(node);
	}
	//Right Left
	if (balance_factor < -1 && input_word < node->right->word) {
		node->right = rotateRight(node->right);
		return rotateLeft(node);
	}

	//Insertion successful, return node
	return node;
}

int main() {
    //reads file and adds to Data Structures, tracking time it takes
    auto start = high_resolution_clock::now();
    readFiletoHeap();
    auto stop = high_resolution_clock::now();
    auto heapDuration = duration_cast<microseconds>(stop - start);
    cout << heapDuration.count() << " microseconds to create the heap dictionary." << endl;
    Node* root = NULL;
    auto start = high_resolution_clock::now();/*
    readFiletoTree(root);
    auto stop = high_resolution_clock::now();
    auto treeDuration = duration_cast<microseconds>(stop - start);
    cout << treeDuration.count() << " microseconds to create the tree dictionary." << endl;
    timeComp(heapDuration,treeDuration);

    string mode = "Heap";
    string input = "";
    while(input != "\\Exit") {
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
        } else if (input == "\\Spell Checker") {
            spellChecker(mode, root);//enter spell checker mode
        } else if (input == "1") {//change to heap mode
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
        } else if (input == "2") {//change to tree mode
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
        } else if (input == "3") {//change to comparison mode
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
        } else if (input == "\\Exit") {//exit program
            return 0;
        } else {//finds definition
            definitionFinder(mode, input, root);
        }
    }
    return 0;
}
