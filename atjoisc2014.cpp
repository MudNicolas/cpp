#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
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
    // 分块初始化
    block_size = sqrt(n);
    block_num = floor((double)n / block_size);
    for (int i = 1; i <= block_num; ++i) {
        st[i] = block_size * (i - 1) + 1;
        ed[i] = block_size * i;
    }
    ed[block_num] = n;

    for (int i = 1; i <= block_num; ++i)
        for (int j = st[i]; j <= ed[i]; ++j)
            belong[j] = i;

    // 数据离散化
    for (int i = 1; i <= n; ++i)
        dis[i] = val[i] = read();
    sort(dis + 1, dis + n + 1);
    int tot = unique(dis + 1, dis + n + 1) - dis - 1;
    for (int i = 1; i <= n; ++i)
        type[i] = lower_bound(dis + 1, dis + tot + 1, val[i]) - dis;

    // 查询离线
    for (int i = 1; i <= m; ++i) {
        q[i].l = read(), q[i].r = read();
        q[i].id = i;
    }
    sort(q + 1, q + m + 1);

    // 回滚莫队
    int i = 1;
    for (int k = 0; k <= block_num; ++k) { // 遍历每块
        int l = ed[k] + 1, r = ed[k]; // lr初始化
        ll now = 0; // 每块答案初始化
        memset(cnt, 0, sizeof(cnt)); // 每块统计初始化
        for (; belong[q[i].l] == k; ++i) { // 遍历左端点属于k块的询问，q是根据左端点的块排过序的
            int ql = q[i].l, qr = q[i].r;
            ll tmp;
            if (belong[ql] == belong[qr]) { // 同块直接暴力
                tmp = 0;
                for (int j = ql; j <= qr; ++j)
                    cnt_force[type[j]] = 0; // 暴力统计的数组在范围内初始化
                for (int j = ql; j <= qr; ++j) {
                    ++cnt_force[type[j]]; // 暴力统计
                    tmp = max(tmp, (ll)cnt_force[type[j]] * val[j]); // 转为longlong
                }
                ans[q[i].id] = tmp;
                continue;
            }
            // 不同块
            while (r < qr) { // 向右拓展区间
                ++r;
                ++cnt[type[r]];
                now = max(now, (ll)cnt[type[r]] * val[r]); // 答案更新
            }
            tmp = now; // 状态记录
            while (l > ql) { // 向左拓展区间
                --l;
                ++cnt[type[l]];
                now = max(now, (ll)cnt[type[l]] * val[l]); // 答案更新
            }
            ans[q[i].id] = now;
            // 状态回滚
            while (l < ed[k] + 1) { // 左端点向右回收，直到k块最右侧，准备下一次区间转移
                --cnt[type[l]];
                l++;
            }
            now = tmp; // 答案回滚
        }
    }
    for (int i = 1; i <= m; ++i)
        printf("%lld\n", ans[i]);
    return 0;
}