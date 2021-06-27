#include<iostream>
#include<stdio.h>
#include<string.h>
#include<map>
#include<vector>
using namespace std;
int n,tot;
 int all;
vector<int> lin[205];
map<string,int> q;
string s,s1;
int dp[201][2];
int flag[201][2];
void dfs(int x)
{
    int ret=0;
    int tmp=0;
    int f1=0;
    int f2=0;
    for(int i=0;i<lin[x].size();i++)
    {
        int v=lin[x][i];
        dfs(v); 
        ret+=max(dp[v][0],dp[v][1]);
 
        if(dp[v][0]==dp[v][1]) f1=1;
        else if(dp[v][0]>dp[v][1]&&flag[v][0]==1) f1=1;   // flag[v][0] is set when dp[v][0] is not usniquly derived
        else if(dp[v][1]>dp[v][0]&&flag[v][1]==1) f1=1;   // flag[v][1] is set when dp[v][1] is not usniquly derived

        tmp+=dp[v][0];
        if(flag[v][0]) f2=1; // f2 is set when dp[v][0] is not uniquly derived i.e when flag[v][0] is set
    }


    dp[x][0]=ret;
    dp[x][1]=tmp+1;
    if(f2) flag[x][1]=1; 
    if(f1) flag[x][0]=1;
}
int main()
{
    while(scanf("%d",&n))
    {
        if(!n) return 0;
        tot = 0 ;
        cin>>s;
        q.clear();
        q[s]=++tot;
        for(int i=1;i<=n;i++)
        {
            lin[i].clear();
        }
        for(int i=1;i<n;i++)
        {
            cin>>s>>s1;
            if(!q[s])
            {
                q [s] = ++ tot;
            }
            if(!q[s1])
            {
                q [s1] = ++ tot;
            }
            lin[q[s1]].push_back(q[s]);
        }
        memset(flag,0,sizeof(flag));
        memset(dp,0,sizeof(dp));
        dfs(1);


        if(dp[1][0]==dp[1][1])
        {
            printf("%d No\n",dp[1][0]);
        }
        else if(dp[1][0]>dp[1][1]&&flag[1][0])
        {
            printf("%d No\n",dp[1][0]);
        }
        else if(dp[1][1]>dp[1][0]&&flag[1][1])
        {
            printf("%d No\n",dp[1][1]);
        }
        else printf("%d Yes\n",max(dp[1][0],dp[1][1]));
    }
}
