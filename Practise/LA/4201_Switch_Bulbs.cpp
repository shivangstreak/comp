#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int vis[1<<16];
vector<int>switches;
int convert(char str[]){
        int res=0,len=strlen(str),p=1;
        for(int i=0;i<len;i++){
                res+=(str[len-1-i]-'0')*p;
                p*=2;
        }
        return res;
}
int main(){
        int t,n,m,k,d,s,Q,Case=1;scanf("%d",&t);
        while(t--){
                memset(vis,-1,sizeof(vis));
                scanf("%d%d",&n,&m);
                switches.clear();
                for(int j=0;j<m;j++){
                        scanf("%d",&k);
                        s=0;
                        for(int i=0;i<k;i++){
                                scanf("%d",&d);
                                s=s|1<<d;
                        }
                        switches.pb(s);
                }
                queue<int>q;
                q.push(0);
                vis[0]=0;
                while(q.empty()==false){
                        int top=q.front();
                        q.pop();
                        for(int i=0;i<m;i++){
                                int temp=top^switches[i];
                                if(vis[temp]==-1){
                                        vis[temp]=vis[top]+1;
                                        q.push(temp);
                                }
                        }
                }
                scanf("%d",&Q);
                printf("Case %d:\n",Case++);
                while(Q--){
                        char str[20];
                        scanf("%s",str);                     
                        int temp=convert(str);
                        printf("%d\n",vis[temp]);
                }    
                printf("\n");            
        }
	return 0;
}	
