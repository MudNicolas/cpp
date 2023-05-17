#include <bits/stdc++.h>
#include <iostream>

using namespace std;

const int MAXN = 1e5 + 5;
typedef long long ll;

int n, m, r, p, cnt;
int head[MAXN], fa[MAXN], depth[MAXN], size[MAXN], son[MAXN], id[MAXN], top[MAXN], h_son[MAXN];
int val[MAXN];

inline ll read()
{
    ll ans = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c)) {
        ans = ans * 10 + c - '0';
        c = getchar();
    }
    return ans;
}

struct Edge {
    int to, next;
} edge[MAXN << 1];

void add_edge(int u, int v)
{
    edge[++cnt].to = v;
    edge[cnt].next = head[u];
    head[u] = cnt;
}

// 先得到每个节点的fa（父节点）、size（子树大小）、depth（深度）、h_son（重子节点）
void dfs1(int p, int dep = 1)
{
    int p_size = 1; // 当前节点树size
    int ma = 0; // 寻找重子节点
    depth[p] = dep; // 当前节点深度
    for (int i = head[p]; i; i = edge[i].next) { // 遍历临接表
        int q = edge[i].to; // 获取子节点q
        if (!depth[q]) { // q没遍历过
            dfs1(q, dep + 1);
            fa[q] = p; // q的父节点设为p
            p_size += size[q]; // p子树的size加上q子树的size
            if (size[q] > ma)
                h_son[p] = q, ma = size[q]; // 设定p的重子节点为q
        }
    }
    size[p] = p_size;
}

int dfscnt, dfsn[MAXN], subtree_max_dfsn[MAXN];
// 得到每个节点的top（链头，即所在的重链中深度最小的那个节点）
void dfs2(int p)
{
    dfsn[p] = ++dfscnt; // 设定p点dfs序
    // 优先遍历重链
    if (h_son[p] != 0) { // p点有重子节点
        top[h_son[p]] = top[p]; // 设置重子节点链头为p的链头（需要先把根节点的top初始化为自身）
        dfs2(h_son[p]); // 递归遍历重链
    }
    for (int i = head[p]; i; i = edge[i].next) { // 遍历临接表
        int q = edge[i].to; // 获取子节点q
        if (!top[q]) { // 若q的链头没找到（此时肯定是轻节点）
            top[q] = q; // q的链头是q（开启一个新的重链，或单独的节点）
            dfs2(q);
        }
    }
    subtree_max_dfsn[p] = dfscnt; // p点的子树遍历结束，设置p树的最大dfs深度为cnt
}

int lca(int a, int b)
{
    // 当ab点不在一条链时，将深链上跳，最终ab同链
    while (top[a] != top[b]) {
        if (depth[top[a]] > depth[top[b]])
            a = fa[top[a]];
        else
            b = fa[top[b]];
    }
    // ab同链，返回较浅节点
    return (depth[a] > depth[b] ? b : a);
}

int mark[MAXN * 4], tree[MAXN * 4];
int N;

// zkw线段树build
void build()
{
    N = 1 << __lg(n) + 1;
    for (ll i = 1; i <= n; i++)
        tree[N + dfsn[i]] = val[i] % p; // 以dfs序建立线段树
    for (ll i = N - 1; i; i--)
        tree[i] = (tree[i << 1] + tree[i << 1 | 1]) % p;
}

// zkw线段树update
void update(ll l, ll r, ll k)
{
    // len是本层节点对应的区间长度，cntl、cntr是左、右两指针分别实际修改的区间长度
    ll len = 1, cntl = 0, cntr = 0;
    for (l += N - 1, r += N + 1; l ^ r ^ 1; l >>= 1, r >>= 1, len <<= 1) {
        tree[l] += (cntl * k) % p, tree[r] += (cntr * k) % p;
        tree[l] %= p;
        if (~l & 1)
            tree[l ^ 1] += (k * len) % p, mark[l ^ 1] += k, cntl += len, tree[l ^ 1] %= p;
        if (r & 1)
            tree[r ^ 1] += (k * len) % p, mark[r ^ 1] += k, cntr += len, tree[r ^ 1] %= p;
    }
    // 修改汇聚到同一点之后，向上将修改推到根节点
    for (; l; l >>= 1, r >>= 1)
        tree[l] += (cntl * k) % p, tree[r] += (cntr * k) % p, tree[l] %= p, tree[r] %= p;
}

