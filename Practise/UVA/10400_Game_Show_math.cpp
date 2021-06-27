#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int offset=32000;
const int mx=offset*2+10;
bool dp[105][mx];
bool vis[105][mx];
int n,arr[105],tar;
int trace[105][mx];
void init(){
       for(int i=0;i<105;i++){
                for(int j=0;j<mx;j++){
                     dp[i][j]=false;        
                     vis[i][j]=false;                     
                }                                 
       }
}
bool build(int pos,int s){
        if(pos==n){
                return s==tar;
        }
        bool &res=dp[pos][s+offset];
        if(vis[pos][s+offset]==true){
                return res;
        }
        vis[pos][s+offset]=true;
        res=false;
        if(res==false && (s+arr[pos])<=offset){              
                trace[pos][s+offset]=1;
                res|=build(pos+1,s+arr[pos]);
        }
        if(res==false && (s-arr[pos])>=-offset){
                trace[pos][s+offset]=2;
                res|=build(pos+1,s-arr[pos]);
        } 
        if(res==false && s*arr[pos]<=offset && s*arr[pos]>=-offset){
                trace[pos][s+offset]=3;
                res|=build(pos+1,s*arr[pos]);
        }
        if(res==false && arr[pos]!=0 && s%arr[pos]==0){
                trace[pos][s+offset]=4;
                res|=build(pos+1,s/arr[pos]);                
        }        
        return res;
}
void express(int pos,int s){
        if(pos==n){
                return;
        }
        else if(trace[pos][s+offset]==1){
                printf("+%d",arr[pos]);
                express(pos+1,s+arr[pos]);
        }
        else if(trace[pos][s+offset]==2){
                printf("-%d",arr[pos]);
                express(pos+1,s-arr[pos]);
        }
        else if(trace[pos][s+offset]==3){
                printf("*%d",arr[pos]);
                express(pos+1,s*arr[pos]);
        }
        else if(trace[pos][s+offset]==4){
                printf("/%d",arr[pos]);
                express(pos+1,s/arr[pos]);
        }
}
int main(){
        int t;scanf("%d",&t);
        while(t--){
                init();
                scanf("%d",&n);
                for(int i=0;i<n;i++)
                        scanf("%d",&arr[i]);
                scanf("%d",&tar);
                bool ans=build(1,arr[0]);   
                if(ans==false){
                        printf("NO EXPRESSION\n");
                }    
                else{
                        printf("%d",arr[0]);
                        express(1,arr[0]);
                        printf("=%d\n",tar);
                }
        }      
	return 0;
}	
