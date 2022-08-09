//
//

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

bool checkSymmetric(TreeNode *left, TreeNode *right) {
    if(!left || !right) return left == right;

    if(left->val != right->val) return false;
    return checkSymmetric(left->left, right->right) &&
           checkSymmetric(left->right, right->left);
}

// TODO!! NOT working as expected
bool isSymmetric(TreeNode* root) {
    if(!root) return true;
    return checkSymmetric(root->left, root->right);
}

int main()
{
    TreeNode *root {nullptr};
    TreeNode *r2 {nullptr};

    createBinaryTree(root, {3, 9, 20, -1, -1, 15, 7});
    inorder(root);


    // createBinarySearchTree(root, {9, 15, 5, 20, 16, 8, 12, 3, 6});
    // createBinarySearchTree(root, {10, 5, 20, 8, 30});
    createBinaryTree(root, {1, 2, 2, 3, 4, 4, 3});
    createBinaryTree(r2, {1, 2, 2, -1, 3, -1, 3});

    cout << boolalpha << isSymmetric(root) << endl;
    cout << boolalpha << isSymmetric(r2) << endl;
    // std::cout << "Level order traversal: \n";
    // levelOrderTraversal(root);

    // std::cout << "\nPostorder traversal: \n";
    // postorder(root);
}