// 路径update
void update_path(int x, int y, int k)
{
    k %= p;
    while (top[x] != top[y]) { // 不在一个路径时
        if (depth[top[x]] > depth[top[y]]) { // 深链上跳
            update(dfsn[top[x]], dfsn[x], k); // 更新x点到链头的区间
            x = fa[top[x]]; // 链上跳
        } else {
            update(dfsn[top[y]], dfsn[y], k); // 更新y点到链头的区间
            y = fa[top[y]]; // 链上跳
        }
    }
    // 在同一个路径，退化为普通线段树区间更新
    if (depth[x] > depth[y])
        update(dfsn[y], dfsn[x], k);
    else
        update(dfsn[x], dfsn[y], k);
}

// zkw线段树query
ll query(ll l, ll r)
{
    ll ans = 0, len = 1, cntl = 0, cntr = 0;
    for (l += N - 1, r += N + 1; l ^ r ^ 1; l >>= 1, r >>= 1, len <<= 1) {
        // 加上标记更改的值大小
        ans += (cntl * mark[l] + cntr * mark[r]) % p;
        ans %= p;
        if (~l & 1)
            ans += tree[l ^ 1], cntl += len;
        if (r & 1)
            ans += tree[r ^ 1], cntr += len;
    }
    ans %= p;
    for (; l; l >>= 1, r >>= 1)
        ans += (cntl * mark[l] + cntr * mark[r]) % p, ans %= p;
    return ans;
}

// 路径query
int query_path(int x, int y)
{
    int ans = 0;
    while (top[x] != top[y]) { // 不在一个路径
        if (depth[top[x]] > depth[top[y]]) { // 深链上跳
            ans += query(dfsn[top[x]], dfsn[x]) % p; // 查询链上区间和（深链节点连续）
            ans %= p;
            x = fa[top[x]];
        } else {
            ans += query(dfsn[top[y]], dfsn[y]) % p;
            ans %= p;
            y = fa[top[y]];
        }
    }
    // 在同一个路径，退化为普通线段树区间查询
    if (depth[x] > depth[y])
        ans += query(dfsn[y], dfsn[x]) % p;
    else
        ans += query(dfsn[x], dfsn[y]) % p;
    return ans %= p;
}

void update_subtree(int x, int k)
{
    update(dfsn[x], subtree_max_dfsn[x], k);
}

int query_subtree(int x)
{
    return query(dfsn[x], subtree_max_dfsn[x]) % p;
}

void init(int root)
{
    top[root] = root; // 初始化根节点链头为自身
    dfs1(root);
    dfs2(root);
    build();
}

int main()
{
    n = read(), m = read(), r = read(), p = read();
    for (int i = 1; i <= n; i++)
        val[i] = read();
    for (int i = 1; i <= n - 1; i++) {
        int x = read(), y = read();
        add_edge(x, y);
        add_edge(y, x);
    }
    init(r);
    for (; m; m--) {
        int opt, x, y, z;
        opt = read();
        if (opt == 1) {
            x = read(), y = read(), z = read();
            update_path(x, y, z);
        }
        if (opt == 2) {
            x = read(), y = read();
            printf("%d\n", query_path(x, y) % p);
        }
        if (opt == 3) {
            x = read(), z = read();
            update_subtree(x, z);
        }
        if (opt == 4) {
            x = read();
            printf("%d\n", query_subtree(x) % p);
        }
    }
}