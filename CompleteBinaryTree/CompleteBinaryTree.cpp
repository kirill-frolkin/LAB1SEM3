#include "CompleteBinaryTree.h"
#include <queue>
using namespace std;
CompleteBinaryTree *createCBT()
{
    CompleteBinaryTree *tree = new CompleteBinaryTree;
    tree->root = nullptr;
    tree->size = 0;
    return tree;
}
void deleteNode(TreeNode *node)
{
    if (!node)
        return;
    deleteNode(node->left);
    deleteNode(node->right);
    delete node;
}
void deleteCBT(CompleteBinaryTree *tree)
{
    if (tree)
    {
        deleteNode(tree->root);
        delete tree;
    }
}
void insertCBT(CompleteBinaryTree *tree, const string &value)
{
    TreeNode *newNode = new TreeNode{value, nullptr, nullptr};
    if (!tree->root)
    {
        tree->root = newNode;
        tree->size++;
        return;
    }
    queue<TreeNode *> q;
    q.push(tree->root);
    while (!q.empty())
    {
        TreeNode *curr = q.front();
        q.pop();
        if (!curr->left)
        {
            curr->left = newNode;
            break;
        }
        else
            q.push(curr->left);
        if (!curr->right)
        {
            curr->right = newNode;
            break;
        }
        else
            q.push(curr->right);
    }
    tree->size++;
}
bool findCBT(CompleteBinaryTree *tree, const string &value)
{
    if (!tree->root)
        return false;
    queue<TreeNode *> q;
    q.push(tree->root);
    while (!q.empty())
    {
        TreeNode *curr = q.front();
        q.pop();
        if (curr->data == value)
            return true;
        if (curr->left)
            q.push(curr->left);
        if (curr->right)
            q.push(curr->right);
    }
    return false;
}
bool isCompleteCBT(CompleteBinaryTree *tree)
{
    if (!tree->root)
        return true;
    queue<TreeNode *> q;
    q.push(tree->root);
    bool null_found = false;
    while (!q.empty())
    {
        TreeNode *curr = q.front();
        q.pop();
        if (!curr)
            null_found = true;
        else
        {
            if (null_found)
                return false;
            q.push(curr->left);
            q.push(curr->right);
        }
    }
    return true;
}
