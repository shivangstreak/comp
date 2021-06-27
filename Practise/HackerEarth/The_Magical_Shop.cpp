#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
ll dp[100005];
int main(){
	faster;
	ll a,b;cin>>a>>b;
	//scanf("%d %d\n",&a,&b);
	string str;
	cin>>str;
    ll sum=0;
	dp[0]=a%b;
	int len=str.length();
	for(int i=1;i<len;i++){
		dp[i]=((dp[i-1]%b)*(dp[i-1]%b))%b;
	}
	for(int i=0;i<len;i++){
		if(str[i]=='1'){
			sum=((sum%b)+(dp[i]%b))%b;
		}
	}
	//printf("%d\n",sum);
	cout<<sum<<"\n";
	return 0;
}
