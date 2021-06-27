#include<bits/stdc++.h>
using namespace std;
int P[25][25];
int main(){
	int n,m;scanf("%d%d",&n,&m);
	int x,y;scanf("%d%d",&x,&y);	
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			scanf("%d",&P[i][j]);
		}
	}
	int sum=0;
	for(int i=y;i<m;i++){
		P[x-1][i]+=sum;
		sum=P[x-1][i];
	}
	sum=0;
	for(int i=x;i<n;i++){
		P[i][y-1]+=sum;
		sum=P[i][y-1];
	}
	for(int i=x;i<n;i++){
		for(int j=y;j<m;j++){
			P[i][j]+=min(P[i-1][j],P[i][j-1]);
		}
	}
	/*for(int i=x-1;i<n;i++){
		for(int j=y-1;j<m;j++){
			cout<<P[i][j]<<" ";
		}
	cout<<"\n";
	}*/
	int ans=P[x-1][y-1]-P[n-1][m-1];
	if(ans<0){
		printf("N\n");
	}
	else{
		printf("Y %d\n",ans);
	}
	return 0;
}
