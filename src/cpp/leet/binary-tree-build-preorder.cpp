#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <fmt/format.h>

class TreeNode {
public:
    TreeNode(int d)
    : data {d}
    , left {nullptr}
    , right {nullptr}
    {}

    int data;
    TreeNode *left;
    TreeNode *right;
};

class BinaryTree {
public:
    TreeNode* buildTree(const std::vector<int> & nodes, int idx = 0);
    void preorder(TreeNode *root);
    void inorder(TreeNode *root);
    void postorder(TreeNode *root);
    void levelorder(TreeNode *root);

    int countNodes(TreeNode *root);
    int sumOfNodes(TreeNode *root);
    int height(TreeNode *root);
    int diameter(TreeNode *root);

    struct TreeInfo {
        int height;
        int diam;

        TreeInfo(int ht, int di)
        : height{ht}
        , diam{di}
        {}
    };

    TreeInfo diameter_opt(TreeNode *root);
};

// Build a binary tree using preorder sequence of nodes
TreeNode* BinaryTree::buildTree(const std::vector<int> & nodes, [[maybe_unused]] int i) {
    static int idx = -1;
    idx++;
    if(nodes[idx] == -1) {
        return nullptr;
    }

    TreeNode *newNode = new TreeNode(nodes[idx]);
    newNode->left = buildTree(nodes);
    newNode->right = buildTree(nodes);
    return newNode;
}

// root -> left -> right
void BinaryTree::preorder(TreeNode *root) {
    if(!root) {
        // fmt::print("-1 ");
        return;
    }
    fmt::print("{} ", root->data);
    preorder(root->left);
    preorder(root->right);
}

// left -> root -> right
void BinaryTree::inorder(TreeNode *root) {
    if(!root) return;

    inorder(root->left);
    fmt::print("{} ", root->data);
    inorder(root->right);
}

// left -> right -> root
void BinaryTree::postorder(TreeNode *root) {
    if(!root) return;

    postorder(root->left);
    postorder(root->right);
    fmt::print("{} ", root->data);
}

void BinaryTree::levelorder(TreeNode *root) {
    if(!root) return;

    std::queue<TreeNode *> q;
    q.push(root);
    q.push(nullptr);

    while(!q.empty()) {
        TreeNode *curr = q.front();
        q.pop();

        if(curr) {
            fmt::print("{} ", curr->data);
            if(curr->left) q.push(curr->left);
            if(curr->right) q.push(curr->right);
        } else {
            fmt::print("\n");
            if(q.empty()) break;
            else q.push(nullptr);
        }
    }
}

int BinaryTree::countNodes(TreeNode *root) {
    if(!root) return 0;

    int leftNodes{}, rightNodes{};
    leftNodes = countNodes(root->left);
    rightNodes = countNodes(root->right);

    return 1 + leftNodes + rightNodes;
}

int BinaryTree::sumOfNodes(TreeNode *root) {
    if(!root) return 0;

    int leftSum{}, rightSum{};
    leftSum = sumOfNodes(root->left);
    rightSum = sumOfNodes(root->right);

    return root->data + leftSum + rightSum;
}

int BinaryTree::height(TreeNode *root) {
    if(!root) return 0;

    int leftHeight{}, rightHeight{};
    leftHeight = height(root->left);
    rightHeight = height(root->right);

    return std::max(leftHeight, rightHeight) + 1;
}

int BinaryTree::diameter(TreeNode *root) {
    if(!root) return 0;

    int leftDiameter = diameter(root->left);
    int rightDiameter = diameter(root->right);
    int rootDiameter = height(root->left) + height(root->right) + 1;

    return std::max({leftDiameter, rightDiameter, rootDiameter});
}

BinaryTree::TreeInfo BinaryTree::diameter_opt(TreeNode *root) {
    if(!root)  return {0, 0};

    TreeInfo left = diameter_opt(root->left);
    TreeInfo right = diameter_opt(root->right);

    int height = std::max(left.height, right.height) + 1;
    int ldiam = left.diam;
    int rdiam = right.diam;
    int rootdiam = left.height + right.height + 1;
    int diam = std::max({ldiam, rdiam, rootdiam});
    return {height, diam};
}

int main() {
    std::vector<int> nodes {1, 2, 4, 8, -1, -1, -1, 5, -1, -1, 3, -1, 6, -1, -1};
    BinaryTree *tree = new BinaryTree;
    TreeNode *root = tree->buildTree(nodes);
    fmt::print("Preorder: ");
    tree->preorder(root);

    fmt::print("\nInorder: ");
    tree->inorder(root);

    fmt::print("\nPostorder: ");
    tree->postorder(root);

    fmt::print("\nLevelorder: \n");
    tree->levelorder(root);

    // fmt::print("\n");
    fmt::print("Node count = {}\n", tree->countNodes(root));
    fmt::print("Sum of nodes = {}\n", tree->sumOfNodes(root));
    fmt::print("Height of tree = {}\n", tree->height(root));
    fmt::print("diameter of tree = {}\n", tree->diameter(root));
    fmt::print("diameter of tree = {}\n", tree->diameter_opt(root).diam);
}