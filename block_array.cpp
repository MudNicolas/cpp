#include <bits/stdc++.h>
#include <iostream>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;

inline ll read()
{
    ll ans = 0;
    char c = cin.get();
    while (!isdigit(c))
        c = cin.get();
    while (isdigit(c)) {
        ans = ans * 10 + c - '0';
        c = cin.get();
    }
    return ans;
}

ll st[N], ed[N], belong[N], size[N], A[N], sum[N], mark[N];
ll n, q, sq;

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

    for (int i = 1; i <= sq; ++i)
        size[i] = ed[i] - st[i] + 1; // 获取i块的大小
}

void update(ll x, ll y, ll k)
{
    if (belong[x] == belong[y]) { // 若xy同块
        for (int i = x; i <= y; ++i) {
            A[i] += k; // 暴力修改A[i]
            sum[belong[i]] += k; // 暴力修改i所属的块的sum
        }
        return;
    }

    for (int i = x; i <= ed[belong[x]]; ++i) { // 遍历x到x所属区间结束的端点
        A[i] += k;
        sum[belong[i]] += k;
    }
    for (int i = st[belong[y]]; i <= y; ++i) { // 遍历y所属区间开始的端点到y
        A[i] += k;
        sum[belong[i]] += k;
    }
    for (int i = belong[x] + 1; i < belong[y]; ++i) // 遍历xy间的整块
        mark[i] += k; // 懒标记
}

ll query(ll x, ll y)
{
    ll ans = 0;
    if (belong[x] == belong[y]) {
        for (int i = x; i <= y; ++i)
            ans += A[i] + mark[belong[i]]; // 注意要加上懒标记
        return ans;
    }
    for (int i = x; i <= ed[belong[x]]; ++i) // 遍历x到x所属区间结束的端点
        ans += A[i] + mark[belong[i]];
    for (int i = st[belong[y]]; i <= y; ++i) // 遍历y所属区间开始的端点到y
        ans += A[i] + mark[belong[i]];
    for (int i = belong[x] + 1; i < belong[y]; ++i) // 遍历xy间的整块
        ans += sum[i] + mark[i] * size[i]; // 注意懒标记要乘上块长

    return ans;
}

int main()
{
    n = read();
    q = read();
    init();
    for (int i = 1; i <= n; ++i)
        A[i] = read();
    for (int i = 1; i <= sq; ++i)
        for (int j = st[i]; j <= ed[i]; ++j)
            sum[i] += A[j]; // sum[i]保存第i块之和

    while (q--) {
        ll op = read(), x = read(), y = read(), k;
        if (op == 1)
            k = read(), update(x, y, k);
        else
            cout << query(x, y) << endl;
    }
}