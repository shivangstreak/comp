#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
vector<int> g[15];
bool vis[15];
int disc[15],disc_low[15],parent[15];
int Time;
vector<pair<int,int>>res;
bool Art[15];
void art(int x){
        disc[x]=disc_low[x]=++Time;
        vis[x]=true;
        int len=g[x].size();
        int child=0;
        for(int i=0;i<len;i++){
                if(vis[g[x][i]]==false){
                    parent[g[x][i]]=x;
                    child++;
                    art(g[x][i]);
                    if(parent[x]==-1 && child>1){
                        Art[x]=true;
                    }
                    if(parent[x]!=-1 && disc_low[g[x][i]]>=disc[x]){
                        Art[x]=true;﻿
                    }
                    if(disc_low[g[x][i]]>disc[x]){
                        if(g[x][i]<=x)
                            res.pb({g[x][i],x});
                        else
                            res.pb({x,g[x][i]});    
                    }
                    disc_low[x]=min(disc_low[x],disc_low[g[x][i]]);
                }
                else if(g[x][i]!=parent[x]){
                        disc_low[x]=min(disc_low[x],disc[g[x][i]]);
                }
        }
}
int main(){
        Time=0;
        int n,m,x,y;
        memset(parent,-1,sizeof(parent));
        memset(Art,false,sizeof(Art));
        scanf("%d%d",&n,&m);
        for(int i=0;i<m;i++){
                scanf("%d%d",&x,&y);
                g[x].pb(y);
                g[y].pb(x);
        }
        for(int i=0;i<n;i++){
                if(vis[i]==false){
                        art(i);
                }
        }
        sort(res.begin(),res.end());
        int Cnt=0;
        vector<int>ans;
        for(int i=0;i<n;i++){
                if(Art[i]){
                        Cnt++;
                        ans.pb(i);
                }
        }
        printf("%d\n",Cnt);
        for(int i=0;i<Cnt;i++){
                printf("%d ",ans[i]);
        }
        int len=res.size();
        printf("\n%d\n",len);
        for(int i=0;i<len;i++){
                printf("%d %d\n",res[i].first,res[i].second);
        }
	return 0;
}	


