#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int main(){
        int t;scanf("%d",&t);
        ll x,y,z;
        while(t--){
                scanf("%lld%lld%lld",&x,&y,&z);
                if((z>x && z>y) || (z%(__gcd(x,y)))!=0){
                        printf("NO\n");
                }
                else{
                        printf("YES\n");
                }
        }
	return 0;
}	
