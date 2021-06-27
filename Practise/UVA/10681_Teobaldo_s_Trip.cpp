#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
vector<int> g[105];
bool dp[205][105];
int n,m,s,e,d;
void init(){
        for(int i=0;i<105;i++){
                g[i].clear();
        }        
        for(int i=0;i<205;i++){
                for(int j=0;j<105;j++){
                        dp[i][j]=false;
                }
        }
}
void rec(int days,int v){
        if(days>d || v>n){
                return;
        }
        if(dp[days][v]){
                return;
        }
        dp[days][v]=true;
        int len=g[v].size();
        for(int i=0;i<len;i++){
                rec(days+1,g[v][i]);
        }
}
int main(){
        while(true){
                scanf("%d%d",&n,&m);
                if(n==0 && m==0){
                        break;
                } 
                init();
                while(m--){
                        scanf("%d%d",&s,&e);
                        g[s].pb(e);
                        g[e].pb(s);
                }
                scanf("%d%d%d",&s,&e,&d);
                rec(0,s);
                if(dp[d][e]){
                        printf("Yes, Teobaldo can travel.\n");
                }
                else{
                        printf("No, Teobaldo can not travel.\n");
                }
        }
	return 0;
}	
