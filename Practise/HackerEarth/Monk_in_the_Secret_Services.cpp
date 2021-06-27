#include<bits/stdc++.h>
using namespace std;
int D[105][105];
int vis[105];
int main(){
	int t,n,m,x,y,c,s,h,a;scanf("%d",&t);
	while(t--){
		memset(vis,0,sizeof(vis));
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(i==j){
					D[i][j]=0;
				}
				else{
					D[i][j]=20000;
				}
			}
		}
		while(m--){
			scanf("%d%d%d",&x,&y,&c);
			D[x][y]=min(c,D[x][y]);
			D[y][x]=min(c,D[y][x]);
		}	
	/*for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
			cout<<D[i][j]<<" ";
			}
			cout<<endl;
	}
		cout<<endl;*/
		scanf("%d%d%d",&s,&a,&h);
		vis[a]=1;vis[s]=1;vis[h]=1;
		for(int k=1;k<=n;k++){
			for(int i=1;i<=n;i++){
				for(int j=1;j<=n;j++){
						D[i][j]=min(D[i][k]+D[k][j],D[i][j]);
				}
			}
		}
		/*for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
			cout<<D[i][j]<<" ";
			}
			cout<<endl;
		}*/
		int ans=INT_MIN;
		for(int i=1;i<=n;i++){
			if(vis[i]==0){
				//cout<<"processing "<<i<<":-\n";
				//cout<<s<<" "<<a<<" "<<h<<endl;
				//cout<<D[s][i]<<" "<<D[i][s]<<endl;
				//cout<<D[s][i]<<" "<<D[i][a]<<" "<<D[a][i]<<" "<<D[i][h]<<endl;
				ans=max(ans,D[s][i]+D[i][a]+D[a][i]+D[i][h]);
			}		
		}
		printf("%d\n",ans);
	}
	return 0;
}
