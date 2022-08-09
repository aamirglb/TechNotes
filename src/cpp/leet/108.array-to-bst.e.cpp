// Given an integer array nums where the elements are sorted in ascending order, convert it to a height-balanced binary search tree.
// A height-balanced binary tree is a binary tree in which the depth of the two subtrees of every node never differs by more than one.

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

TreeNode *insert(TreeNode * &root, int key)
{
    if(!root) {
        root = new TreeNode(key);
        return root;
    }
    if(key < root->val)
        root->left = insert(root->left, key);
    else if(key > root->val)
        root->right = insert(root->right, key);
    return root;
}

void preorder(TreeNode *root) {
    if(root) {
        cout << root->val << " ";
        preorder(root->left);
        preorder(root->right);
    } else {
        cout << "null" << " ";
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

TreeNode *insertNode(vector<int>& nums, int low, int high) {
    if(low > high) return nullptr;

    int mid = (low + high) / 2;
    auto root = new TreeNode(nums[mid]);
    root->left = insertNode(nums, low, mid - 1);
    root->right = insertNode(nums, mid+1, high);
    return root;
}

TreeNode* sortedArrayToBST(vector<int>& nums) {
    return insertNode(nums, 0, nums.size() - 1);
}

int main() {
    vector<int> nums {-10, -3, 0, 5, 9};
    auto r = sortedArrayToBST(nums);
    breathFirstSearch(r);

}
