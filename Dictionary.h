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
#include <map>
#include <iomanip>
#include <chrono>
#include <thread>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
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

class AVLTree {
    public:
        Node* root;
        //constructors
        AVLTree(){
            root = NULL;
        }
        AVLTree(Node* z) {
            root = z;
        }

    //sets root of tree
    void setRoot(Node* n) {
      root = n;
    }
    //returns tree root
    Node* getRoot(){
        return root;
    }
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

string findDefinitionAVL(Node* node, string word) {
	//searches tree for word
	cout << "enters function" << endl;
    if (node == NULL) {
        //if node is nothing (beyond leaves), word NOT found
		cout << "if this happens before compare, root is NULL" << endl;
        return "DNE";
    } else if (node->word == word){
        //if node is word, return word
        return node->word;
    } else{
		if (word.compare(node->word) < 0){
            //if word less than node word, search left
            //recursively call find to check left subtree
			cout << "compare left" << endl;
            return findDefinitionAVL(node->left, word);
        } else if (word.compare(node->word) > 0){
            //if word greater than node word, search right
            //recursively call find to check right subtree
			cout << "compare right" << endl;
            return findDefinitionAVL(node->right, word);
        }
	}
	return "DNE";
}
/*
Node* searchID(Node* root, string ID) {
    //searches tree for ID
    if (root == NULL) {
        //if node is nothing (beyond leaves), ID NOT found
        return NULL;
    } else if (root->ID == ID){
        //if node has ID, return node
        return root;
    } else{
        if (ID.compare(root->ID) < 0){
            //if ID less than node ID, search left
            //recursively call find to check left subtree
            return searchID(root->left, ID);
        } else if (ID.compare(root->ID) > 0){
            //if ID greater than node ID, search right
            //recursively call find to check right subtree
            return searchID(root->right, ID);
        }
    }
    return root;
}
*/

string spellCheckAVL(Node* node, string word) {
	string def = "DNE";
	//def = definition
	return def;
}

//class Trie



//methods for Trie









string findDefinitionTrie(string word) {
	string def = "DNE";
	//def = definition
	return def;
}

string spellCheckTrie(string word) {
	string def = "DNE";
	//def = definition
	return def;
}

#endif /* Dictionary_H */
