#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int arr[20];
const ll MOD=1e9+7;
ll modular_pow(ll base,ll exp,ll MOD){
        ll res=1;
        while(exp>0){
                if(exp&1){
                        res=(res * base)%MOD;
                }
                base=(base * base)%MOD;
                exp=exp>>1;
        }
        return res;
}
int main(){
        int n,t;scanf("%d",&t);
        int tt=1;
        while(t--){           
                scanf("%d",&n);
                for(int i=0;i<n;i++){
                        scanf("%d",&arr[i]);
                }
                ll ans=INT_MIN;
                for(int i=1;i<(1<<n);i++){
                        ll add=0;
                        ll mul=1;
                        int cnt=0;
                        for(int j=0;j<n;j++){
                                if( (i>>j) &1 ){  // or you can write if( i& (1<<j) )
                                        cnt++;
                                        mul=(mul*arr[j])%MOD;
                                        add=(add + arr[j])%MOD;               
                                }
                        }
                        if(cnt>=2){
                                ll temp=modular_pow(add,MOD-2,MOD);
                                temp=(temp%MOD * mul%MOD)%MOD;
                                ans=max(ans,temp);
                        }
                }
                cout << "Case #" << (tt++) << ": " << ans << endl;
        }
	return 0;
}	


