#include<bits/stdc++.h>
using namespace std;
int n, m;
char a[55][55];
int  d[55][55];

int dx[] = {0, 0, 1, -1, 1, -1, 1, -1};
int dy[] = {1, -1, 0, 0, 1, -1, -1, 1};

bool valid (int x, int y) {
  return x >= 0 && y >= 0 && x < n && y < m;
}

int dfs (int x, int y) {
  if(d[x][y] != -1)
    return d[x][y];
  d[x][y] = 0;
  for(int k = 0; k < 8; ++k) {
    int n_x = x + dx[k];
    int n_y = y + dy[k];
    if(valid(n_x, n_y)) {
      if(a[n_x][n_y] == a[x][y] + 1) {
        d[x][y] = max(d[x][y], 1 + dfs(n_x, n_y));
      }
    }
  }
  return d[x][y];
}

int main () {

  int test_id=0;

  while(scanf("%d%d", &n, &m)) {
    if(n == 0 && m == 0)
      break;
    for(int i = 0; i < n; ++i) {
      scanf("%s", a[i]);
    }
    int ans = 0;
    for(int i = 0; i < 55; ++i) {
      for(int j = 0; j < 55; ++j) {
        d[i][j] = -1;
      }
    }
    for(int i = 0; i < n; ++i) {
      for(int j = 0; j < m; ++j) {
        if(a[i][j] == 'A' && d[i][j] == -1) {
          ans = max(ans, dfs(i, j));
        }
      }
    }
    printf("Case %d: %d\n", ++test_id, ans + 1);
  }
  return 0;
}
