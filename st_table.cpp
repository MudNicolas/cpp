#include <bits/stdc++.h>
#include <iostream>
using namespace std;

const int MAXN = 50005;
int f[__lg(MAXN) + 1][MAXN]; // 第二维的大小根据数据范围决定，不小于log(MAXN)，定义全局变量，在函数中定义大数组会导致segment fault段错误（爆栈）
int Log2[MAXN], A[MAXN];

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

void init(int n)
{
    for (int i = 1; i <= n; ++i)
        f[0][i] = A[i];
    for (int i = 1; i <= __lg(n); ++i)
        for (int j = 1; j + (1 << i) - 1 <= n; ++j)
            f[i][j] = max(f[i - 1][j], f[i - 1][j + (1 << (i - 1))]);
}
int query(int l, int r)
{
    int s = __lg(r - l + 1);
    return max(f[s][l], f[s][r - (1 << s) + 1]);
}

int main()
{
    int n = read(), m = read();
    for (int i = 1; i <= n; i++) {
        A[i] = read();
    }
    init(n);
    for (; m; m--) {
        int l = read(), r = read();
        cout << query(l, r) << endl;
    }
}