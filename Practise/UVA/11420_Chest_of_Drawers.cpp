/*
#include<cstdio>
#include<cstring>
using namespace std;
 
typedef long long int L;
L arr[66][66][2];
 
L dp(int n, int s, int x)
{
	if(n == 1)
	{
		if(s == 0 && x == 1)
			return 1;
		if(s == 0 && x == 0)
			return 2;
		if(s == 1 && x == 1)
			return 1;
		return 0;
	}		
	if(n < s)
		return 0;
	if(n == s && x == 0)
		return 0;
	if(arr[n][s][x] != -1)
		return arr[n][s][x];
	if(x)
		arr[n][s][x] =  dp(n-1,s-1,1) + dp(n-1,s,0);
	else
		arr[n][s][x] =  dp(n-1,s,1) + dp(n-1,s,0);
	return arr[n][s][x];	
}
main()
{
	memset(arr, -1, sizeof(arr));
	int n,s;
	while(1)
	{
		scanf("%d %d", &n, &s);
		if(n<0 && s<0)
			break;
		printf("%lld\n", dp(n,s, 1));  
	}
}
*/#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
ll dp[70][70][2];
void init(){
        for(int i=0;i<70;i++){
                for(int j=0;j<70;j++){
                        for(int k=0;k<2;k++){
                                dp[i][j][k]=-1;
                        }
                }
        }
}
ll fxn(int n,int s,int d){
        if(n==1){
                if(s==0 && d==0){
                        return 2;
                }
                if(s==0 && d==1){
                        return 1;
                }
                if(s==1 && d==1){
                        return 1;
                }
                if(s==1 && d==0){
                        return 0;
                }
        }
        if(s>n){
                return 0;
        }
        if(s==n && d==0){
                return 0;
        }
        if(dp[n][s][d]!=-1)
                return dp[n][s][d];
        if(d==1){
                dp[n][s][d]=fxn(n-1,s-1,1)+fxn(n-1,s,0);
        }
        else{
                dp[n][s][d]=fxn(n-1,s,1)+fxn(n-1,s,0);
        }
        return dp[n][s][d];        
}
int main(){
        int n,s;
        init();
        while(true){
                scanf("%d%d",&n,&s);
                
                if(n<0 && s<0){
                        break;
                }
                printf("%lld\n",fxn(n,s,1));
        }
	return 0;
}	
