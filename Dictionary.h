//
// Created by Adam Slavny on 12/7/20.
/*
Dictionary.h
Authors: Andrew Restivo, Darren Peters, Adam Slavny
12/4/20
COP3530 - Data Structures
Project 3: Dictionary and Spell Checker
Language: C++
Data Structures used: AVL Tree and Trie
functions:
    find definition
    spell check
    spelling suggestions
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <math.h>
#include <unordered_map>
using namespace std;
#ifndef Dictionary_H
#define Dictionary_H

//class AVL
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

//methods for AVL
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
Node* createAvlNode(string input_word, string input_partOfSpeech, string input_definition) {
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
Node* rotateLeft(Node *node) {
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
Node* rotateRight(Node *node) {
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
Node* insert(Node* node, string input_word, string input_partOfSpeech, string input_definition) {
    //Preform recursive insertion
    if (node == NULL) {
        Node* temp_node = createAvlNode(input_word, input_partOfSpeech, input_definition);
        //cout << "successful" << endl;
        return temp_node;
    }
    if (input_word < node->word)
        node->left = insert(node->left, input_word, input_partOfSpeech, input_definition);
    else if (input_word > node->word)
        node->right = insert(node->right, input_word, input_partOfSpeech, input_definition);
    else {
        //cout << "unsuccessful" << endl;
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

string findDefinitionAVL(Node* current, string search_word) {
    if (current == NULL) {
        return "DNE";
    }
    else {
        if (current->word == search_word) {
            return (current->partOfSpeech + " " + current->definition);
        } else if (current->word > search_word) {
            return findDefinitionAVL(current->left, search_word);
        } else if (current->word < search_word) {
            return findDefinitionAVL(current->right, search_word);
        }
    }
    return "DNE";
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

//uses Levenshtein Distance to calculate the closest word
string spellCheckAVL(Node* current, string word) {
    string closestWord = "DNE"; //word to return
    int distclosestWord = 10000; //initialize LD value to very large
    int dist[50][50]; //matrix for Levenshtein Distance

    //set word to correct as char array
    char wordToCorrect[word.length() + 1];
    strcpy(wordToCorrect, word.c_str());
    int l1 = strlen(wordToCorrect);

    //vector of words
    vector<string> wordList;
    vector<string>* ptrWordList = &wordList;
    printInorder(current, ptrWordList);
    //loop through entire tree
    for (unsigned int i = 0; i < wordList.size(); i++) {
        int t,track;
        //set word to compare to word to correct as char array
        char wordToCompare[wordList[i].length() + 1];
        strcpy(wordToCompare, wordList[i].c_str());
        int l2 = strlen(wordToCompare);
        //set first row to 0 - l1
        for(int j = 0; j <= l1; j++) {
            dist[0][j] = j;
        }
        //set first column to 0 - l2
        for(int k = 0; k <= l2; k++) {
            dist[k][0] = k;
        }
        //loops through every letter pair of each word to determine if its equal
        for (int m = 1; m <= l1; m++) {
            for(int n = 1; n <= l2; n++) {
                //if the letter in word to compare is in word to correct
                if(wordToCorrect[n - 1] == wordToCompare[m - 1]) {
                    track = 0;
                } else {
                    track = 1;
                }
                if ((dist[n - 1][m] + 1) < (dist[n][m - 1] + 1)) {
                    t = (dist[n - 1][m] + 1);
                } else {
                    t = (dist[n][m - 1] + 1);
                }
                //set distance of letter position
                if (t < (dist[n - 1][m - 1] + track)) {
                    dist[n][m] = t;
                } else {
                    dist[n][m] = (dist[n - 1][m - 1] + track);
                }
            }
        }
        //if current word is closer than the previous closest, update stored word and value
        if (dist[l2][l1] < distclosestWord) {
            distclosestWord = dist[l2][l1];
            closestWord = wordList[i];
        }
    }
    return closestWord;
}


//Start of Trie
//class Trie

// Structure for Trie
struct Trie {
    bool isWord;
    unordered_map<char, Trie*> map;
    string meaning;
};

// create a new Trie node
Trie* getNewTrieNode()
{
    Trie* node = new Trie;
    node->isWord = false;
    return node;
}

// Function to insert a word with its meaning
void insertTrie(Trie*& root, const string& str, const std::string& type,const string& def)
{

    // If root is null
    if (root == NULL)
        root = getNewTrieNode();

    Trie* temp = root;
    for (int i = 0; i < str.length(); i++) {
        char x = str[i];

        // Make a new node if there is no path
        if (temp->map.find(x) == temp->map.end())
            temp->map[x] = getNewTrieNode();

        temp = temp->map[x];
    }

    // Mark end of word and store the meaning
    temp->isWord = true;
    temp->meaning = type+ " " + def;
}

// Function to search a word in the Trie
// and return its meaning if the word exists
string findDefinitionTrie(Trie* root, const string& word)
{
    // If root is null i.e. the dictionary is empty
    if (root == nullptr) {
        cout <<  "root is empty";
        return "DNE";
    }

    Trie* temp = root;

    // Search a word in the Trie
    for (int i = 0; i < word.length(); i++) {
        temp = temp->map[word[i]];
        if (temp == NULL)
            return "DNE";
    }

    // If it is the end of a valid word stored
    // before then return its meaning
    if (temp->isWord)
        return temp->meaning;
    return "DNE";
}


string spellCheckTrie(string word) {
    string def = "DNE";
    //def = definition
    return def;
}

#endif /* Dictionary_H */
