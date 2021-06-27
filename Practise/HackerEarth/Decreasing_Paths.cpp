#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int arr[1005][1005];
ll dp[1005][1005];
int n;
const int MOD=1e9+7;
bool chk(int i,int j,int k){
        if(i>=0 && i<n && j>=0 && j<n && arr[i][j]<k){
                return true;
        }
        return false;
}
int main(){
        scanf("%d",&n);
        for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                        scanf("%d",&arr[i][j]);
                        dp[i][j]=1;
                }
        }
        for(int k=1;k<=100;k++){
                for(int i=0;i<n;i++){
                        for(int j=0;j<n;j++){
                                if(arr[i][j]==k){
                                        ll ans=dp[i][j];
                                        if(chk(i-1,j,k)==true){
                                                ans+=dp[i-1][j];
                                                ans%=MOD;
                                        }
                                        if(chk(i+1,j,k)==true){
                                                ans+=dp[i+1][j];
                                                ans%=MOD;
                                        }
                                        if(chk(i,j-1,k)==true){
                                                ans+=dp[i][j-1];
                                                ans%=MOD;
                                        }
                                        if(chk(i,j+1,k)==true){
                                                ans+=dp[i][j+1];
                                                ans%=MOD;
                                        }
                                        dp[i][j]=ans;                                                                          
                                }
                        }
                }
        }
        ll res=0;
        for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                        res+=dp[i][j];
                        res%=MOD;
                }
        }
        printf("%lld\n",res);
	return 0;
}	


