#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
ll n;
const int MOD=1000000007;
int main(){
        int t;scanf("%d",&t);
        ll k,d;
        while(t--){
                scanf("%lld",&n);
                k=2;
                ll sum=0;
                while(k<=n){
                       d=1;
                       while(d<k){
                            if(d+k<=n){
                                sum=(sum%MOD + (d+k)%MOD)%MOD;
                            }
                            else{
                                break;
                            }
                            d=d*2;
                       }
                       k=k*2;
                }
                printf("%lld\n",sum);  
        }   
	return 0;
}	


