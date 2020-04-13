//https://www.jianshu.com/p/ad0894a2f697
/*
链接：https://www.nowcoder.com/questionTerminal/5e029c555f194ffa8e6c9cbc2adbefc0
来源：牛客网

伞屉国是一个以太阳能为主要发电手段的国家，因此他们国家中有着非常多的太阳能基站，链接着的基站会组合成一个发电集群。但是不幸的是伞屉国不时会遭遇滔天的洪水，当洪水淹没基站时，基站只能停止发电，同时被迫断开与相邻基站的链接。你作为伞屉国的洪水观察员，有着这样的任务：在洪水到来时，计算出发电集群被洪水淹没后被拆分成了多少个集群。

由于远古的宇宙战争的原因，伞屉文明是一个二维世界里的文明，所以你可以这样理解发电基站的位置与他们的链接关系：给你一个一维数组a，长度为n，表示了n个基站的位置高度信息。数组的第i个元素a[i]表示第i个基站的海拔高度是a[i],而下标相邻的基站才相邻并且建立链接，即x号基站与x-1号基站、x+1号基站相邻。特别的，1号基站仅与2号相邻，而n号基站仅与n-1号基站相邻。当一场海拔高度为y的洪水到来时，海拔高度小于等于y的基站都会被认为需要停止发电，同时断开与相邻基站的链接。


输入描述:
每个输入数据包含一个测试点。

第一行为一个正整数n，表示发电基站的个数 (0 < n <= 200000)

接下来一行有n个空格隔开的数字，表示n个基站的海拔高度，第i个数字a[i]即为第i个基站的海拔高度，对于任意的i(1<=i<=n),有(0 <= a[i] < 2^31-1)

接下来一行有一个正整数q(0 < q <= 200000)，表示接下来有q场洪水

接下来一行有q个整数，第j个整数y[j]表示第j场洪水的海拔为y[j],对于任意的j(1<=j<=n),有(-2^31 < y[j] < 2^31-1)


输出描述:
输出q行，每行一个整数，第j行的整数ans表示在第j场洪水中，发电基站会被分割成ans个集群。标准答案保证最后一个整数后也有换行。
示例1
输入
10
6 12 20 14 15 15 7 19 18 13 
6
15 23 19 1 17 24
输出
2
0
1
1
2
0
*/
#include <iostream>
#include <algorithm>

using namespace std;

struct nums
{
    int idx;
    int h;

    bool operator < (nums other)  // 重载<操作符
    {
        return h < other.h;
    }
};

const int maxn = 200006;
nums a[maxn], b[maxn];    // 发电基站与洪水海拔
int ans[maxn];            // 记录结果：每次洪水分割的集群数
int sunk[maxn];           // 记录基站沉没与否(全局变量初始化为0)
int n, m;                 // 发电基站数目和洪水数目

int main()
{
    scanf("%d", &n);

    // 读入发电基站的海拔信息，数组a从1开始存储信息
    for (int i = 1; i <= n; i++)
    {
        a[i].idx = i;
        scanf("%d", &a[i].h);
    }

    // 对a排序（自动调用重载的<操作符）
    sort(a + 1, a + n + 1);
    scanf("%d", &m);

    // 读入m次洪水的海拔高度
    for (int i = 1; i <= m; i++)
    {
        b[i].idx = i;
        scanf("%d", &b[i].h);
    }

    // 对b也排序
    sort(b + 1, b + m + 1);

    int last = 1, ret = 1;           // 基站信息的遍历变量，及集群数目
    sunk[0] = sunk[n + 1] = 1;       // 假设0和n+1号基站淹没(实际没有这俩)

    for (int i = 1; i <= m; i++)     // 遍历排序后的m次洪水，计算每次洪水分割的集群数
    {
        // 只需研究每个被淹没的基站就可以得出答案
        while (last <= n && a[last].h <= b[i].h)
        {
            int idx = a[last].idx;   // 记录基站下标
            sunk[idx] = 1;           // 记录idx号基站被淹没

            int adj = sunk[idx - 1] + sunk[idx + 1];
            if (adj == 0) ret++;     // 两侧基站均没有被淹没(0+0)
            else if (adj == 2) ret--;// 两侧基站均被淹没(1+1)

            last++;
        }

        ans[b[i].idx] = ret;         // 记录洪水对应的分割集群数
    }

    for (int i = 1; i <= m; i++)     // 输出m次洪水分割的集群数
        printf("%d\n", ans[i]);

    return 0;
}
