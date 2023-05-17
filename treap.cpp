#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

// 定义Treap的节点结构体
struct TreapNode {
    int val; // 节点值
    int priority; // 节点优先级
    TreapNode* left; // 左子节点指针
    TreapNode* right; // 右子节点指针
    TreapNode(int key)
    {
        this->val = key;
        this->priority = rand();
        this->left = nullptr;
        this->right = nullptr;
    }
};

TreapNode* zig(TreapNode* root)
{
    TreapNode* newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;
    return newRoot;
}
TreapNode* zag(TreapNode* root)
{
    TreapNode* newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;
    return newRoot;
}
// 插入节点到Treap中
TreapNode* insert(TreapNode* root, int val)
{
    if (root == NULL)
        return new TreapNode(val);
    if (val < root->val) // key小于当前值，插到左边
    {
        root->left = insert(root->left, val);
        // 通过旋转操作保持堆的性质
        if (root->left->priority < root->priority)
            return zig(root);
    } else // key大于等于当前值，插到右边
    {
        root->right = insert(root->right, val);
        if (root->right->priority < root->priority)
            return zag(root);
    }
    return root;
}

TreapNode* search(TreapNode* root, int key)
{
    if (root == nullptr || root->val == key) {
        return root;
    }
    if (key < root->val) {
        return search(root->left, key);
    } else {
        return search(root->right, key);
    }
}

TreapNode* deleteNode(TreapNode* root, int key)
{
    if (root == nullptr) {
        return root;
    }
    if (key < root->val) { // key小于当前值，继续在左子树中查找
        root->left = deleteNode(root->left, key);
    } else if (key > root->val) { // key大于当前值，继续在右子树中查找
        root->right = deleteNode(root->right, key);
    } else { // 找到要删除的节点
        if (root->left == nullptr) { // 没有左子节点
            TreapNode* temp = root->right;
            delete root;
            root = temp;
        } else if (root->right == nullptr) { // 没有右子节点
            TreapNode* temp = root->left;
            delete root;
            root = temp;
        } else if (root->left->priority < root->right->priority) { // 左子节点的优先级更高
            root = zig(root); // 向右旋转
            root->right = deleteNode(root->right, key); // 继续在右子树中删除节点
        } else { // 右子节点的优先级更高
            root = zag(root); // 向左旋转
            root->left = deleteNode(root->left, key); // 继续在左子树中删除节点
        }
    }
    return root;
}

// 中序遍历Treap
void inorderTraversal(TreapNode* root)
{
    if (root == nullptr) {
        return;
    }
    inorderTraversal(root->left);
    cout << root->val << " ";
    inorderTraversal(root->right);
}

TreapNode* predecessor(TreapNode* root, int key)
{
    TreapNode* pred = nullptr;
    while (root) {
        if (root->val >= key) { // 当前节点的key大于等于目标key，向左遍历
            root = root->left;
        } else { // 当前节点的key小于目标key，更新前驱节点并向右遍历
            pred = root;
            root = root->right;
        }
    }
    return pred;
}

TreapNode* successor(TreapNode* root, int key)
{
    TreapNode* succ = nullptr;
    while (root) {
        if (root->val <= key) { // 当前节点的key小于等于目标key，向右遍历
            root = root->right;
        } else { // 当前节点的key大于目标key，更新后继节点并向左遍历
            succ = root;
            root = root->left;
        }
    }
    return succ;
}

// 计算Treap中节点的子树大小
int getSize(TreapNode* root)
{
    if (!root)
        return 0;
    return 1 + getSize(root->left) + getSize(root->right);
}

// 查询Treap中第k大的节点
TreapNode* findKth(TreapNode* root, int k)
{
    if (!root)
        return nullptr;
    int leftSize = getSize(root->left);
    if (leftSize >= k) { // 第k大的节点在左子树中
        return findKth(root->left, k);
    } else if (leftSize == k - 1) { // 当前节点即为第k大的节点
        return root;
    } else { // 第k大的节点在右子树中
        return findKth(root->right, k - leftSize - 1);
    }
}

int main()
{
    // 初始化随机种子
    srand(time(NULL));

    // 构建一棵Treap
    TreapNode* root = NULL;
    root = insert(root, 5);
    root = insert(root, 2);
    root = insert(root, 8);
    root = insert(root, 1);
    root = insert(root, 3);
    root = insert(root, 9);
    root = insert(root, 4);
    cout << root->val << endl;
    cout << findKth(root, 2)->val << endl;

    root = deleteNode(root, root->val);
    //  中序遍历Treap
    inorderTraversal(root);
    cout << search(root, 5)->val << endl;

    return 0;
}