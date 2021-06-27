#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
#define INF 99999999
int n,t;
int dp[10][1005];
int arr[10][1005];
void init(){
        for(int i=0;i<10;i++){
                for(int j=0;j<1005;j++){
                        dp[i][j]=-1;
                }
        }
}
int fxn(int alt,int dist){
        if(dist>n || alt>9 || alt<0){
                return INF;
        }
        if(dist==n){
                if(alt==0){
                        return 0;
                }
                else{
                        return INF;
                }
        }
        if(dp[alt][dist]!=-1){
                return dp[alt][dist];
        }
        dp[alt][dist]=min(60-arr[alt][dist]+fxn(alt+1,dist+1),min(30-arr[alt][dist]+fxn(alt,dist+1),20-arr[alt][dist]+fxn(alt-1,dist+1)));
        return dp[alt][dist];
}
int main(){
        scanf("%d",&t);
        while(t--){
                scanf("%d",&n);
                n/=100;
                init();
                for(int i=9;i>=0;i--){
                        for(int j=0;j<n;j++){
                                scanf("%d",&arr[i][j]);
                        }
                }
                int ans=fxn(0,0);
                printf("%d\n\n",ans);               
        }
	return 0;
}	
