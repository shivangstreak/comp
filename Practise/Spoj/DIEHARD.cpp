#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int dp[3][1005][1005][105];
int fxn(int type,int h,int a,int time){
	if(h<=0 || a<=0)
		return time-1;
	if(dp[type][h][a][time]!=-1)
		return 	dp[type][h][a][time];
	if(type==0){
		dp[type][h][a][time]=max(fxn(1,h-5,a-10,time+1),fxn(2,h-20,a+5,time+1));
	}	
	else if(type==1){
		dp[type][h][a][time]=max(fxn(0,h+3,a+2,time+1),fxn(2,h-20,a+5,time+1));
	}
	else{
		dp[type][h][a][time]=max(fxn(1,h-5,a-10,time+1),fxn(0,h+3,a+2,time+1));	
	}
	return dp[type][h][a][time];
}
int main(){
	int t,h,a;scanf("%d",&t);
	while(t--){
		for(int i=0;i<3;i++)
			for(int j=0;j<1005;j++)
				for(int k=0;k<1005;k++)
					for(int o=0;o<105;o++) dp[i][j][k][o]=-1;
		scanf("%d%d",&h,&a);
		if(h<=0 || a<=0)
			printf("0\n");
		else	
			cout<<max(fxn(0,h,a,0),max(fxn(1,h,a,0),fxn(2,h,a,0)))<<endl;
	}
	return 0;
}

