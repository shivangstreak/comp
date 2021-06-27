#include<bits/stdc++.h>
using namespace std;
char S[55][55];
int dp[55][55];
int X[]={0,0,1,-1,1,-1,1,-1};
int Y[]={1,-1,0,0,1,-1,-1,1};
int h,w;
bool cheackBound(int i,int j){
	if(i>=0 && i<h && j>=0 && j<w){
		return true;
	}
	else{
		return false;
	}
}
int dfs(int i,int j){
	if(dp[i][j]!=-1){
		return dp[i][j];
	}
	dp[i][j]=0;
	for(int k=0;k<8;k++){
		if(cheackBound(i+X[k],j+Y[k])){
				if(S[i+X[k]][j+Y[k]]==S[i][j]+1){
					dp[i][j]=max(dp[i][j],dfs(i+X[k],j+Y[k])+1);
				}
		}
	}
	return dp[i][j];	
}
int main(){
	scanf("%d%d",&h,&w);
	int u=1,ans;
	while(h!=0 && w!=0){
		ans=0;
		for(int i=0;i<h;i++){
			cin>>S[i];	
		}			
		    for(int i = 0; i < 55; i++) {
		      for(int j = 0; j < 55; j++) {
			dp[i][j] = -1;
		      }
		    }	
		int flag=0;
		//memset(dp,-1,sizeof(dp));		
		for(int i=0;i<h;i++){
			for(int j=0;j<w;j++){
				if(S[i][j]=='A' && dp[i][j]==-1){
					flag=1;		
					ans=max(ans,dfs(i,j));
				}
			}			
		}
		if(ans==0 && flag==0){
			printf("Case %d: %d\n",u,ans);
		}
		else
			printf("Case %d: %d\n",u,ans+1);
		u++;
		scanf("%d%d",&h,&w);
	}
	return 0;
}
