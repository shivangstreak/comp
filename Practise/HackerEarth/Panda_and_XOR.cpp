#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int MOD=1e9+7,N=1e5+5;
int arr[N];
ll temp[130],freq[130];
ll modular_pow(ll base,ll exp,ll MOD){
        ll res=1;
        while(exp>0){
                if(exp&1){
                        res*=base;
                        res=res%MOD;
                }
                base*=base;
                base%=MOD;
                exp>>=1;
        }
        return res;
}
int main(){
        int n;scanf("%d",&n);
        for(int i=0;i<n;i++){
                scanf("%d",&arr[i]);
        }
        for(int i=0;i<n;i++){
                memset(temp,0,sizeof(temp));
                for(int j=0;j<128;j++){
                        if(freq[j]!=0){
                                temp[j^arr[i]]+=freq[j];
                                temp[j^arr[i]]=(temp[j^arr[i]]%MOD + MOD)%MOD;
                        }
                }
                for(int j=0;j<128;j++){
                        freq[j]+=temp[j];
                        freq[j]=(freq[j]%MOD + MOD)%MOD;
                }
                freq[arr[i]]++;
                freq[arr[i]]=(freq[arr[i]]%MOD + MOD)%MOD;
        }
        ll ans=0;
        ll div=modular_pow(2,MOD-2,MOD);
        for(int i=0;i<128;i++){ 
               ll cal=freq[i];
               cal=cal*(cal-1);
               	/*while(cal<0)
		        cal+=MOD;*/
	        if(cal<0){
	                cal+=MOD;
	        }
	        cal%=MOD;
	        cal=cal*div;
	        if(cal>=MOD){
	                cal=cal%MOD;
	        }
	        ans+=cal;
	        if(ans>=MOD){
	                ans%=MOD;
	        }
        }
        printf("%lld\n",ans);
	return 0;
}	


