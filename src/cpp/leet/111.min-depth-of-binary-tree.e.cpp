// Given a binary tree, find its minimum depth.
// The minimum depth is the number of nodes along the shortest path from
// the root node down to the nearest leaf node.

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val{0}, left{nullptr}, right{nullptr} {}
    TreeNode(int x) : val{x}, left{nullptr}, right{nullptr} {}
    TreeNode(int x, TreeNode *left_, TreeNode *right_)
        : val{x}
        , left{left_}
        , right{right_}
    {}
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

void postorder(TreeNode *root) {
    if(root) {
        postorder(root->left);
        postorder(root->right);
        cout << root->val << " ";
    }
}

int minDepth(TreeNode *root) {
    if(!root) return 0;
    if(!root->left && !root->right) return 1;

    int x = numeric_limits<int>::max();
    int y = numeric_limits<int>::max();

    if(root->left)
        x = minDepth(root->left);
    if(root->right)
        y = minDepth(root->right);
    return 1 + min(x, y);
}

int main() {
    TreeNode *root {nullptr};
    createBinaryTree(root, {3, 9, 20, -1, -1, 15, 7});
    cout << minDepth(root) << endl;

    TreeNode *s {nullptr};
    createBinaryTree(s, {1, 2, 3, 8, -1, 4, 5, 6, -1});
    cout << minDepth(s) << endl;
}