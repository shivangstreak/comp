#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > vii;

#define MAXN 1000 + 5

int N, n[MAXN], l[MAXN], p[MAXN], o, nL;
bool adj[MAXN][MAXN], crit[MAXN][MAXN];

void dfs(int x){
     n[x] = l[x] = o++;
     for(int i = 0; i < N; i++){
          if(adj[x][i]){
               if(!n[i]){
                    p[i] = x;
                    dfs(i);
                    if(l[i] > n[x]){
                         crit[x][i] = crit[i][x] = 1;
                         nL++;
                    }
                    l[x] = min(l[x], l[i]);
               }
               else if(p[x] != i) l[x] = min(l[x], n[i]);
          }
     }
}

int main(){
     int a, t, b, f = 0;
     while(scanf("%d", &N) == 1){
          if(!N){
               printf("0 critical links\n\n");
               continue;
          }
          memset(n, 0, sizeof(n));
          memset(p, -1, sizeof(p));
          memset(adj, 0, sizeof(adj));
          memset(crit, 0, sizeof(crit));
          o = 1;
          nL = 0;
          for(int i = 0; i < N; i++){
               scanf("%d (%d)", &a, &t);
               for(int i = 0; i < t; i++){
                    scanf("%d", &b);
                    adj[a][b] = adj[b][a] = 1;
               }
          }
          for(int i = 0; i < N; i++) if(!n[i]) dfs(i);
          printf("%d critical links\n", nL);
          for(int i = 0; i < N; i++){
               for(int j = i + 1; j < N; j++){
                    if(crit[i][j]) printf("%d - %d\n", i, j);
               }
          }
          printf("\n");
     }
}
