#include<bits/stdc++.h>
using namespace std;
const int N=2e3+5;
int a[N],b[N];
int lena,lenb;
int dp[N][N];
void lcs(){
	for(int i=0;i<=lena;i++){
		for(int j=0;j<=lenb;j++){
			if(i==0 || j==0){
				dp[i][j]=0;
			}
			else{
				if(a[i-1]==b[j-1]){
					dp[i][j]=1+dp[i-1][j-1];
				}
				else{
					dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
				}
			}
		}
	}
}
int main(){
	int d,e;scanf("%d",&d);
	while(d--){
		lena=0;
		scanf("%d",&e);
		while(e!=0){
			a[lena++]=e;
			scanf("%d",&e);
		}
		int mx=-1;
		while(true){
			scanf("%d",&e);
			if(e==0){
				break;
			}
			lenb=0;
			while(e!=0){
				b[lenb++]=e;
				scanf("%d",&e);
			}
			lcs();
			if(dp[lena][lenb]>mx){
				mx=dp[lena][lenb];
			}
		}
		printf("%d\n",mx);
	}
	return 0;
}
