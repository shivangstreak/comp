#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int arr[300][300],dp[300][300];
int main(){
        int t,n;scanf("%d",&t);
        while(t--){
                scanf("%d",&n);
                for(int i=0;i<300;i++){
                        for(int j=0;j<300;j++){
                                arr[i][j]=0;
                                dp[i][j]=0;
                        }
                }
                int i=0;
                for(int k=1;k<((n/2)+1);i++,k++){
                        int cnt=0;
                        for(int j=(n/2)-k+1;cnt<k;j+=2,cnt++){
                                scanf("%d",&arr[i][j]);
                        }
                }
                for(int k=(n/2)+1;k>=1;k--,i++){
                        int cnt=0;
                        for(int j=(n/2)-k+1;cnt<k;j+=2,cnt++){
                                scanf("%d",&arr[i][j]);
                        }
                }
                /*for(int i=0;i<n;i++){
                        for(int j=0;j<n;j++){
                                cout<<arr[i][j]<<" ";
                        }
                        cout<<endl;
                }*/         
                for(int j=0;j<n;j++){
                        dp[n-1][j]=arr[n-1][j];
                }
                for(int r=n-2;r>=0;r--){
                        for(int j=0;j<n;j++){
                                if(j==0){
                                        dp[r][j]=arr[r][j]+dp[r+1][j+1];
                                }
                                else if(j==n-1){
                                        dp[r][j]=arr[r][j]+dp[r+1][j-1];
                                }
                                else{
                                        dp[r][j]=arr[r][j]+max(dp[r+1][j-1],dp[r+1][j+1]);
                                }
                        }
                }   
                printf("%d\n",dp[0][n/2]);                    
        }
	return 0;
}	
