#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=(1<<14)+5;
ll arr[N];
//ll dp[N][N];
ll getSum(int left,int right){
        return arr[right]-arr[left-1];
}
int binary_Search(int l, int r, ll s) {
    int low, high, mid;
    low = l;
    high = r;
    while( low <= high ) {
        mid = ( low + high ) / 2;
        ll x = getSum(l, mid);
        if( x == s && (mid == l || getSum(l, mid-1) != s )) {
            return mid;
        } else if( x >= s ) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1;
}
/*int binary_Search(int left,int right,ll sum){
        int mid,ans=-1;
        while(left<=right){
                mid=(left+right)/2;
                ll x=getSum(left,mid);
                if(x==sum){
                        ans=mid;
                        right=mid-1;
                }
                else if(x<sum){
                        left=mid+1;
                }
                else{
                        right=mid-1;
                }
        }
        return ans;
}*/
ll solve(int left,int right){
        /*if(dp[left][right]!=-1){
                return dp[left][right];
        }*/
        ll sum=getSum(left,right);
        if(left!=right && sum%2==0){
                int valid_i=binary_Search(left,right,sum/2);
                if(valid_i!=-1){
                        //return dp[left][right]=max(solve(left,valid_i),solve(valid_i+1,right))+1;
                    return max(solve(left,valid_i),solve(valid_i+1,right))+1;
                }
        }
       // return dp[left][right]=0;
        return 0ll;
}
int main(){
        int n,t;scanf("%d",&t);
        while(t--){
                /*for(int i=0;i<N;i++){
                        for(int j=0;j<N;j++){
                                dp[i][j]=-1;
                        }
                }*/
                scanf("%d",&n);
                for(int i=1;i<=n;i++){
                        
                        scanf("%lld",&arr[i]);
                        arr[i]+=arr[i-1];
                }      
                printf("%lld\n",solve(1,n));
        }
	return 0;
}	


