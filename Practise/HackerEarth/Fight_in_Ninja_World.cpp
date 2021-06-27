#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=2*1e4+5;
vector<int> g[N];
bool vis[N],isThere[N];
int main(){
        int n,t,a,b;scanf("%d",&t);
        int Case=1;
        while(t--){
                for(int i=0;i<N;i++){
                        g[i].clear();
                        vis[i]=false;
                        isThere[i]=false;
                }
                scanf("%d",&n);
                for(int i=0;i<n;i++){
                        scanf("%d%d",&a,&b);
                        g[a].pb(b);
                        g[b].pb(a); 
                        isThere[a]=true;
                        isThere[b]=true;
                }
                ll sum=0;
                ll lv[2];
                lv[0]=lv[1]=0;                
                for(int i=1;i<N;i++){
                        if(isThere[i]==true && vis[i]==false){
                             queue<pair<int,int>>q;
                             q.push({i,0});
                             vis[i]=true;                             
                             lv[0]++;
                             while(q.empty()==false){
                                pair<int,int> top_p=q.front();
                                q.pop();
                                int top=top_p.first;
                                int ch=top_p.second;
                                int len=g[top].size();
                                for(int j=0;j<len;j++){
                                        if(vis[g[top][j]]==false){
                                                lv[(ch+1)%2]++;
                                                vis[g[top][j]]=true;
                                                q.push({g[top][j],(ch+1)%2});
                                        }
                                }
                             }
                             //cout<<lv[0]<<" "<<lv[1]<<endl;
                             sum+=max(lv[0],lv[1]);
                             lv[0]=0;
                             lv[1]=0;   
                        }
                }
                printf("Case %d: %lld\n",Case++,sum);
        }
	return 0;
}	


