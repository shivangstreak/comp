#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
double X[3005],Y[3005],F[3005];
double dp[3005];
int main(){
        int n;
        cin>>n;
        for(int i=0;i<n;i++){
                cin>>X[i]>>Y[i]>>F[i];
        }
        fill(dp,dp+n,INT_MIN);
        dp[0]=F[0];
        for(int i=1;i<n;i++){
               // cout<<dp[i]<<endl;
                for(int j=0;j<i;j++){
                        dp[i]=max(dp[i],dp[j]-(double)sqrt( ( double ) (X[i]-X[j]) * (X[i]-X[j]) + (Y[i]-Y[j]) * (Y[i]-Y[j]) ) );
                }
                dp[i]+=F[i];
        }
        printf("%.6lf\n",dp[n-1]);
	return 0;
}	
