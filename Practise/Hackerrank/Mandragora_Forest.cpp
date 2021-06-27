#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const  int N=1e5+5;
ll arr[N];
int main(){
        int n,t;scanf("%d",&t);
        while(t--){
                scanf("%d",&n);
                for(int i=0;i<n;i++){
                        scanf("%lld",&arr[i]);
                }
                sort(arr,arr+n);
                for(int i=n-2;i>=0;i--){
                        arr[i]+=arr[i+1];
                }
                ll ans=0; 
                for(int i=0;i<n;i++){
                        ans=max(ans,(i+1)*arr[i]);
                }
                printf("%lld\n",ans);
        }
	return 0;
}	


