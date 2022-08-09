// Given the root of a binary tree, return its maximum depth.
// A binary tree's maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

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

// void insertNode(TreeNode* &node, queue<TreeNode *> &q, int value)
// {
//     if(value != -1) {
//         TreeNode *t = new TreeNode(value);
//         node = t;
//         q.push(t);
//     }
// }

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

int maxDepth(TreeNode* root) {

    if(root) {
        auto maxLeft = maxDepth(root->left);
        auto maxRigth = maxDepth(root->right);
        return max(maxLeft, maxRigth) + 1;
    }
    return 0;
}

int main() {
    TreeNode *root {nullptr};

    createBinaryTree(root, {3, 9, 20, -1, -1, 15, 7});
    cout << "Postorder traversal:\n";
    inorder(root);
    cout << "\nmax depth: " << maxDepth(root);

    TreeNode *r1 {};
    createBinaryTree(r1, {1});
    cout << "\nmax depth: " << maxDepth(r1);

    TreeNode *r2 {};
    createBinaryTree(r2, {1, -1, 2});
    cout << "\nmax depth: " << maxDepth(r2);

}
