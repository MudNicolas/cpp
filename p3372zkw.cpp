#include <bits/stdc++.h>
#include <iostream>
using namespace std;
typedef long long ll;

inline ll read()
{
    ll ans = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
    {
        ans = ans * 10 + c - '0';
        c = getchar();
    }
    return ans;
}

const ll maxn = 10001;
ll tree[maxn * 4], a[maxn], mark[maxn * 4];
ll n, m, N;

void build()
{
    N = 1 << __lg(n) + 1; // 加法优先级比左移高
    for (ll i = 1; i <= n; i++)
        tree[i + N] = a[i]; // 叶子节点最左侧留空，方便查询
    for (ll i = N - 1; i; i--)
        tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

void update(ll x, ll d) // 单点修改
{
    for (ll i = x + N; i; i >>= 1)
        tree[i] += d;
}

void update(ll l, ll r, ll d)
{
    // len是本层节点对应的区间长度，cntl、cntr是左、右两指针分别实际修改的区间长度
    ll len = 1, cntl = 0, cntr = 0;
    for (l += N - 1, r += N + 1; l ^ r ^ 1; l >>= 1, r >>= 1, len <<= 1)
    {
        tree[l] += cntl * d, tree[r] += cntr * d;
        if (~l & 1)
            tree[l ^ 1] += d * len, mark[l ^ 1] += d, cntl += len;
        if (r & 1)
            tree[r ^ 1] += d * len, mark[r ^ 1] += d, cntr += len;
    }
    // 修改汇聚到同一点之后，向上将修改推到根节点
    for (; l; l >>= 1, r >>= 1)
        tree[l] += cntl * d, tree[r] += cntr * d;
}

ll query(ll l, ll r)
{
    ll ans = 0, len = 1, cntl = 0, cntr = 0;
    for (l += N - 1, r += N + 1; l ^ r ^ 1; l >>= 1, r >>= 1, len <<= 1)
    {
        // 加上标记更改的值大小
        ans += cntl * mark[l] + cntr * mark[r];
        if (~l & 1)
            ans += tree[l ^ 1], cntl += len;
        if (r & 1)
            ans += tree[r ^ 1], cntr += len;
    }
    for (; l; l >>= 1, r >>= 1)
        ans += cntl * mark[l] + cntr * mark[r];
    return ans;
}

int main()
{
    n = read(), m = read();
    for (ll i = 1; i <= n; i++)
    {
        a[i] = read();
    }
    build();
    for (int i = 0; i < m; ++i)
    {
        ll opr = read(), l = read(), r = read();
        if (opr == 1)
        {
            ll d = read();
            update(l, r, d);
        }
        else
            printf("%lld\n", query(l, r));
    }
}