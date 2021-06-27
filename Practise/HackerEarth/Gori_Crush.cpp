#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e6+6;
ll BIT[N+5];
ll arr[N+5];
vector<ll>VV;
map<ll,int>M;
int cnt;
struct node{
        int type;
        ll a,b,c,d;
}Q[N+5];
ll query(int indx){
        ll res=0;
        while(indx>0){
                res+=BIT[indx];
                indx-=(indx&(-indx));
        }
        return res;
}
void update(int indx,ll val){
        while(indx<=cnt){
                BIT[indx]+=val;
                indx+=(indx&(-indx));
        }
}
int main(){
        int n,q,type;
        ll a,b,c,d,k;
        VV.clear();
        M.clear();
        scanf("%d%d%lld",&n,&q,&k);
        for(int i=0;i<n;i++){
                scanf("%lld",&arr[i]);
                VV.pb(arr[i]);
        }
        for(int i=0;i<q;i++){
                scanf("%d",&type);
                if(type==0){
                      scanf("%lld%lld",&a,&b);  
                      VV.pb(b);
                      node temp;
                      temp.type=0;
                      temp.a=a;
                      temp.b=b;
                      Q[i]=temp;
                }
                else{
                        scanf("%lld%lld%lld%lld",&a,&b,&c,&d);
                        VV.pb(a);
                        VV.pb(b);VV.pb(c);VV.pb(d);
                        node temp;
                        temp.a=a;
                        temp.b=b;
                        temp.c=c;
                        temp.d=d;
                        temp.type=1;
                        Q[i]=temp;
                }
        }
        sort(VV.begin(),VV.end());
        M[VV[0]]=1;
        cnt=2;
        int SIZE=(int)VV.size();
        for(int i=1;i<SIZE;i++){
                if(VV[i-1]!=VV[i]){
                        M[VV[i]]=cnt;
                        cnt++;
                }
        }
        for(int i=0;i<n;i++){
                update(M[arr[i]],1);
        }
        for(int i=0;i<q;i++){
               // cout<<i<<endl;
                if(Q[i].type==0){
                        int x=Q[i].a;
                        ll y=Q[i].b;
                        update(M[arr[x-1]],-1);
                        update(M[y],1);
                        arr[x-1]=y;
                }
                else{
			ll x, y, res;
			if(Q[i].c > Q[i].b) {
				x = INT_MAX;
				y = INT_MIN;
			} else if(Q[i].a > Q[i].d) {
				x = INT_MAX;
				y = INT_MIN;
			} else {
				x = max(Q[i].a, Q[i].c);
				y = min(Q[i].b, Q[i].d);
			}
			if(y < x) {
				res = 0;
			} else {
				res = query(M[y]) - query(M[x] - 1);
			}
			if(res >= k) {
				printf("Propose\n");
			} else {
				printf("Do not propose\n");
			}
                }
        }
	return 0;
}	


