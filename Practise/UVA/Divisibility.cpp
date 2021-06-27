#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int n,k,t;
int arr[10005];
int dp[200][10005];
void init(){
        for(int i=0;i<200;i++){
                for(int j=0;j<10005;j++){
                        dp[i][j]=-1;
                }
        }
}
bool fxn(int sum,int i){
        sum=((sum%k)+k)%k;
        if(i==n){
                if(sum==0){
                        return true;
                }
                else{
                        return false;
                }
        }
        if(dp[sum][i]!=-1){
                return dp[sum][i];
        }
        bool chk=false;
        chk|=fxn(sum+arr[i],i+1);
        if(chk==false)
                 chk|=fxn(sum-arr[i],i+1);
        dp[sum][i]=chk;
        return dp[sum][i];
}
int main(){
        scanf("%d",&t);
        while(t--){
                init();
                scanf("%d%d",&n,&k);
                for(int i=0;i<n;i++){
                       scanf("%d",&arr[i]); 
                }
                if(n==1){
                        if((arr[0]%k+k)%k==0){
                                printf("Divisible\n");        
                        }
                        else{
                                printf("Not divisible\n");
                        }
                }
                else{
                       if(fxn(arr[0],1)==true){
                                printf("Divisible\n");
                       } 
                       else{
                                printf("Not divisible\n");                                
                       }
                }
        } 
	return 0;
}	
