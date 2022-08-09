// Given the root of a binary tree, return all root-to-leaf paths in any order.
// A leaf is a node with no children.

#include <iostream>
#include <vector>
#include <queue>
#include <string>

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

bool isLeafNode(TreeNode *node) {
    if(!node->left && !node->right) return true;
    else return false;
}

void recursiveRootToLeaf(TreeNode *root, vector<int> &path, vector<string> &res) {
    if(!root) return;

    path.push_back(root->val);

    if(isLeafNode(root)) {
        string s;
        size_t i = 0;
        for(; i < path.size() - 1; ++i) {
            s += to_string(path[i]) + "->";
        }
        s += to_string(path[i]);
        res.push_back(s);
    }

    recursiveRootToLeaf(root->left, path, res);
    recursiveRootToLeaf(root->right, path, res);
    path.pop_back();
}

vector<string> binaryTreePaths(TreeNode* root) {
    vector<string> res;
    vector<int> path;
    recursiveRootToLeaf(root, path, res);
    return res;
}

int main() {
    TreeNode *r1 {nullptr};
    createBinaryTree(r1, {1, 2, 3, -1, 5});
    auto res = binaryTreePaths(r1);
    for(const auto& s : res) cout << s << ", ";
    cout << endl << " -- " << endl;

    res.clear();
    TreeNode *r2 {nullptr};
    createBinaryTree(r2, {5, 4, 8, 11, -1, 13, 4, 7, 2, -1, -1, -1, 1});
    res = binaryTreePaths(r2);
    for(const auto& s : res) cout << s << ", ";
    cout << endl;
 }
