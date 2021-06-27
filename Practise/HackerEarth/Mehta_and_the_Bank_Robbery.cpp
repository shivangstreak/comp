#include <bits/stdc++.h>
using namespace std;
int N,W;
pair <long long, int> A[2002];
long long primes[] = {2,3,5,7,11,13,17,19,23,29};
long long dp[2][2002][11];
int main()
{
	//reverse(primes, primes+10);
	scanf("%d%d", &N, &W);
    for ( int i = 0; i < N; i++ ) scanf("%lld%d", &A[i].first, &A[i].second);
    sort(A, A+N);
   // reverse(A,A+N);
    long long ans = 0;
    //memset(dp, -1, sizeof(dp));
    for ( int j = 0; j <= W; j++ ) for ( int k = 0; k <= 10; k++ ) dp[0][j][k] = 0;
    for ( int i = 1; i <= N; i++ ) {
    	for ( int j = 0; j <= W; j++ ) {
    		for ( int k = 0; k <= 10; k++ ) {
    			if ( j == 0 ) {
    				dp[i%2][j][k] = 0;
    			}
    		/*	if ( dp[(i-1)%2][j][k] != -1 ) dp[i%2][j][k] = max(dp[i%2][j][k], dp[(i-1)%2][j][k]);*/
    		dp[i%2][j][k]=dp[(i-1)%2][j][k];
    			if ( j-A[i-1].second >= 0 ) {
    				//if ( dp[(i-1)%2][j-A[i-1].second][k] != -1 ) {
    		dp[i%2][j][k] = max(dp[i%2][j][k], dp[(i-1)%2][j-A[i-1].second][k] + A[i-1].first);
    				//}
    				if ( k-1 >= 0 ) {
    					//if ( dp[(i-1)%2][j-A[i-1].second][k-1] != -1 ) 
 dp[i%2][j][k] = max(dp[i%2][j][k], dp[(i-1)%2][j-A[i-1].second][k-1] + A[i-1].first*primes[k-1]);
    				}
    			}
    			//ans = max(ans, dp[i%2][j][k]);
    		}
    	}
    }
    printf("%lld\n", dp[N%2][W][10]);
    return 0;
}

