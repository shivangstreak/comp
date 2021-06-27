#include<bits/stdc++.h> // Find all cycles of degree of 3 sum all degrees and substact 6 as we have to exclude degree caused by other two vertices
using namespace std;
int mn=INT_MAX;
bool g[4005][4005];
int degree[4005];
int main(){
	int a,b,n,m;scanf("%d%d",&n,&m);
	while(m--){
		scanf("%d%d",&a,&b);
		g[a][b]=true;g[b][a]=true;
		degree[a]++;
		degree[b]++;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(j!=i){
				if(g[i][j]){
					for(int k=1;k<=n;k++){
						if(k!=i && k!=j){
							if(g[i][k] && g[j][k])
							mn=min(mn,degree[i]+degree[j]+degree[k]);
						}
					}
				}
			}
		}
	}
	if(mn==INT_MAX)
		cout<<"-1\n";
	else
		cout<<mn-6<<"\n";
	return 0;
}
