#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int x[20],y[20];
double dist[20][20];
double dp[1<<16];
int n;
double f(int bitmask){
	if(bitmask==((1<<(2*n))-1)){
		dp[bitmask]=0;
		return dp[bitmask];
	}
	if(dp[bitmask]!=0){
		return dp[bitmask];
	}
	double mn=32767 * 32767;
	for(int i=0;i<2*n;i++){
		if(!(bitmask&(1<<i))){
			for(int j=i+1;j<2*n;j++){
				if(!(bitmask&(1<<j))){
					mn=min(mn,dist[i][j]+f(bitmask|1<<i|1<<j));
				}
			}
		}
	}
	dp[bitmask]=mn;
	return mn;
}
int main(){
	string str;
	int k=1;
	while(true){
		cin>>n;
		//cout<<"n is "<<n<<endl;
		if(n==0)
			break;
		for(int i=0;i<2*n;i++){
			cin>>str>>x[i]>>y[i];
			//cout<<str<<" "<<x[i]<<" "<<y[i]<<endl;
		}
		for(int i=0;i<2*n;i++){
			for(int j=0;j<2*n;j++){
				dist[i][j]=sqrt((double)((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])));
				//cout<<dist[i][j]<<" ";
			}
			//cout<<endl;
		}
		memset(dp,0,sizeof(dp));
		printf("Case %d: %.2lf\n",k++,f(0));
		//cout<<k++<<" "<<ans<<endl;
	}
	return 0;
}
