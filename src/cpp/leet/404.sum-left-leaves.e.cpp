// Given the root of a binary tree, return the sum of all left leaves.
// A leaf is a node with no children. A left leaf is a leaf that is the left child of another node.

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

void postorder(TreeNode *root) {
    if(root) {
        postorder(root->left);
        postorder(root->right);
        cout << root->val << " ";
    }
}

bool isLeaf(TreeNode *node) {
    if(!node->left && !node->right) return true;
    else return false;
}

int sumOfLeftLeaves(TreeNode* root) {
    if(!root) return 0;
    if(root->left && isLeaf(root->left)) {
        return root->left->val + sumOfLeftLeaves(root->right);
    } else {
        return sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right);
    }
}

int main() {
    TreeNode *root {nullptr};

    createBinaryTree(root, {3, 9, 20, -1, -1, 15, 7});
    cout << sumOfLeftLeaves(root) << endl;

    TreeNode *r2 {nullptr};
    createBinaryTree(r2, {1});
    cout << sumOfLeftLeaves(r2) << endl;

    TreeNode *r3 {nullptr};
    createBinaryTree(r3, {1, 2, 3, 4, 5});
    cout << sumOfLeftLeaves(r3) << endl;

    TreeNode *r4 {nullptr};
    createBinaryTree(r4, {-9, -3, 2, -1, 4, 4, 0, -6, -1, -5});
    cout << sumOfLeftLeaves(r4) << endl;
}