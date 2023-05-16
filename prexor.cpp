#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
vector<pair<int, int>> edges[MAXN];
int n, prefix[MAXN], ans = 0;

void dfs(int u, int fa)
{
    for (auto it = edges[u].begin(); it != edges[u].end(); ++it) {
        int v = it->first;
        int w = it->second;
        if (v != fa) {
            prefix[v] = prefix[u] ^ w;
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
        for (int j = i + 1; j <= n; ++j) {
            ans = max(ans, prefix[i] ^ prefix[j]);
        }
    }

    cout << ans << endl;
    return 0;
}