#include <cstdio>
using namespace std;

const int mod = 1000000007;

int vi[1000005];

int go[75][1000005]; // 将数组稍微开大以避免越界
int sum[75][1000005]; // 小的一维定义在前，增加缓存命中率

int modadd(int a, int b)
{
    if (a + b >= mod)
        return a + b - mod; // 减法代替取模，加快运算
    return a + b;
}

int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", vi + i);
    }

    for (int i = 1; i <= n; ++i) {
        go[0][i] = (i + k) % n + 1; // i点跳2^0=1次到达的点编号
        sum[0][i] = vi[i]; // i点跳1次获得的点权
    }

    for (int i = 1; i <= 60; i++) {
        for (int j = 1; j <= n; j++) {
            go[i][j] = go[i - 1][go[i - 1][j]]; // j点跳2^i次到达的点编号
            sum[i][j] = modadd(sum[i - 1][j], sum[i - 1][go[i - 1][j]]); // j点跳2^i次获得的点权和
        }
    }

    long long m;
    scanf("%lld", &m);

    int ans = 0;
    int now = 1;
    for (int i = 0; m; i++) {
        if (m & (1ll << i)) { // m 的第 i 位是否为 1，1默认为int，左移31位以上会溢出
            ans = modadd(ans, sum[i][now]);
            now = go[i][now];
            m ^= (1ll << i); // 将第 i 位置零
        }
    }

    printf("%d\n", ans);
}
