#include <bits/stdc++.h>
#include <iostream>
using namespace std;

const int MAXN = 500005;

int fa[MAXN][20], depth[MAXN]; // fa的第二维大小不应小于log2(MAXN)
bool vis[MAXN];

struct {
    int t, next;
} e[MAXN << 1];

int head[MAXN], tot;

int read()
{
    int ans = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c)) {
        ans = ans * 10 + c - '0';
        c = getchar();
    }
    return ans;
}

void add(int x, int y)
{
    e[++tot].t = y;
    e[tot].next = head[x];
    head[x] = tot;
}

void dfs(int now, int fath)
{ // now表示当前节点，fath表示它的父亲节点
    if (vis[now])
        return;
    vis[now] = true;
    fa[now][0] = fath;
    depth[now] = depth[fath] + 1;
    for (int i = 1; i <= __lg(depth[now]); i++)
        fa[now][i] = fa[fa[now][i - 1]][i - 1]; // now的2^i祖先等于now的2^(i-1)祖先的2^(i-1)祖先
    for (int i = head[now]; i; i = e[i].next) // 遍历树
        if (e[i].t != fath)
            dfs(e[i].t, now);
}

int LCA(int x, int y)
{
    if (depth[x] < depth[y]) // 设x的深度 >= y的深度
        swap(x, y);
    while (depth[x] > depth[y])
        x = fa[x][__lg(depth[x] - depth[y])]; // 先跳到同一深度
    if (x == y) // 到同深度后发现两点相等，说明y是x的祖先
        return y;
    for (int k = __lg(depth[x]); k >= 0; k--) // x,y在LCA的左右子树，不断向上跳
        if (fa[x][k] != fa[y][k]) // 跳到它们LCA的下面一层（两个点肯定不相等），此时它们的父节点为LCA。
            x = fa[x][k], y = fa[y][k]; // 不能在 fa[x][k] == fa[y][k] 时break，因为他们的2^k级父节点相同，不代表2^0级父节点相同
    return fa[x][0]; // 返回父节点
}

int main()
{
    int n = read(), m = read(), s = read();

    for (int i = 1; i <= n - 1; ++i) {
        int x = read(), y = read();
        add(x, y);
        add(y, x);
    }

    dfs(s, 0);
    for (int i = 1; i <= m; ++i) {
        int x = read(), y = read();
        cout << LCA(x, y) << endl;
    }
    return 0;
}