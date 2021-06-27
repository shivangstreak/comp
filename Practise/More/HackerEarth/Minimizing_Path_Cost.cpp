#include<bits/stdc++.h> // Floyd warshall....
using namespace std;
map<string,int>m;
string str1,str2;
int D[105][105];
const int lim=1e9+500000;
int main(){
	int q,u,v,n,e,d;scanf("%d%d",&n,&e);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j)
				D[i][j]=0;
			else{
				D[i][j]=lim;
			}		
		}
	}
	for(int i=1;i<=n;i++){
		cin>>str1;
		m[str1]=i;	
	}
	while(e--){
		cin>>str1>>str2>>d; 
		u=m[str1];
		v=m[str2];
		D[u][v]=min(d,D[u][v]);
		D[v][u]=min(d,D[v][u]);
	}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++){
				D[i][j]=min(D[i][j],D[i][k]+D[k][j]);
			}
	scanf("%d",&q);
	while(q--){
		cin>>str1>>str2;
		printf("%d\n",D[m[str1]][m[str2]]);		
	}
	return 0;
}
