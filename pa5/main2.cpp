#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <set>
#include <stack>
using namespace std;
#define mem(x, y) memset(x, y, sizeof(x))
#define SI(x) scanf("%d", &x)
#define SL(x) scanf("%lld", &x)
#define PI(x) printf("%d", x)
#define PL(x) printf("%lld", x)
#define P_ printf(" ")
const int INF = 0x3f3f3f3f;
const double PI = acos(-1.0);
typedef long long LL;
const int MAXN = 1010;
char s[2010];
int mp[MAXN][MAXN];
int usd[MAXN];
int ans[MAXN];
int vis[MAXN];
int main()
{
  stack<int> S;
  int t;
  while (mem(s, 0), gets(s))
  {
    int mx = 0;
    mem(usd, 0);
    int len = strlen(s), temp = 0;
    for (int i = 0; i < len; i++)
    {
      if (s[i] == '(')
        temp = 1;
      if (isdigit(s[i]))
      {
        if (temp)
        {
          t = 0;
          while (isdigit(s[i]))
            t = t * 10 + s[i] - '0', i++;
          mx = max(mx, t);
          if (!S.empty())
            mp[t][S.top()] = mp[S.top()][t] = 1, usd[S.top()]++, usd[t]++;
          S.push(t);
          temp = 0;
        }
      }
      if (s[i] == ')')
        if (!S.empty())
          S.pop();
    }
    int k = 0;
    mem(vis, 0);
    int num = mx;
    for (int i = 1; i <= mx; i++)
      usd[i]--;
    while (true)
    {
      temp = INF;
      for (int i = 1; i <= mx; i++)
        if (!vis[i])
          if (!usd[i])
            temp = min(i, temp);
      if (temp == INF)
        break;
      num--;
      for (int i = 1; i <= mx; i++)
      {
        if (!vis[i] && mp[temp][i])
        {
          ans[k++] = i;
          break;
        }
      }
      vis[temp] = 1;
      for (int i = 1; i <= mx; i++)
        if (!vis[i] && mp[temp][i])
          mp[temp][i] = mp[i][temp] = 0, usd[i]--;
    }
    for (int i = 0; i < k; i++)
    {
      if (i)
        printf(" ");
      PI(ans[i]);
    }
    puts("");
  }
  return 0;
}
