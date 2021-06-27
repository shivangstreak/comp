#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=3*1e5+5;
ll arr[N];
int flag[N];
int main(){
        int n;scanf("%d",&n);
        for(int i=0;i<n;i++){
                scanf("%d",&arr[i]);
                flag[i]=1;
        }
        ll ans=0;
        ll temp;
        for(int i=30;i>=0;i--){
                temp=1<<i;
                int cnt=0;
                for(int i=0;i<n;i++){
                        if(flag[i]==1 && (temp&arr[i])){
                                cnt++;
                        }
                }
                if(cnt>=2){
                        ans+=temp;
                        for(int i=0;i<n;i++){
                                if(flag[i]==1 && !(temp&arr[i])){
                                        flag[i]=0;
                                }
                        }
                }
        }
        printf("%lld\n",ans);
	return 0;
}	


