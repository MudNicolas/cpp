#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e6 + 10;

int a[maxn], cnt[maxn], ans[maxn], belong[maxn];
int q_cnt, c_cnt, n, m, block_size, block_num, now;

struct query {
    int l, r, time, id;
    friend bool operator<(const query& a, const query& b)
    {
        // return (belong[a.l] ^ belong[b.l]) ? belong[a.l] < belong[b.l] : ((belong[a.r] ^ belong[b.r]) ? belong[a.r] < belong[b.r] : a.time < b.time);
        if (belong[a.l] != belong[b.l])
            return belong[a.l] < belong[b.l]; // 左端点块升序
        if (belong[a.r] != belong[b.r])
            return belong[a.r] < belong[b.r]; // 右端点块升序
        return a.time < b.time; // 时间戳升序
    }
} q[maxn];

struct modify {
    int pos, color;
} c[maxn];

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

inline void add(int p)
{
    now += !cnt[p]++;
}

inline void del(int p)
{
    now -= !--cnt[p];
}

inline void modify(int p, int time)
{
    if (c[time].pos >= q[p].l && c[time].pos <= q[p].r) { // 修改值在目标区间内
        del(a[c[time].pos]); // 答案删除原值
        add(c[time].color); // 答案添加新值
    }
    swap(a[c[time].pos], c[time].color); // 交换原值和新值，便于回退修改
}

int main()
{
    n = read(), m = read();
    block_size = pow(n, 2.0 / 3.0); // 设定块大小为n^(2/3)
    block_num = ceil((double)n / block_size); // ceil向上取整，此处把末尾零散块自成一整块
    for (int i = 1; i <= block_num; ++i)
        for (int j = (i - 1) * block_size + 1; j <= i * block_size; ++j)
            belong[j] = i;
    for (int i = 1; i <= n; ++i)
        a[i] = read();
    for (int i = 1; i <= m; ++i) {
        char opt;
        cin >> opt;
        if (opt == 'Q') {
            q[++q_cnt].l = read();
            q[q_cnt].r = read();
            q[q_cnt].time = c_cnt; // 当前查询对应的时间戳为序列修改次数
            q[q_cnt].id = q_cnt;
        } else if (opt == 'R') {
            c[++c_cnt].pos = read(); // 一次新的修改
            c[c_cnt].color = read();
        }
    }
    sort(q + 1, q + q_cnt + 1);

    int l = 1, r = 0, time = 0;
    for (int i = 1; i <= q_cnt; ++i) {
        // 区间转移
        while (l < q[i].l)
            del(a[l++]);
        while (l > q[i].l)
            add(a[--l]);
        while (r < q[i].r)
            add(a[++r]);
        while (r > q[i].r)
            del(a[r--]);
        // 时间戳对应的序列状态转移
        while (time < q[i].time) {
            modify(i, ++time);
        }
        while (time > q[i].time) {
            modify(i, time--);
        }
        ans[q[i].id] = now;
    }
    for (int i = 1; i <= q_cnt; ++i)
        printf("%d\n", ans[i]);

    return 0;
}