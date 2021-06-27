#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e5+5;
int arr[N];
int main(){
        int n;
        ll ans=0;
        scanf("%d",&n);
        for(int i=0;i<n;i++){
                scanf("%d",&arr[i]);
        }
        for(int i=0;i<=30;i++){
                ll temp=1<<i;
                ll cnt=0;
                for(int j=0;j<n;j++){
                        if(temp&arr[j]){
                                cnt++;
                        }
                }
                if(cnt!=0){
                        cnt=(cnt*(cnt-1))/2;
                        ans+=cnt*temp;
                }
        }
        printf("%lld\n",ans);
	return 0;
}	


