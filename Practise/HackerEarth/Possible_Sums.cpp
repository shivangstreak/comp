#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e4+5;
bool dp[N];
int arr[105];
int main(){
        int n,t;scanf("%d",&t);
        while(t--){
                scanf("%d",&n);
                for(int i=0;i<N;i++){
                        dp[i]=false;
                }
                dp[0]=true;
                for(int i=0;i<n;i++){
                        scanf("%d",&arr[i]);
                }
                for(int i=0;i<n;i++){
                        for(int j=N;j>=0;j--){
                                if(arr[i]<=j){
                                        dp[j]|=dp[j-arr[i]];
                                }
                        }
                }
                int cnt=0;
                for(int i=0;i<N;i++){
                        if(dp[i]==true){
                                cnt++;
                        }
                }
                printf("%d\n",cnt);
        }
	return 0;
}	


