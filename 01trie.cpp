#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int N = 1e5 + 5, M = 30; // M 表示二进制位数
int n, idx = 0, trie[N * M][2], prefix[N], ans = 0;

void insert(int x)
{ // 将 x 插入到 01-Trie 中
    int p = 0;
    for (int i = M - 1; i >= 0; i--) {
        int b = (x >> i) & 1;
        if (!trie[p][b])
            trie[p][b] = ++idx;
        p = trie[p][b];
    }
}

int query(int x)
{ // 在 01-Trie 上查询与 x 异或后结果的最大值
    int p = 0, res = 0;
    for (int i = M - 1; i >= 0; i--) {
        int b = (x >> i) & 1;
        if (trie[p][1 - b]) {
            res |= (1 << i);
            p = trie[p][1 - b];
        } else {
            p = trie[p][b];
        }
    }
    return res;
}

void dfs(int u, int fa)
{ // 计算每个节点的异或前缀和，并将其插入到 01-Trie 中
    for (auto [v, w] : edges[u]) {
        if (v != fa) {
            prefix[v] = prefix[u] ^ w;
            insert(prefix[v]);
            dfs(v, u);
        }
    }
}

int main()
{
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        edges[u].emplace_back(v, w);
        edges[v].emplace_back(u, w);
    }

    dfs(1, 0);
    for (int i = 1; i <= n; ++i) {
        ans = max(ans, query(prefix[i]));
    }

    cout << ans << endl;
    return 0;
}