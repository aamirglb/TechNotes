// Given the root of a binary tree, invert the tree, and return its root.
#include <iostream>
#include <vector>
#include <queue>
#include <vector>
#include <numeric>

using namespace std;

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// This is a simple binary tree not a binary search tree
void createBinaryTree(TreeNode * &root, initializer_list<int> nodeList) {
    queue<TreeNode *> q;
    int nodeCnt {};

    // insert node one by one in the tree
    for(const auto& val : nodeList) {
        // Not a first node
        if(root) {
            ++nodeCnt;
            TreeNode *r = q.front();

            if(val != -1) {
                TreeNode *t = new TreeNode(val);
                if(nodeCnt % 2 != 0) {
                    r->left = t;
                } else {
                    r->right = t;
                }
                q.push(t);
            }
            if(nodeCnt % 2 == 0) q.pop();
        } else { // first node
            root = new TreeNode(val);
            q.push(root);
        }
    }
}

void inorder(TreeNode *root) {
    if(root) {
        cout << root->val << ' ';
        inorder(root->left);
        inorder(root->right);
    }
}

TreeNode* invertTree(TreeNode* root) {
    if(!root) return nullptr;

    swap(root->left, root->right);
    invertTree(root->left);
    invertTree(root->right);
    return root;
}

int main() {
    TreeNode *root {nullptr};
    createBinaryTree(root, {4, 2, 7, 1, 3, 6, 9});
    inorder(root); cout << endl;
    root = invertTree(root);
    inorder(root); cout << endl;
}