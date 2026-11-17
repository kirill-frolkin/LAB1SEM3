#pragma once
#include <string>
using namespace std;
struct TreeNode { string data; TreeNode* left; TreeNode* right; };
struct CompleteBinaryTree { TreeNode* root; int size; };
CompleteBinaryTree* createCBT();
void deleteCBT(CompleteBinaryTree* tree);
void insertCBT(CompleteBinaryTree* tree, const string& value);
bool findCBT(CompleteBinaryTree* tree, const string& value);
bool isCompleteCBT(CompleteBinaryTree* tree);
