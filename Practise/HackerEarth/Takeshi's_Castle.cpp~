#include<bits/stdc++.h> //Dynamic programming..
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL);
double p[10005],dp[10005];
int dist[10005];
int n,l,d;
int main(){
	scanf("%d%d%d",&n,&l,&d);
	dp[n+1]=1.0;
	p[0]=1;
	dist[0]=0;
	dist[n+1]=d;
	for(int i=1;i<=n;i++){
		scanf("%lf",&p[i]);
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&dist[i]);
	}
	for(int i=n;i>=0;i--){
		//cout<<"dist is "<<dist[i]<<" p is "<<p[i]<<endl;	
		double ans=-1;
		int flag=1;
		for(int j=i+1;j<=n+1;j++){
			if(dist[j]-dist[i]<=l){
				ans=max(ans,dp[j]*p[i]);
				flag=0;
			}
			else{
				break;
			}
		}
		if(flag==1){
			printf("IMPOSSIBLE\n");
			return 0;
		}
		dp[i]=ans;
	}
	/*for(int i=0;i<=n+1;i++){
		cout<<dp[i]<<" ";
	}
	cout<<endl;*/
	printf("%.10lf\n",dp[0]);	
	return 0;
}
