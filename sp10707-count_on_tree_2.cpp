#include <bits/stdc++.h>
using namespace std;

const int maxn = 200200;

inline int read()
{
    int res = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        res = (res << 1) + (res << 3) + (c ^ 48), c = getchar();
    return res;
}
int cnt[maxn], dis[maxn], first[maxn], last[maxn], ans[maxn], belong[maxn], visited[maxn], ora_cnt, l = 1, r, now, block_size, block_num; // 莫队相关
int ora_ord[maxn], val[maxn], head[maxn], depth[maxn], fa[maxn][30], edge_cnt; // 树相关
int n, m;

struct Edge {
    int to, next;
} edge[maxn << 1];

void add_edge(int u, int v)
{
    edge[++edge_cnt].to = v;
    edge[edge_cnt].next = head[u];
    head[u] = edge_cnt;
}

void dfs(int p)
{
    ora_ord[++ora_cnt] = p;
    first[p] = ora_cnt;
    for (int i = head[p]; i; i = edge[i].next) {
        int q = edge[i].to;
        if (depth[q])
            continue;
        depth[q] = depth[p] + 1;
        fa[q][0] = p;
        for (int i = 1; i <= __lg(depth[q]); ++i)
            fa[q][i] = fa[fa[q][i - 1]][i - 1]; // 倍增法预处理2^i级祖先
        dfs(q);
    }
    ora_ord[++ora_cnt] = p;
    last[p] = ora_cnt;
}

// 倍增求LCA
int LCA(int x, int y)
{
    if (depth[x] < depth[y])
        swap(x, y);
    while (depth[x] > depth[y])
        x = fa[x][__lg(depth[x] - depth[y])];
    if (x == y)
        return y;
    for (int k = __lg(depth[x]); k >= 0; k--)
        if (fa[x][k] != fa[y][k])
            x = fa[x][k], y = fa[y][k];
    return fa[x][0]; // 返回父节点
}

struct query {
    int l, r, lca, id;
    friend bool operator<(query const& a, query const& b)
    {
        return (belong[a.l] ^ belong[b.l]) ? (belong[a.l] < belong[b.l]) : ((belong[a.l] & 1) ? a.r < b.r : a.r > b.r);
    }
} q[maxn];

// 没访问过加上当前节点，访问过删去当前节点（去除出现2次的点）
void work(int pos)
{
    visited[pos] ? now -= !--cnt[val[pos]] : now += !cnt[val[pos]]++;
    visited[pos] ^= 1;
}
int main()
{
    freopen("sp10707.in", "r", stdin);

    n = read();
    m = read();
    for (int i = 1; i <= n; ++i)
        val[i] = dis[i] = read(); // dis数组用于离散数据
    sort(dis + 1, dis + n + 1);
    int tot = unique(dis + 1, dis + n + 1) - dis - 1; // unique去重，返回去重之后的尾指针

    for (int i = 1; i <= n; ++i)
        val[i] = lower_bound(dis + 1, dis + tot + 1, val[i]) - dis; // 将val离散化

    for (int i = 1; i < n; ++i) {
        int x = read(), y = read();
        add_edge(x, y);
        add_edge(y, x);
    }
    depth[1] = 1;
    dfs(1);

    block_size = sqrt(ora_cnt), block_num = ceil((double)ora_cnt / block_size);
    for (int i = 1; i <= block_num; ++i)
        for (int j = block_size * (i - 1) + 1; j <= i * block_size; ++j)
            belong[j] = i;

    for (int i = 1; i <= m; ++i) {
        int L = read(), R = read(), lca = LCA(L, R);
        if (first[L] > first[R])
            swap(L, R); // 确保每个询问在欧拉序中L出现得比R早
        if (L == lca) { // 若同链，欧拉序连续，lca在区间中
            q[i].l = first[L], q[i].r = first[R];
        } else { // 若不同链，lca不在欧拉序区间中，需要特判lca
            q[i].l = last[L], q[i].r = first[R], q[i].lca = lca;
        }
        q[i].id = i;
    }

    sort(q + 1, q + m + 1);
    for (int i = 1; i <= m; ++i) {
        while (l < q[i].l)
            work(ora_ord[l++]);
        while (l > q[i].l)
            work(ora_ord[--l]);
        while (r < q[i].r)
            work(ora_ord[++r]);
        while (r > q[i].r)
            work(ora_ord[r--]);
        if (q[i].lca)
            work(q[i].lca); // 加上lca
        ans[q[i].id] = now;
        if (q[i].lca)
            work(q[i].lca); // 去掉lca（lca与欧拉序区间可能不连续，需要特判）
    }
    for (int i = 1; i <= m; ++i)
        printf("%d\n", ans[i]);
    return 0;
}