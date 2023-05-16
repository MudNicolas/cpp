#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 1e6 + 5, SQN = 1e3 + 5;

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

ll n, q, sq;
ll st[N], ed[N], belong[N], size[N], A[N], sum[SQN], mark[SQN], block_sort[N];

void init()
{
    sq = sqrt(n); // 有sqrt(n)个块
    for (int i = 1; i <= sq; ++i) {
        st[i] = n / sq * (i - 1) + 1; // st[i]表示i号块的第一个元素的下标
        ed[i] = n / sq * i; // ed[i]表示i号块的最后一个元素的下标
    }
    ed[sq] = n; // 将可能会漏掉的小块纳入最后一块中

    for (int i = 1; i <= sq; ++i) // 遍历所有块
        for (int j = st[i]; j <= ed[i]; ++j) // 遍历当前块的范围
            belong[j] = i; // 表示j号元素归属于i块
}

void update(int t) // 更新并重新排序t号块
{
    for (int i = st[t]; i <= ed[t]; ++i)
        block_sort[i] = A[i];
    sort(block_sort + st[t], block_sort + ed[t] + 1);
}

void modify(ll x, ll y, ll k)
{
    if (belong[x] == belong[y]) { // 若xy同块
        for (int i = x; i <= y; ++i) {
            A[i] += k; // 暴力修改A[i]
        }
        update(belong[x]);
        return;
    }

    for (int i = x; i <= ed[belong[x]]; ++i) { // 遍历x到x所属区间结束的端点
        A[i] += k;
    }
    for (int i = st[belong[y]]; i <= y; ++i) { // 遍历y所属区间开始的端点到y
        A[i] += k;
    }
    update(belong[x]), update(belong[y]);
    for (int i = belong[x] + 1; i < belong[y]; ++i) // 遍历xy间的整块
        mark[i] += k; // 懒标记
}

ll query(ll x, ll y, ll k)
{
    ll ans = 0;
    if (belong[x] == belong[y]) {
        ans += 1 + block_sort + y - lower_bound(block_sort + x, block_sort + y + 1, k - mark[belong[x]]);
        return ans;
    }
    for (int i = x; i <= ed[belong[x]]; ++i) // 遍历x到x所属区间结束的端点
        if (A[i] + mark[belong[x]] >= k)
            ans++;
    for (int i = st[belong[y]]; i <= y; ++i) // 遍历y所属区间开始的端点到y
        if (A[i] + mark[belong[y]] >= k)
            ans++;
    for (int i = belong[x] + 1; i < belong[y]; ++i) // 遍历xy间的整块
        ans += 1 + block_sort + ed[i] - lower_bound(block_sort + st[i], block_sort + ed[i] + 1, k - mark[i]);

    return ans;
}

int main()
{
    n = read();
    q = read();
    init();
    for (int i = 1; i <= n; ++i)
        A[i] = read(), block_sort[i] = A[i];

    for (int i = 1; i <= sq; ++i)
        sort(block_sort + st[i], block_sort + ed[i] + 1);

    while (q--) {
        char op;
        cin >> op;
        ll l = read(), r = read(), k = read();
        if (op == 'M')
            modify(l, r, k);
        else
            printf("%d\n", query(l, r, k));
    }
}