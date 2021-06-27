#define pb push_back

using namespace std;

vector<int>adj[1000];

int main() 

{

    int t,n,m,i,x,y,s;

    cin>>t;

    while(t--)

    {

        cin>>n>>m;

        for(i=0;i<m;i++){
            cin>>x>>y;
            adj[x].pb(y);
            adj[y].pb(x);
        }
        cin>>s;
        bool vis[n+1];
        memset(vis,false,sizeof(vis));
        vis[s]=true;
        set<int>l1,l2;
        for(i=1;i<=n;i++)
        {
            if(i!=s)
            l1.insert(i);
        }

        list<int>q;
        q.push_back(s);
        int dist[n+1];
        memset(dist,0,sizeof(dist));
        while(!q.empty()){
            int u=q.front();
            q.pop_front();
            for(i=0;i<adj[u].size();i++)
            {
                if(!vis[adj[u][i]])
                {
                    l1.erase(adj[u][i]);
                    l2.insert(adj[u][i]);
                }
            }
            std::set<int>::iterator it;
            for(it=l1.begin();it!=l1.end();it++)
            {
                vis[*it]=true;
                q.push_back(*it);
                dist[*it]=dist[u]+1;
            }
            l1=l2;
            l2.clear();
        }
        for(i=1;i<=n;i++)
        cout<<dist[i]<<" ";
        cout<<endl;
    }

    return 0;
}
