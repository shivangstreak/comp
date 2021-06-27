#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e6+5;
ll BIT[11][N];
ll arr[N];
void Update(int Count,int indx,ll val){
        while(indx<=N){
                BIT[Count][indx]+=val;
                indx+=(indx & (-indx));
        }
}
ll Query(int Count,int indx){
        ll res=0;
        while(indx>0){
           res+=BIT[Count][indx];
           indx-=(indx & (-indx));
        }
        return res;
}
int COUNT(ll x){
        bool C[10]={false};
        while(x!=0){
                C[x%10]=true;
                x/=10;
        }
        int cnt=0;
        for(int i=0;i<10;i++){
                if(C[i]==true){
                        cnt++;
                }
        }
        return cnt;
}
int main(){
        int q,n;scanf("%d",&n);
        for(int i=1;i<=n;i++){
                scanf("%lld",&arr[i]);
                Update(COUNT(arr[i]),i,1ll);
        }
        scanf("%d",&q);
        while(q--){
                int type;scanf("%d",&type);
                if(type==0){
                        int u;ll v;
                        scanf("%d%lld",&u,&v);
                        Update(COUNT(arr[u]),u,-1ll);
                        arr[u]+=v;
                        Update(COUNT(arr[u]),u,1ll);                        
                }
                else if(type==1){
                        int u;ll v;
                        scanf("%d%lld",&u,&v);
                        Update(COUNT(arr[u]),u,-1ll);
                        arr[u]=v;
                        Update(COUNT(arr[u]),u,1ll);                        
                }
                else if(type==2){
                        int l,r,c;
                        scanf("%d%d%d",&l,&r,&c);
                        printf("%lld\n",Query(c,r)-Query(c,l-1));
                }
        }
	return 0;
}	


