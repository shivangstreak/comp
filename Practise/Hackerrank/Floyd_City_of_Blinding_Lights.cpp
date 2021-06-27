#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
ll dist[405][405];
int n,a,b,w,q,m;
const ll INF=1e11;
void floyd(){
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(dist[i][j]>dist[i][k]+dist[k][j]){
					dist[i][j]=dist[i][k]+dist[k][j];
				}
			}
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<405;i++){
		for(int j=0;j<405;j++){
			if(i==j){
				dist[i][j]=0;
				continue;
			}
			dist[i][j]=INF;
		}
	}
	while(m--){
		scanf("%d%d%d",&a,&b,&w);
		dist[a][b]=w;
	}
	scanf("%d",&q);
	floyd();
	while(q--){
		scanf("%d%d",&a,&b);
		if(dist[a][b]==INF){
			printf("-1\n");
			continue;
		}
		printf("%lld\n",dist[a][b]);
	}
	return 0;
}
