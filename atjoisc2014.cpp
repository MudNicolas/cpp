#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn = 1e5 + 5;

int val[maxn], type[maxn], cnt[maxn], cnt_force[maxn], belong[maxn], st[maxn], ed[maxn], dis[maxn];
ll ans[maxn];
struct query {
    int l, r, id;
    friend bool operator<(query const& a, query const& b)
    {
        return (belong[a.l] ^ belong[b.l]) ? belong[a.l] < belong[b.l] : a.r < b.r;
    }
} q[maxn];
int n, m, block_size, block_num;

inline ll read()
{
    int res = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        res = (res << 1) + (res << 3) + (c ^ 48), c = getchar();
    return res;
}

int main()
{
    n = read(), m = read();
    block_size = sqrt(n);
    block_num = ceil((double)n / block_size);
    for (int i = 1; i <= block_num; ++i) {
        st[i] = block_size * (i - 1) + 1;
        ed[i] = block_size * i;
        for (int j = st[i]; j <= ed[i]; ++j)
            belong[j] = i;
    }
    ed[block_num] = n;

    for (int i = 1; i <= n; ++i)
        dis[i] = val[i] = read();
    sort(dis + 1, dis + n + 1);
    int tot = unique(dis + 1, dis + n + 1) - dis - 1;
    for (int i = 1; i <= n; ++i)
        type[i] = lower_bound(dis + 1, dis + tot + 1, val[i]) - dis;

    for (int i = 1; i <= m; ++i) {
        q[i].l = read(), q[i].r = read();
        q[i].id = i;
    }
    sort(q + 1, q + m + 1);
    int i = 1;
    for (int k = 0; k <= block_num; ++k) {
        int l = ed[k] + 1, r = ed[k];
        ll now = 0;
        memset(cnt, 0, sizeof(cnt));
        for (; belong[q[i].l] == k; ++i) {
            int ql = q[i].l, qr = q[i].r;
            ll tmp;
            if (belong[ql] == belong[qr]) { // 同块直接暴力
                tmp = 0;
                for (int j = ql; j <= qr; ++j)
                    cnt_force[type[j]] = 0;
                for (int j = ql; j <= qr; ++j) {
                    ++cnt_force[type[j]];
                    tmp = max(tmp, 1ll * cnt_force[type[j]] * val[j]);
                }
                ans[q[i].id] = tmp;
                continue;
            }
            // 不同块
            while (r < qr) {
                ++r;
                ++cnt[type[r]];
                now = max(now, 1ll * cnt[type[r]] * val[r]);
            }
            tmp = now; // 状态记录
            while (l > ql) {
                --l;
                ++cnt[type[l]];
                now = max(now, 1ll * cnt[type[l]] * val[l]);
            }
            ans[q[i].id] = now;
            // 状态回滚
            while (l < ed[k] + 1) {
                --cnt[type[l]];
                l++;
            }
            now = tmp;
        }
    }
    for (int i = 1; i <= m; ++i)
        printf("%lld\n", ans[i]);
    return 0;
}