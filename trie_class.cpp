#include <cstring>
#include <iostream>
#include <map>
using namespace std;

class TrieNode {
public:
    bool isEndOfWord;
    map<char, TrieNode*> children;
    TrieNode() // 构造函数
    {
        isEndOfWord = false;
        children = map<char, TrieNode*>(); // 构造一个空的children map对象
    }
};

class Trie {
private:
    TrieNode* root; // 定义trie的根节点

public:
    Trie()
    {
        root = new TrieNode(); // 构造对象时，创建root节点对象
    }

    void insert(string word)
    {
        TrieNode* node = root; // 防止把root给改了
        for (auto c : word) {
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->isEndOfWord = true;
    }

    bool search(string word)
    {
        TrieNode* node = root;
        for (auto c : word) {
            if (node->children.find(c) == node->children.end()) {
                return false;
            }
            node = node->children[c];
        }
        return node->isEndOfWord;
    }

    bool startsWith(string prefix)
    {
        TrieNode* node = root;
        for (char c : prefix) {
            if (node->children.find(c) == node->children.end()) {
                return false;
            }
            node = node->children[c];
        }
        return node != nullptr;
    }

    void remove(string word)
    {
        remove(root, word, 0);
    }

private:
    bool remove(TrieNode* node, string word, int depth)
    {
        if (depth == word.size()) {
            if (node->isEndOfWord) {
                node->isEndOfWord = false; // 将此字符串设为不存在
                return node->children.empty(); // map::empty()判断map对象是否为空，若不为空，说明有其他字符串依赖此节点，不能删除
            }
            return false; // 没有这个字符串，不用删除
        }

        char c = word[depth]; // 获取word字符串的第depth个字符
        if (node->children.find(c) == node->children.end()) {
            return false; // 若depth没到字符串长度时当前节点已无子节点，也说明该字符串不存在，不用删除
        }

        bool shouldDeleteNode = remove(node->children[c], word, depth + 1);
        if (shouldDeleteNode) {
            node->children.erase(c); //  map::erase()会删除指定的键值对，并释放该键值对对象的内存。
            return node->children.empty(); // return true，表示该节点被删了，可以根据情况删除上一层的节点了
        }
        return false;
    }
};

int main()
{
    Trie trie;

    trie.insert("apple");
    trie.insert("apple");
    cout << (trie.search("apple") ? "Found" : "Not Found") << endl;

    trie.remove("apple");
    cout << (trie.search("apple") ? "Found" : "Not Found") << endl;

    cout << (trie.search("app") ? "Found" : "Not Found") << endl;
    trie.insert("app");
    cout << (trie.search("app") ? "Found" : "Not Found") << endl;

    return 0;
}