#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int dp[12][105],arr[12][105];
int main(){
        int t,n,m;
        scanf("%d",&t);
        while(t--){
                scanf("%d%d",&m,&n);
                for(int i=0;i<12;i++){
                        for(int j=0;j<105;j++){
                                dp[i][j]=0;
                        }
                }
                for(int i=1;i<=m;i++){
                        for(int j=1;j<=n;j++){
                              scanf("%d",&arr[i][j]);  
                        }
                }
                for(int j=1;j<=n;j++){
                        if(arr[1][j]>=5){
                                dp[1][j]=arr[1][j];
                        }
                }
                for(int i=2;i<=m;i++){
                        for(int j=1;j<=n;j++){
                                int M=0;
                                for(int k=1;k<=j;k++){
                                     if(arr[i][k]>=5 && dp[i-1][j-k]!=0)
                                        M=max(M,dp[i-1][j-k]+arr[i][k]);
                                }
                                dp[i][j]=M;
                        }
                }
		if(dp[m][n] == 0) 
			printf("Peter, you shouldn't have played billiard that much.\n");
		else 
			printf("Maximal possible average mark - %.lf.\n", (double)dp[m][n]/m + 1e-9);
        }
	return 0;
}
/*
#include<stdio.h>
main() {
	int T, n, m;
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d", &n, &m);
		int L[11][101] = {}, a, b, c;
		for(a = 1; a <= n; a++) 
			for(b = 1; b <= m; b++) 
				scanf("%d", &L[a][b]);
		int A[11][101] = {};
		for(a = 1; a <= m; a++)	
			if(L[1][a] >=5) 
				A[1][a] = L[1][a];
		for(a = 2; a <= n; a++) {
			for(b = 1; b <= m; b++) { 
				int max = 0; 
				for(c = 1; c <= b; c++) 
					if(L[a][c] >= 5 && A[a-1][b-c]) { 
						if(max < L[a][c] + A[a-1][b-c]) {
							max = L[a][c] + A[a-1][b-c]; 
						} 
					}
				A[a][b] = max;
			} 
		} 
		if(A[n][m] == 0) 
			puts("Peter, you shouldn't have played billiard that much.");
		else 
			printf("Maximal possible average mark - %.2lf.\n", (double)A[n][m]/n + 1e-9);
	}
	return 0;
}
*/	
