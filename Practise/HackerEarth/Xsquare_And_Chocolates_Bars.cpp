#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e6+5;
char str[N];
int dp[N];
int main(){
	int t;scanf("%d",&t);
	while(t--){
		scanf("%s",str);
		int len=strlen(str);
		fill(dp,dp+len,0);
		int ans=0;
		for(int i=2;i<len;i++){
			if(!(str[i-2]==str[i] && str[i-1]==str[i])){
				dp[i]=3+((i-3>=0)?dp[i-3]:0);
			}
			ans=max(ans,dp[i]);
		}
		printf("%d\n",len-ans);
	}
	return 0;
}	
