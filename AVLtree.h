#pragma once
#ifndef AVLTREE_H_
#define AVLTREE_H_
#include<iostream>
#include<string>
#include "FunctionUtil.h"
using namespace std;
// Avl Node
template <typename T>
struct AVLNode
{
	T key;
	int lineNumber;
	string fileName;
	AVLNode<T>* left, * right;
	AVLNode()
	{
		lineNumber = 0;
		left = right = NULL;
	}
};
// Implementation of the AVL Tree
template <typename T>
struct AVL {
	AVLNode<T>* root;
	int lineCount;
public:
	AVL() {
		root = NULL;
		lineCount = 0;
	}

	AVLNode<T>* getRoot() const {
		return root;
	}

	int Height(AVLNode<T>* r) {
		if (r == NULL)
			return 0;

		else {
			int leftHeight;
			int rightHeight;

			if (r->left == NULL) {
				leftHeight = Height(r->left);
			}
			else {
				return 0;
			}

			if (r->right != NULL) {
				rightHeight = Height(r->right);
			}
			else {
				return 0;
			}

			leftHeight += 1;
			rightHeight += 1;

			if (leftHeight >= rightHeight) {
				return leftHeight;
			}

			else {
				return rightHeight;
			}
		}
	}

	AVLNode<T>* fileHandling(AVLNode<T>* AVLNodeptr, string fn, string data)
	{
		// Filehandling
		ofstream openFile(fn, ios_base::app);
		openFile << data << endl;
		return AVLNodeptr;
	}

	string getFileName(T id, AVLNode<T>* ptr)
	{
		string n = "./textFiles/";
		n += id + "_";
		n += to_string(ptr->lineNumber / 100);
		n += ".txt";
		return n;
	}

	void delete_line(char* file_name, int n)
	{
		string data; int i = 0;
		ifstream file1(file_name);
		ofstream file2("temp.txt");
		getline(file1, data);
		while (!file1.eof())
		{
			if (i == n)
			{
				data = "This value has been Deleted\n";
				file2 << data;
			}
			else
			{
				file2 << data;
				file2 << endl;
			}
			getline(file1, data);
			i++;
		}
		// closing output file 
		file1.close();
		// closing input file 
		file2.close();
		// remove the original file 
		remove(file_name);
		// rename the file 
		rename("temp.txt", file_name);
	}

	int heightDifference(AVLNode<T>* r) {
		int leftHt = Height(r->left);
		int rightHt = Height(r->right);

		return (leftHt - rightHt);
	}

	AVLNode<T>* rightR_Rotate(AVLNode<T>* r) {
		AVLNode<T>* temp;
		temp = r->right;
		r->right = temp->left;
		temp->left = r;
		return temp;
	}

	AVLNode<T>* leftL_Rotate(AVLNode<T>* r) {
		AVLNode<T>* temp;
		temp = r->left;
		r->left = temp->right;
		temp->right = r;
		return temp;
	}

	AVLNode<T>* leftR_Rotate(AVLNode<T>* r) {
		AVLNode<T>* temp;
		temp = r->left;
		r->left = rightR_Rotate(temp);
		return leftL_Rotate(r);
	}

	AVLNode<T>* rightL_Rotate(AVLNode<T>* r) {
		AVLNode<T>* temp;
		temp = r->right;
		r->right = leftL_Rotate(temp);
		return rightR_Rotate(r);

	}

	AVLNode<T>* balanceTree(AVLNode<T>* r) {
		int balfact = heightDifference(r);
		if (balfact > 1) {

			if (heightDifference(r->left) > 0) {

				r = leftL_Rotate(r);
			}
			else
				r = leftR_Rotate(r);
		}
		else if (balfact < -1) {

			if (heightDifference(r->right) > 0) {

				r = rightL_Rotate(r);
			}
			else
				r = rightR_Rotate(r);
		}
		return r;
	}

	AVLNode<T>* insert(T k, string fn, string data, AVLNode<T>* AVLNodeptr) {

		if (AVLNodeptr == NULL) {

			AVLNodeptr = new AVLNode<T>();

			// TODO: Change LineCount / 100 if u want to change check if new files created
			fn = fn.substr(0, fn.size() - 4);
			fn += "_" + to_string(lineCount / 100);
			fn += ".txt";

			AVLNodeptr->key = k;
			AVLNodeptr->fileName = fn;
			AVLNodeptr->lineNumber = lineCount;
			fileHandling(AVLNodeptr, AVLNodeptr->fileName, data);

			lineCount++;

			return AVLNodeptr;
		}
		else if (k < AVLNodeptr->key) {

			AVLNodeptr->left = insert(k, fn, data, AVLNodeptr->left);
			AVLNodeptr = balanceTree(AVLNodeptr);
		}
		else if (k > AVLNodeptr->key) {

			AVLNodeptr->right = insert(k, fn, data, AVLNodeptr->right);
			AVLNodeptr = balanceTree(AVLNodeptr);
		}
		return AVLNodeptr;
	}

	AVLNode<T>* minValueAVLNode(AVLNode<T>* r) {
		AVLNode<T>* current = r;

		while (current->left != NULL)
			current = current->left;

		return current;
	}

	AVLNode<T>* deleteAVLNode(T n, AVLNode<T>* r)
	{
		if (r == NULL)
			return r;

		if (n < r->key) {
			r->left = deleteAVLNode(n, r->left);
		}

		else if (n > r->key) {
			r->right = deleteAVLNode(n, r->right);
		}

		else
		{
			char* theFile = new char[r->fileName.length()];
			for (int i = 0; i < r->fileName.length(); i++) {
				theFile[i] = r->fileName[i];
			}
			delete_line(theFile, (r->lineNumber));
			delete[] theFile;

			if (r->left == NULL) {
				AVLNode<T>* temp = r->right;
				delete r;
				return temp;
			}

			else if (r->right == NULL) {
				AVLNode<T>* temp = r->left;
				delete r;
				return temp;
			}

			AVLNode<T>* temp = minValueAVLNode(r->right);
			r->key = temp->key;
			r->lineNumber = temp->lineNumber;
			r->fileName = temp->fileName;
			r->right = deleteAVLNode(temp->key, r->right);

		}
		return r;
	}

	AVLNode<T>* Search(AVLNode<T>* node, T k)
	{
		// The given key is
		// not found in BST
		if (node == NULL)
			return node;
		// The given key is found
		else if (node->key == k) {
			//cout << "Key: " << node->key << ", Line Number: " << node->lineNumber << ", File Name: " << node->fileName << endl;
			//line = node->lineNumber;

			ifstream openFile(node->fileName);
			string fullLine;

			//cout << node->fileName << endl;

			getline(openFile, fullLine);

			for (int i = 1; i < node->lineNumber - 1; i++) {
				getline(openFile, fullLine);
			}


			cout << fullLine << endl;

			return node;
		}

		// The given is greater than
		// current node's key
		else if (node->key < k)
			return Search(node->right, k);
		// The given is smaller than
		// current node's key
		else
			return Search(node->left, k);
	}


	void removeAVLNodeAndBalance(T n, AVLNode<T>* r) {
		root = deleteAVLNode(n, r);

		if (Height(r) > 1) {
			root = balanceTree(r);
		};

	}

	void Display(AVLNode<T>* r)
	{
		if (r == NULL)
			return;

		else {
			Display(r->left);
			cout << "Key: " << To_Integer(r->key) << ", Line Number: " << r->lineNumber << ", File Name: " << r->fileName << endl;
			Display(r->right);
		}
	}
};
#endif