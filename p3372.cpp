#include <bits/stdc++.h>
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

const ll MAXN = 100001;
ll n, m, A[MAXN], tree[MAXN * 3], mark[MAXN * 3];

inline void push_down(ll p, ll len)
{
    mark[p * 2] += mark[p];
    mark[p * 2 + 1] += mark[p];
    tree[p * 2] += mark[p] * (len - len / 2);
    tree[p * 2 + 1] += mark[p] * (len / 2);
    mark[p] = 0;
}
void build(ll l = 1, ll r = n, ll p = 1)
{
    if (l == r)
        tree[p] = A[l];
    else
    {
        ll mid = (l + r) / 2;
        build(l, mid, p * 2);
        build(mid + 1, r, p * 2 + 1);
        tree[p] = tree[p * 2] + tree[p * 2 + 1];
    }
}
void update(ll tl, ll tr, ll k, ll p = 1, ll l = 1, ll r = n)
{
    if (l > tr || r < tl)
        return;
    else if (l >= tl && r <= tr)
    {
        tree[p] += (r - l + 1) * k;
        if (r > l)
            mark[p] += k;
    }
    else
    {
        ll mid = (l + r) / 2;
        push_down(p, r - l + 1);
        update(tl, tr, k, p * 2, l, mid);
        update(tl, tr, k, p * 2 + 1, mid + 1, r);
        tree[p] = tree[p * 2] + tree[p * 2 + 1];
    }
}
ll query(ll tl, ll tr, ll p = 1, ll l = 1, ll r = n)
{
    if (l > tr || r < tl)
        return 0;
    else if (l >= tl && r <= tr)
        return tree[p];
    else
    {
        ll mid = (l + r) / 2;
        push_down(p, r - l + 1);
        return query(tl, tr, p * 2, l, mid) + query(tl, tr, p * 2 + 1, mid + 1, r);
    }
}
int main()
{
    n = read();
    m = read();
    for (int i = 1; i <= n; ++i)
        A[i] = read();
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
    return 0;
}