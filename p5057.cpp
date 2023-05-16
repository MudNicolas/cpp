#include <bits/stdc++.h>
#define lowbit(x) (x & (-x))
using namespace std;
int n, m;
const int maxn = 1e5 + 5;
int c[maxn];
void fix(int x)
{
    for (; x; x -= lowbit(x))
        c[x] ^= 1;
}
int ask(int x)
{
    int res = 0;
    for (; x <= n; x += lowbit(x))
        res ^= c[x];
    return res;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int t;
        scanf("%d", &t);
        if (t == 1)
        {
            int l, r;
            scanf("%d%d", &l, &r);
            fix(r), fix(l - 1);
        }
        else if (t == 2)
        {
            int x;
            scanf("%d", &x);
            printf("%d\n", ask(x));
        }
    }
    return 0;
}