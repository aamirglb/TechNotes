// Given a binary tree, determine if it is height-balanced.
// For this problem, a height-balanced binary tree is defined as:
// a binary tree in which the left and right subtrees of every node differ in height by no more than 1.

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

void breathFirstSearch(TreeNode *root) {
    TreeNode *p = root;
    queue<TreeNode *> q;
    cout << p->val << " ";
    q.push(p);

    while(!q.empty()) {
        p = q.front();
        q.pop();
        if(p->left) {
            cout << p->left->val << " ";
            q.push(p->left);
        } else {
            cout << "null" << " ";
        }

        if(p->right) {
            cout << p->right->val << " ";
            q.push(p->right);
        } else {
            cout << "null" << " ";
        }
    }
}

int height(TreeNode* root) {
    if(root) {
        auto maxLeft = height(root->left);
        auto maxRigth = height(root->right);
        return max(maxLeft, maxRigth) + 1;
    }
    return 0;
}

bool isBalanced(TreeNode* root) {
    if(!root) return true;

    int x = height(root->left);
    int y = height(root->right);
    cout << "left = " << x << " right = " << y << endl;
    if(abs(x - y) > 1) return false;
    return isBalanced(root->left) && isBalanced(root->right);

}

int main() {
    TreeNode *root {nullptr};
    createBinaryTree(root, {3, 9, 20, -1, -1, 15, 7});
    breathFirstSearch(root); cout << endl;
    cout << endl << boolalpha << isBalanced(root) << endl;

    TreeNode *r2{nullptr};
    createBinaryTree(r2, {1, 2, 2, 3, -1, -1, 3, 4, -1, -1, 4});
    breathFirstSearch(r2); cout << endl;
    cout << endl << boolalpha << isBalanced(r2) << endl;
}