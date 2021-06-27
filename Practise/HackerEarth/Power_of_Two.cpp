#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
ll arr[205];
bool isPowerOfTwo(ll x){
        return (x & !(x&(x-1)) );
}
int main(){
        int n,t;scanf("%d",&t);
        ll total=0;
        for(int i=0;i<=31;i++){
                total+=(1<<i);
        }
        while(t--){
              scanf("%d",&n);
              for(int i=0;i<n;i++){
                 scanf("%lld",&arr[i]);
              }
              if(n==1){
                if(isPowerOfTwo(arr[0])){
                        printf("YES\n");
                }
                else{
                        printf("NO\n");
                }
                continue;
              }
              int flag=0;
              for(int i=0;i<=31;i++){
                        ll ans=total;
                        for(int j=0;j<n;j++){
                                if((arr[j] & (1<<i))){
                                        ans=ans&arr[j];
                                }        
                        }
                        if(isPowerOfTwo(ans)){
                                flag=1;
                                break;
                        }
              }
              if(flag==1){
                printf("YES\n");
              }
              else{
                printf("NO\n");
              }
        }
	return 0;
}	


