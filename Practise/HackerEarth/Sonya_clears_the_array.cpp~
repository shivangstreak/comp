#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e6+50;
bool primes[N];
int NextPrime[N],PrevPrime[N];
int dp[505][505];
int arr[505];
void init(){
        for(int i=0;i<505;i++){
                for(int j=0;j<505;j++){
                        dp[i][j]=INT_MAX;
                }
        }
        memset(primes,true,sizeof(primes));        
}
void sieve(){
        primes[0]=false;
        primes[1]=false;
        for(int i=2;i*i<N;i++){
                if(primes[i]==true){
                        for(int j=i*i;j<N;j+=i){
                                primes[j]=false;
                        }
                }
        }
}
int cost(int l,int r){
        if(NextPrime[l]>=NextPrime[r]){
                return NextPrime[l]-l+NextPrime[NextPrime[l]+1]-r;
        }
        else{
                if(NextPrime[r]==2){
                        return (2-l+3-r);
                }
                else{
                        return (PrevPrime[NextPrime[r]-1]-l+NextPrime[r]-r);
                }
        }
}
int solve(int l,int r){
        if(l>r){
                return 0;
        }
        if(dp[l][r]!=INT_MAX){
                return dp[l][r];
        }
        for(int i=l+1;i<=r;i+=2){
                dp[l][r]=min(dp[l][r],cost(arr[l],arr[i])+solve(l+1,i-1)+solve(i+1,r));
        }
        return dp[l][r];
}
int main(){
        int n;scanf("%d",&n);
        if(n==0){
                printf("0\n");
                return 0;
        }
        for(int i=1;i<=n;i++){
                scanf("%d",&arr[i]);
        }
        init();
        sieve();
        for(int i=N-2;i>=1;i--){
                if(primes[i]==true){
                        NextPrime[i]=i;        
                }
                else{
                        NextPrime[i]=NextPrime[i+1];
                }
        }
        for(int i=1;i<N;i++){
                if(primes[i]==true){
                        PrevPrime[i]=i;
                }
                else{
                        PrevPrime[i]=PrevPrime[i-1];
                }
        }
        printf("%d\n",solve(1,n)+n/2);
	return 0;
}	


