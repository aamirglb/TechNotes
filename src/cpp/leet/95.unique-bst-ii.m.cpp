// Given an integer n, return all the structurally unique BST's (binary search trees), which has
// exactly n nodes of unique values from 1 to n. Return the answer in any order.

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

void insertNode(TreeNode* &node, queue<TreeNode *> &q, int value)
{
    if(value != -1) {
        TreeNode *t = new TreeNode(value);
        node = t;
        q.push(t);
    }
}

// This is a simple binary tree not a binary search tree
void createBinaryTree(TreeNode * &root, initializer_list<int> nodeList)
{
    std::queue<TreeNode *> q;
    bool isLeft{true};

    for(const auto& value : nodeList) {
        if(!root) {
            root = new TreeNode(value);
            q.push(root);
        } else {
            TreeNode *p = q.front();
            if(isLeft) {
                insertNode(p->left, q, value);
            } else {
                insertNode(p->right, q, value);
                q.pop();
            }
            isLeft = !isLeft;
        }
    }
}

// Level order traversal of binary search tree
// Level order traversal is same as Breath First Search (BSF)
void levelOrderTraversal(TreeNode *root)
{
    TreeNode* p = root;
    std::queue<TreeNode *> q;
    std::cout << p->val << " ";
    q.push(p);

    while(!q.empty()) {
        p = q.front();
        q.pop();
        if(p->left) {
            std::cout << p->left->val << " ";
            q.push(p->left);
        }
        if(p->right) {
            std::cout << p->right->val << " ";
            q.push(p->right);
        }
    }
}

void inorder(TreeNode* root) {
    if(root) {
        inorder(root->left);
        std::cout << root->val << " ";
        inorder(root->right);
     }
}

void postorder(TreeNode* root) {
    if(root) {
        postorder(root->left);
        postorder(root->right);
        cout << root->val << " ";
    }
}

vector<TreeNode*> helper(int first, int last) {

    if(first > last) return {nullptr};
    TreeNode *root {};
    vector<TreeNode *> ans;

    for(int i = first; i <= last; ++i) {
        vector<TreeNode *> left = helper(first, i - 1);
        vector<TreeNode *> right = helper(i+1, last);

        for(auto l : left) {
            for(auto r : right) {
                root = new TreeNode(i);
                root->left = l;
                root->right = r;
                ans.push_back(root);
            }
        }
    }
    return ans;
}

vector<TreeNode*> generateTrees(int n) {
    auto res = helper(1, n);
    cout << "number of trees: " << res.size() << endl;
    for(auto p : res) {
        postorder(p);
        std::cout << std::endl;
        // if(p) {
        //     cout << p->val << " ";
        // } else {
        //     cout << " null ";
        // }
    }
    return res;
}

int main() {
    generateTrees(5);
}