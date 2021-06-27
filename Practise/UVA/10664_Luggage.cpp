#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
vector<int>v;
char str[5000];
void cal(string s){
	int len=s.size();
	int d=0;
	for(int i=0;i<len;i++){
		d=d*10+(s[i]-'0');
	}
	v.pb(d);
}
int dp[25][250];
void f(int n,int sum){
	for(int s=0;s<=sum;s++)
		dp[0][s]=0;
	for(int i=1;i<=n;i++){
		for(int s=0;s<=sum;s++){
			if(v[i]>s){
				dp[i][s]=dp[i-1][s];
			}
			else{
				dp[i][s]=max(dp[i-1][s],dp[i-1][s-v[i]]+v[i]);
			}
		}
	}
	if(dp[n][sum]==sum){
		printf("YES\n");
	}	
	else{
		printf("NO\n");
	}
}
int main(){
	int k,m,n,sum,len;scanf("%d\n",&m);
	while(m--){
		v.clear();
		sum=0;
		scanf("%[^\n]%*c",str);
		len=strlen(str);
		string temp="";
		v.pb(0);
		for(int i=0;i<len;i++){
			if(str[i]==' '){
				cal(temp);
				temp="";
			}
			else{
				temp+=str[i];
			}
		}
		cal(temp);
		int size=v.size();
		for(int i=0;i<size;i++)
			sum+=v[i];
		if(sum&1){
			printf("NO\n");
			continue;
		}	
		f(size-1,sum/2);
	}
	return 0;
}
