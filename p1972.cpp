/*
洛谷p1972 HH的项链
逆序对
*/

#include <algorithm>
#include <cctype>
#include <cstdio>
#define lowbit(x) ((x) & (-x))

const int MAXN = 1e6 + 5;
using namespace std;
typedef long long ll;

ll read()
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

ll tree[MAXN];
inline void update(ll i, ll x)
{
    for (ll pos = i; pos < MAXN; pos += lowbit(pos))
        tree[pos] += x;
}
inline ll query(int n)
{
    ll ans = 0;
    for (ll pos = n; pos; pos -= lowbit(pos))
        ans += tree[pos];
    return ans;
}
inline ll query(ll x, ll y)
{
    return query(y) - query(x - 1);
}

int A[MAXN], have[MAXN], now;
struct query {
    ll l, r, id;
    bool operator<(const query& o) const // 重载<运算符
    {
        return r < o.r;
    }
} Q[MAXN];

int main()
{
    ll n = read();
    for (int i = 1; i <= n; i++) {
        A[i] = read();
        have[A[i]]++;
        if (have[A[i]] == 1)
            update(i, 1);
    }
    ll m = read();
    for (int i = 0; i < m; i++) {
        Q[i].l = read(), Q[i].r = read(), Q[i].id = i;
        printf("%d\n", query(Q[i].l, Q[i].r));
    }

    return 0;
}