#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int deg[10005];
int edgeTo[10005];
bool Leaf[10005];
int main(){
        int n,t,x,y;scanf("%d",&t);
        while(t--){
              scanf("%d",&n);
              memset(deg,0,sizeof(deg));
              memset(Leaf,false,sizeof(Leaf));
              for(int i=0;i<n-1;i++){
                   scanf("%d%d",&x,&y);
                   deg[x]++;
                   deg[y]++;                                           
                   edgeTo[x]=y;
                   edgeTo[y]=x;
              }
              for(int i=1;i<=n;i++){
                  if(deg[i]==1){
                        Leaf[i]=true;
                  }
              }
              for(int i=1;i<=n;i++){
                if(Leaf[i]==true){
                        deg[i]--;
                        deg[edgeTo[i]]--;
                }
              }
              int flag=0;
              for(int i=1;i<=n;i++){
                      if(deg[i]>=3){
                           flag=1;
                           break;
                      }       
              }
              if(flag==1){
                printf("NO\n");
              }
              else{
                printf("YES\n");
              }                
        }
	return 0;
}	


