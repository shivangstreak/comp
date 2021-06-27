#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
bool dp[10005];
int arr[105];
int main(){
        int t;scanf("%d",&t);
        while(t--){
                int m,n;               
                scanf("%d%d",&m,&n);
                fill(dp,dp+m+1,false);
                for(int i=0;i<n;i++){
                        scanf("%d",&arr[i]);
                        dp[arr[i]]=true;        
                }
                sort(arr,arr+n);
                for(int i=1;i<=m;i++){
                        for(int j=0;j<n;j++){
                                if(i-arr[j]>=0 && dp[i-arr[j]]==false){
                                        dp[i]=true;
                                        break;
                                }
                        }
                }
                if(dp[m]==true){
                        printf("Little Deepu\n");
                }
                else{
                        printf("Kate\n");
                }
        }
	return 0;
}	
