#include <bits/stdc++.h>
using namespace std;

// 定义二叉搜索树结点
struct TreeNode {
    // val是本节点的值
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x)
    {
        (*this).val = x;
        (*this).left = nullptr;
        (*this).right = nullptr;
    }
};

// 向二叉搜索树中插入一个结点
TreeNode* insert(TreeNode* root, int val)
{
    if (root == nullptr)
        return new TreeNode(val);
    if (val < root->val)
        root->left = insert(root->left, val);
    else
        root->right = insert(root->right, val);
    return root;
}

// 构建二叉搜索树
TreeNode* build_tree(int* arr, int n)
{
    TreeNode* root = nullptr;
    for (int i = 1; i < n; i++) {
        root = insert(root, arr[i]);
    }
    return root;
}

// 查找二叉搜索树中的最小值
void findMin(TreeNode* root)
{
    while (root->left != nullptr) {
        root = root->left;
    }
    cout << root->val << " ";
}

// 查找二叉搜索树中的最大值
void findMax(TreeNode* root)
{
    while (root->right != nullptr) {
        root = root->right;
    }
    cout << root->val << " ";
}

// 查找节点并返回指针
TreeNode* search(TreeNode* root, int key)
{
    if (root == nullptr)
        return nullptr;
    if (key == root->val)
        return root;
    else if (key < root->val)
        return search(root->left, key);
    else
        return search(root->right, key);
}

TreeNode* deleteNode(TreeNode* root, int key)
{
    if (root == nullptr)
        return nullptr;
    if (key < root->val)
        root->left = deleteNode(root->left, key);
    else if (key > root->val)
        root->right = deleteNode(root->right, key);
    else {
        // 找到了要删除的节点
        if (root->left == nullptr) {
            // 没有左子节点，直接将右子节点替换为当前节点
            TreeNode* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            // 没有右子节点，直接将左子节点替换为当前节点
            TreeNode* temp = root->left;
            delete root;
            return temp;
        } else {
            // 有两个子节点，需要找到后继节点
            TreeNode* successor = root->right;
            while (successor->left != nullptr) {
                successor = successor->left;
            }
            // 将后继节点的值赋给当前节点，并删除后继节点
            root->val = successor->val;
            root->right = deleteNode(root->right, successor->val);
        }
    }
    return root;
}

// 中序遍历二叉搜索树
void inorder_traversal(TreeNode* root)
{
    if (root == nullptr)
        return;
    inorder_traversal(root->left);
    cout << root->val << " ";
    inorder_traversal(root->right);
}

int main()
{
    int arr[] = { 5, 3, 7, 1, 9, 4, 6 };
    int n = sizeof(arr) / sizeof(arr[0]);

    TreeNode* root = build_tree(arr, n);
    cout << root->val << endl;
    root = deleteNode(root, 3);
    inorder_traversal(root);
    findMin(root);
    findMax(root);

    return 0;
}