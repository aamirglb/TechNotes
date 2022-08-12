// Given the root of a binary tree, determine if it is a valid binary search tree (BST).

#include <iostream>
#include <vector>
#include <queue>

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

bool validate(TreeNode *root, long int max, long int min) {
    if(!root) return true;

    if(root->val >= max || root->val <= min) {
        return false;
    } else {
        return validate(root->left, root->val, min) && validate(root->right, max, root->val);
    }
}
bool isValidBST(TreeNode* root) {
    return vaidate(root, numeric_limits<long int>::max(), numeric_limits<long int>::min());
}

int main() {
    TreeNode *r1 {nullptr};
    createBinaryTree(r1, {2, 1, 3});
    // auto res = binaryTreePaths(r1);

    cout << endl << " -- " << endl;
}