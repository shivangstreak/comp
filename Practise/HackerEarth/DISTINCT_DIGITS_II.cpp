#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e5+5,MOD=1e9+7;
ll BIT[11][N];
ll arr[N];
void Update(int Count,int indx,int val){
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
        faster;
        int n,q;cin>>n;
        for(int i=1;i<=n;i++){
               cin>>arr[i];
               Update(COUNT(arr[i]),i,1ll);
        }
        cin>>q;
        string str;
        while(q--){
                cin>>str;
                int u,l,r;ll v;
                if(str=="ADD"){
                        cin>>u>>v;
                        Update(COUNT(arr[u]),u,-1ll);
                        arr[u]=(arr[u]+v)%MOD;
                        Update(COUNT(arr[u]),u,1ll);                                       
                }
                else if(str=="MUL"){
                        cin>>u>>v;
                        Update(COUNT(arr[u]),u,-1ll);
                        arr[u]=(arr[u]*v)%MOD;
                        Update(COUNT(arr[u]),u,1ll);                          
                }
                else if(str=="REP"){
                        cin>>u>>v;
                        Update(COUNT(arr[u]),u,-1ll);
                        arr[u]=(v)%MOD;
                        Update(COUNT(arr[u]),u,1ll);                          
                }
                else if(str=="MAX"){
                        cin>>l>>r;
                        int ans;
                        ll temp,mx;
                        for(int j=10;j>=0;j--){
                                temp=Query(j,r)-Query(j,l-1);
                                if(temp!=0){
                                        mx=temp;
                                        ans=j;
                                        break;
                                }
                        }
                        cout<<ans<<" "<<mx<<"\n";
                }
                else if(str=="MIN"){
                        cin>>l>>r;
                        int ans,mx,temp;
                        for(int i=0;i<=10;i++){
                                temp=Query(i,r)-Query(i,l-1);
                                if(temp!=0){
                                        mx=temp;
                                        ans=i;
                                        break;
                                }
                        }
                        cout<<ans<<" "<<mx<<"\n";                        
                }
        }
	return 0;
}	


