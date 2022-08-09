// Given the root of a binary tree and an integer targetSum, return true if the tree has a root-to-leaf path such that adding up all the values along the path equals targetSum.
// A leaf is a node with no children.

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

int sumOfAllNodes(TreeNode *root) {
    if(root) {
        if(!root->left && !root->right) {

        }
        auto x = sumOfAllNodes(root->left);
        auto y = sumOfAllNodes(root->right);
        return x+y+root->val;
    }
    return 0;
}

// void displayBranch(TreeNode *root, vector<int> &v) {
//     if(!root) return;

//     if(!root->left && !root->right) {
//         v.push_back(root->val);
//         for(const auto& e: v) cout << e << ' ';
//         cout << endl;
//         v.pop_back();
//         return;
//         // v.pop_back();
//     }
//     if(root) {
//         // cout << root->val << ' ';
//         v.push_back(root->val);
//         displayBranch(root->left, v);
//         displayBranch(root->right, v);
//     }
// }

bool isLeaf(TreeNode *node) {
    return !node->left && !node->right;
}

void printRootToLeafPath(TreeNode *root, vector<int> &path) {
    if(!root) return;

    path.push_back(root->val);
    if(isLeaf(root)) {
        for(auto const& e: path) cout << e << ' ';
        cout << endl;
    }
    printRootToLeafPath(root->left, path);
    printRootToLeafPath(root->right, path);
    path.pop_back();
}

void pathSum(TreeNode *root, vector<int> &path) {
    if(!root) return;

    path.push_back(root->val);
    if(isLeaf(root)) {
        for(auto const& e: path) cout << e << ' ';
        cout << " = " << accumulate(path.begin(), path.end(), 0);
        cout << endl;
    }

    pathSum(root->left, path);
    pathSum(root->right, path);
    path.pop_back();
}

void postorder(TreeNode *root) {
    if(root) {
        postorder(root->left);
        postorder(root->right);
        cout << root->val << " ";
    }
}

bool inorder(TreeNode* node, int targetSum, int curSum) {
    if(!node) return false;
    curSum += node->val;

    if(!node->left && !node->right) {
        return curSum == targetSum;
    }

    return inorder(node->left, targetSum, curSum) ||
           inorder(node->right, targetSum, curSum);
}


bool hasPathSum(TreeNode* root, int targetSum) {
    return inorder(root, targetSum, 0);
}

int main() {
    TreeNode *root {nullptr};
    createBinaryTree(root, {5, 4, 8, 11, -1, 13, 4, 7, 2, -1, -1, -1, 1});
    vector<int> v;
    printRootToLeafPath(root, v);
    // postorder(root);
    cout << boolalpha << hasPathSum(root, 22) << endl;
    v.clear();
    pathSum(root, v);
}