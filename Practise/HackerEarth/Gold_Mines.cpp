#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
ll arr[1004][1004];
int main(){
        int r,c,q;
        scanf("%d%d",&r,&c);
        for(int i=1;i<=r;i++){
                for(int j=1;j<=c;j++){
                        scanf("%lld",&arr[i][j]);
                }
        }
        for(int i=1;i<=r;i++){
                for(int j=1;j<=c;j++){
                        if(i>1){
                                arr[i][j]+=arr[i-1][j];
                        }
                        if(j>1){
                                arr[i][j]+=arr[i][j-1];
                        }
                        if(i>1 && j>1){
                                arr[i][j]-=arr[i-1][j-1];
                        }
                }
        }
        scanf("%d",&q);
        int r1,r2,c1,c2;
        while(q--){
                scanf("%d%d%d%d",&r1,&c1,&r2,&c2);
                ll ans=arr[r2][c2];
                if(r1>1){
                      ans-=arr[r1-1][c2];
                }
                if(c1>1){
                      ans-=arr[r2][c1-1];
                }
                if(r1>1 && c1>1){
                      ans+=arr[r1-1][c1-1];
                }
                printf("%lld\n",ans);
        }
	return 0;
}	


