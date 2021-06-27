#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e5+5;
struct node{
        int t,c,r;
}arr[N];
bool cmp(const node &A,const node &B){
        if(A.t==B.t){
               if(A.r==B.r){
                  return A.c<B.c;
               }
               return A.r>B.r;
        }
        return A.t<B.t;
}
int main(){
        int n,t,c,r;
        ll d;
        scanf("%d%lld",&n,&d);
        for(int i=0;i<n;i++){
                scanf("%d%d%d",&t,&c,&r);
                arr[i].t=t;
                arr[i].c=c;
                arr[i].r=r;
        }
        sort(arr,arr+n,cmp);
        ll sum=0;
        ll ans=0;
        ll opt_rate=0;
        int available=arr[0].t;
        for(int i=0;i<n;i++){
                ll temp=opt_rate*(arr[i].t-available);
                sum+=temp;
                if(sum>=d){
                        break;
                }
                if(arr[i].r>opt_rate){
                        opt_rate=arr[i].r;
                        ans+=arr[i].c;
                }
                available=arr[i].t;
        }
        printf("%lld\n",ans);
	return 0;
}	


