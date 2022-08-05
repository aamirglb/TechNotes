#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <initializer_list>

template <typename T>
struct TreeNode {
    T data;
    TreeNode *left;
    TreeNode *right;

    TreeNode() {
        data = -1;
        left = nullptr;
        right = nullptr;
    }

    TreeNode(T d)
        : data {d}
        , left {nullptr}
        , right {nullptr}
    {}

    TreeNode(T d, TreeNode *l, TreeNode *r)
        : data {d}
        , left {l}
        , right {r}
    {}
};

TreeNode<int> *insert(TreeNode<int> * &root, int key)
{
    TreeNode<int> *tmp {nullptr};
    if(!root) {
        tmp = new TreeNode<int>(key);
        return tmp;
    }
    if(key < root->data)
        root->left = insert(root->left, key);
    else if(key > root->data)
        root->right = insert(root->right, key);
    return root;
}

void insertIter(TreeNode<int> * &root, int key) {
    TreeNode<int> *tmp = root;
    TreeNode<int> *prev {nullptr};
    TreeNode<int> *p;

    if(!root) {
        root = new TreeNode<int>(key);
        return;
    }

    while(tmp) {
        prev = tmp;
        if(key < tmp->data)
            tmp = tmp->left;
        else if(key > tmp->data)
            tmp = tmp->right;
        else
            return;
    }
    p = new TreeNode<int>(key);
    if(key < prev->data)
        prev->left = p;
    else
        prev->right = p;
}

int getTreeHeight(TreeNode<int> *root)
{
    int x = 0, y = 0;
    if(root) {
        x = getTreeHeight(root->left);
        y = getTreeHeight(root->right);
        if(x > y) return x + 1;
        else return y + 1;
    }
    return 0;
}

TreeNode<int> *InorderPredecessor(TreeNode<int> *root)
{
    while(root && root->right) {
        root = root->right;
    }
    return root;
}

TreeNode<int> *InorderSuccessor(TreeNode<int> *root)
{
    while(root && root->left) {
        root = root->left;
    }
    return root;
}

TreeNode<int> *deleteNode(TreeNode<int> *root, int key)
{
    if(!root) {
        return nullptr;
    }
    if(!root->left && !root->right) {
        delete root;
        return nullptr;
    }

    if(key < root->data)
        root->left = deleteNode(root->left, key);
    else if(key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        // If height of left subtree is more than right subtree
        if(getTreeHeight(root->left) > getTreeHeight(root->right)) {
            // get inorder predacessor
            auto q = InorderPredecessor(root->left);
            root->data = q->data;
            root->left = deleteNode(root->left, q->data);
        } else {
            auto q = InorderSuccessor(root->right);
            root->data = q->data;
            root->right = deleteNode(root->right, q->data);
        }
    }
    return root;
}
void createBinarySearchTree(TreeNode<int> * &root, std::initializer_list<int> lst)
{
    for(const auto& ele : lst) {
        // root = insert(root, ele);
        insertIter(root, ele);
    }
}

void inorder(TreeNode<int>* root) {
    if(root) {
        inorder(root->left);
        std::cout << root->data << " ";
        inorder(root->right);
     }
}

TreeNode<int>* search(TreeNode<int> *root, int key)
{
    TreeNode<int> *tmp = root;

    while(tmp) {
        if(key == tmp->data)
            return tmp;
        else if(key < tmp->data)
            tmp = tmp->left;
        else
            tmp = tmp->right;
    }
    return nullptr;
}

// Level order traversal of binary search tree
void levelOrderTraversal(TreeNode<int> *root)
{
    TreeNode<int>* p = root;
    std::queue<TreeNode<int> *> q;
    std::cout << p->data << " ";
    q.push(p);

    while(!q.empty()) {
        p = q.front();
        q.pop();
        if(p->left) {
            std::cout << p->left->data << " ";
            q.push(p->left);
        }
        if(p->right) {
            std::cout << p->right->data << " ";
            q.push(p->right);
        }
    }
}

void createFromPreorder(TreeNode<int> * &root, std::vector<int> &arr)
{
    std::stack<TreeNode<int> *> stk;
    TreeNode<int> *t;
    size_t i {};
    root = new TreeNode<int>(arr[i++]);

    TreeNode<int> *p = root;

    while(i < arr.size()) {
        if(arr[i] < p->data) {
            t = new TreeNode<int>(arr[i++]);
            p->left = t;
            stk.push(p);
            p = t;
        } else {
            auto top = stk.top();
            if(arr[i] > p->data && (arr[i] < top->data || stk.empty())) {
                t = new TreeNode(arr[i++]);
                p->right = t;
            } else {
                p = stk.top();
                stk.pop();
            }
        }
    }
}

int main()
{
    TreeNode<int> *root {nullptr};
    // createBinarySearchTree(root, {9, 15, 5, 20, 16, 8, 12, 3, 6});
    // createBinarySearchTree(root, {10, 5, 20, 8, 30});
    createBinarySearchTree(root, {50, 10, 40, 20, 30});

    std::cout << "Level order traversal: \n";
    levelOrderTraversal(root);

    std::cout << "\nInorder traversal: \n";
    inorder(root);

    int key {30};
    auto p = search(root, key);
    if(p) std::cout << "\nKey " << p->data << " found in the tree.\n";
    else std::cout << "\nKey " << key << " not found in the tree.\n";

    deleteNode(root, key);
    std::cout << "\nInorder traversal: \n";
    inorder(root);
}
