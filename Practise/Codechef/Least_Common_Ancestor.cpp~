    #include<bits/stdc++.h>
    using namespace std;
    #define pb push_back
    #define ll long long int
    #define II pair<int,int>
    #define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
    const int N=2*1e5+5;
    int parent[20][N];
    int dep[N];
    bool vis[N];
    vector<int>g[N];
    int n,q,r,u,v; 
    // this gives kth parent of x
    /*int getParent(int x, int k) {
        for (int i = 0; i <=18; ++i) {
       		 if (k & 1) 
       		 	x=parent[i][x];
        		k >>= 1;
        }
        return x;
    }*/
    int getParent(int x,int k){
    	int j=0;
    	while(k>0){
    		if(k&1){
    			x=parent[j][x];
    		}		
    		k>>=1;
    		j++;
    	}
    	return x;
    }
    int lca(int x,int y){
    	if(dep[x]>dep[y]){
    		x=getParent(x,dep[x]-dep[y]);
    	}
    	else if(dep[x]<dep[y]){
    		y=getParent(y,dep[y]-dep[x]);		
    	}
    	if(x==y)
    		return x;
    	for(int i=18;i>=0;i--){
    		if(parent[i][x]!=parent[i][y]){
    			x=parent[i][x];
    			y=parent[i][y];
    		}
    	}
    	return parent[0][x];
    }
    void build_parent(){
    	for(int i=1;i<=18;i++){
    		for(int j=1;j<=n;j++){
    			if(parent[i-1][j]!=-1){
    				parent[i][j]=parent[i-1][parent[i-1][j]];
    			}
    		}
    	}
    }
    void dfs(int x,int d){
    	vis[x]=true;
    	dep[x]=d+1;
    	int len=g[x].size(),v;
    	for(int i=0;i<len;i++){
    		v=g[x][i];
    		if(vis[v]==false){
    			parent[0][v]=x;
    			dfs(v,d+1);
    		}
    	}
    }
    int main(){
    	scanf("%d",&n);
    	// as ceil(log2(200000))=18 
    	for(int i=0;i<=18;i++){
    		for(int j=0;j<=n;j++){
    			parent[i][j]=-1;
    		}
    	}
    	for(int i=0;i<=n;i++){
    		vis[i]=false;
    	}
    	for(int i=0;i<n-1;i++){
    		scanf("%d%d",&u,&v);
    		g[u].pb(v);
    		g[v].pb(u);
    	}
    	dfs(1,0);
    	build_parent();
    	scanf("%d",&q);
    	while(q--){
    		scanf("%d%d%d",&r,&u,&v);
    		int uv=lca(u,v);
    		int rv=lca(r,v);
    		int ru=lca(r,u);
    		int ruv=lca(uv,r);
    		if(uv!=ruv){ // r is in different subtree from lca(u,v)
    			printf("%d\n",uv);
    			continue;
    		}
    		else{
    			if(rv==uv && ru==uv){ // r doesn't have any ancestor on the path from u->v
    				printf("%d\n",uv);
    			}
    			else if(rv==uv){ // r placed elsewhere on the subtree of uv
    				printf("%d\n",ru);
    			}
    			else if(ru==uv){
    				printf("%d\n",rv);
    			}
    		}
    	}
    	return 0;
    } 
