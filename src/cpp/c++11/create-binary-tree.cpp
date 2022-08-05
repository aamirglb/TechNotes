#include <iostream>
#include <queue>
#include <stack>
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

void insertNode(TreeNode<int>* &node, std::queue<TreeNode<int> *> &q, int value)
{
    if(value != -1) {
        TreeNode<int> *t = new TreeNode<int>(value);
        node = t;
        q.push(t);
    }
}

void createBinaryTree(TreeNode<int> * &root, std::initializer_list<int> nodeList)
{
    std::queue<TreeNode<int> *> q;
    bool isLeft{true};

    for(const auto& value : nodeList) {
        if(!root) {
            root = new TreeNode(value);
            q.push(root);
        } else {
            TreeNode<int> *p = q.front();
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

void createBinaryTree(TreeNode<int> * &root)
{
    TreeNode<int> *p, *t;
    std::queue<TreeNode<int> *> q;
    int x;

    std::cout << "Enter root value: ";
    std::cin >> x;

    if(!root) {
        root = new TreeNode<int>(x);
        std::cout << "root node created\n";
        q.push(root);
    }

    while(!q.empty()) {
        p = q.front();
        q.pop();

        std::cout << "Enter left child of '" << p->data << "': ";
        std::cin >> x;

        if(x != -1) {
            t = new TreeNode<int>(x);
            p->left = t;
            q.push(t);
        }

        std::cout << "Enter right child of '" << p->data << "': ";
        std::cin >> x;

        if(x != -1) {
            t = new TreeNode<int>(x);
            p->right = t;
            q.push(t);
        }
    }
}

void preorder(TreeNode<int> *root) {
    if(root) {
        std::cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
     }
}

void inorder(TreeNode<int>* root) {
    if(root) {
        inorder(root->left);
        std::cout << root->data << " ";
        inorder(root->right);
     }
}

void postorder(TreeNode<int>* root) {
    if(root) {
        postorder(root->left);
        postorder(root->right);
        std::cout << root->data << " ";
     }
}

void preorderIter(TreeNode<int> *root) {
    std::stack<TreeNode<int> *> stk;
    auto *t = root;
    while(t || !stk.empty()) {
        if(t) {
            std::cout << t->data << " ";
            stk.push(t);
            t = t->left;
        } else {
            t = stk.top();
            stk.pop();
            t = t->right;
        }
    }
}

void inorderIter(TreeNode<int>* root) {
    std::stack<TreeNode<int> *> stk;
    auto *t = root;

    while(t || !stk.empty()) {
        if(t) {
            stk.push(t);
            t = t->left;
        } else {
            t = stk.top();
            std::cout << t->data << " ";
            stk.pop();
            t = t->right;
        }
    }
}


// void postorderIter(TreeNode<int>* root) {
//     std::stack<TreeNode<int> *> stk;
//     auto *t = root;
//     std::uintptr_t tmp;

//     while(t || !stk.empty()) {
//         if(t) {
//             stk.push(t);
//             t = t->left;
//         } else {
//             tmp = reinterpret_cast<uintptr_t>(stk.top());
//             std::cout << "tmp: " << tmp << std::endl;
//             stk.pop();
//             if(tmp > 0) {
//                 stk.push(reinterpret_cast<TreeNode<int> *>(tmp * -1));
//                 t = reinterpret_cast<TreeNode<int> *>(tmp)->right;
//             } else {
//                 std::cout << reinterpret_cast<TreeNode<int> *>(tmp)->data << " ";
//                 t = nullptr;
//             }
//         }
//     }
// }

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

int countNodes(TreeNode<int> *root)
{
    int x, y;
    if(root) {
        x = countNodes(root->left);
        y = countNodes(root->right);
        return x+y+1;
    }
    return 0;
}

int countNodeDegree(TreeNode<int> *root)
{
    int x, y;
    if(root) {
        x = countNodeDegree(root->left);
        y = countNodeDegree(root->right);
        if(root->left && root->right)
            return x+y+1;
        else
            return x+y;
    }
    return 0;
}

int countLeafNodes(TreeNode<int> *root)
{
    int x, y;
    if(root) {
        x = countLeafNodes(root->left);
        y = countLeafNodes(root->right);
        if(!root->left && !root->right)
            return x+y+1;
        else
            return x+y;
    }
    return 0;
}

int sumOfAllNodes(TreeNode<int> *root)
{
    int x, y;
    if(root) {
        x = sumOfAllNodes(root->left);
        y = sumOfAllNodes(root->right);
        return x+y+root->data;
    }
    return 0;
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

int main()
{
    TreeNode<int> *root {nullptr};
    // createBinaryTree(root);
    // createBinaryTree(root, {10, 20, 30, 40, -1, 60, 50});
    //                         [ 8 ] [ 3 ]   [ 5 ]  [ 12 ]  [10]   [6]    [4]   [ 2 ]
    //                         vvvv  vvvvv   vvvvv  vvvvv   vvvvv  vvvv   vvvv  vvvvv
    createBinaryTree(root, {8, 3, 5, 12, -1, 10, 6, -1, 4, -1, -1, 2, -1, 9, 7, -1, -1, 11, -1});


    std::cout << "\nPreorder Traversel: \n";
    preorder(root);

    std::cout << "\nInorder Traversel: \n";
    inorder(root);

    std::cout << "\nPostorder Traversel: \n";
    postorder(root);

    std::cout << "\nPreorder Traversel (Iterative): \n";
    preorderIter(root);

    std::cout << "\nInorder Traversel (Iterative): \n";
    inorderIter(root);

    // std::cout << "\nPostorder Traversel (Iterative): \n";
    // postorderIter(root);

    std::cout << "\nLevelorder Traversal: \n";
    levelOrderTraversal(root);

    std::cout << "Total Nodes in thre tree: ";
    std::cout << countNodes(root) << std::endl;

    std::cout << "Nodes with degree two: ";
    std::cout << countNodeDegree(root) << std::endl;

    std::cout << "Total leaf nodes: ";
    std::cout << countLeafNodes(root) << std::endl;

    std::cout << "Sum of all nodes: ";
    std::cout << sumOfAllNodes(root) << std::endl;

    std::cout << "Tree height: ";
    std::cout << getTreeHeight(root) << std::endl;
}