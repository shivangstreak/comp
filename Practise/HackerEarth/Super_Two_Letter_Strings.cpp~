#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int MOD=1e9+7;
const int N=1e4+5;
ll dp[N];
int t,n,p;
void compute(){
	memset(dp,0,sizeof(dp));
	dp[0]=1;
	for(int i=1;i<=n;i++){
		for(int j=i-1;j>=0 && i-j<=p;j--){
			dp[i]+=dp[j];
			dp[i]%=MOD;
		}
	}
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&p);
		compute();
		printf("%lld\n",dp[n]);
	}
	return 0;
}

/*
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e4+5;
int dp[N][12];
const int MOD=1e9+7;
void callDP(){
        for(int i=0;i<12;i++){
                dp[0][i]=0;
        }
        for(int i=1;i<12;i++){
                dp[1][i]=1;
        }
        for(int i=0;i<N;i++){
                dp[i][0]=0;
        }
        for(int i=1;i<N;i++){
                dp[i][1]=1;
        }        
        for(int p=2;p<12;p++){
                for(int i=2;i<N;i++){
                        for(int j=i-1;j>=0;j--){
                                if(i-j<p){
                                        dp[i][p]+=dp[j][p];
                                        dp[i][p]%=MOD;
                                }
                        }
                }
        }
}
int main(){
        int t,n,p;cin>>t;//scanf("%d",&t);
        callDP();
        while(t--){
              // scanf("%d%d",&n,&p);
               cin>>n>>p;
               printf("%d\n",dp[n+1][p+1]);
        }
	return 0;
}	

*/	
