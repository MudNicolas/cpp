#include <bits/stdc++.h>
#include <iostream>
using namespace std;

const int MAXN = 505;

/*
next_node[i][c]表示i号点所连、存储字符为c+'a'的点的编号
exist[i]，表示以i节点为结尾的字符串存在，或表示出现了几次
cnt表示当前节点在数组中的编号
*/
int next_node[MAXN][26], exist[MAXN], cnt;

void init() // 初始化
{
    memset(next_node, 0, sizeof(next_node)); // 全部重置为0，表示当前点没有存储字符
    memset(exist, 0, sizeof(exist)); // 全部重置为0，表示当前字符串不存在
    cnt = 1;
}

void insert(string s) // 插入字符串
{
    int cur = 1;
    for (auto c : s) {
        // 尽可能重用之前的路径，如果做不到则新建节点
        if (!next_node[cur][c - 'a'])
            next_node[cur][c - 'a'] = ++cnt;
        cur = next_node[cur][c - 'a']; // 继续向下
    }
    exist[cur] += 1;
}

bool find_prefix(string s) // 查找某个前缀是否出现过
{
    int cur = 1;
    for (auto c : s) {
        // 沿着前缀所决定的路径往下走，如果中途发现某个节点不存在，说明前缀不存在
        if (!next_node[cur][c - 'a'])
            return false;
        cur = next_node[cur][c - 'a'];
    }
    return true;
}

int search(string s)
{
    int cur = 1;
    for (auto c : s) {
        if (!next_node[cur][c - 'a'])
            return 0;
        cur = next_node[cur][c - 'a'];
    }
    return exist[cur];
}

int main()
{
    init();
    insert("apple");
    insert("apple");
    cout << search("apple") << endl;
    cout << search("app") << endl;
    insert("app");
    cout << search("app") << endl;
}