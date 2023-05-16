#include <bits/stdc++.h>
using namespace std;

inline int read()
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

const int N = 1e6 + 5;

int cnt[N], A[N], belong[N], st[N], ed[N], ans[N];
int now, n, sq, q, l = 1, r = 0;

struct query // 把询问以结构体方式保存
{
    int l, r, id; // id保存询问编号
} Q[N];

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

inline void add(int p) // 添数，p为下标
{
    if (cnt[A[p]] == 0) // 如果A[p]之前没在区间内出现过
        now++; // 多了一个新数
    cnt[A[p]]++; // A[p]出现次数+1
}

inline void del(int p) // 删数
{
    cnt[A[p]]--; // A[p]出现次数-1
    if (cnt[A[p]] == 0) // 当前区间内没有A[p]了
        now--; // 少了一个数
}

bool cmp(query a, query b) // 块编号为主关键字，右端点为此关键字奇偶排序
{
    return (belong[a.l] ^ belong[b.l]) ? belong[a.l] < belong[b.l] : ((belong[a.l] & 1) ? a.r < b.r : a.r > b.r);
}

int main()
{
    n = read();
    for (int i = 1; i <= n; ++i)
        A[i] = read();
    init();
    q = read();
    for (int i = 0; i < q; ++i)
        Q[i].l = read(), Q[i].r = read(), Q[i].id = i;
    sort(Q, Q + q, cmp); // 对查询进行排序
    for (int i = 0; i < q; ++i) {
        while (l > Q[i].l)
            add(--l);
        while (l < Q[i].l)
            del(l++);
        while (r < Q[i].r)
            add(++r);
        while (r > Q[i].r)
            del(r--);
        ans[Q[i].id] = now;
    }
    for (int i = 0; i < q; ++i)
        printf("%d\n", ans[i]);
}