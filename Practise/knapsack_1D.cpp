#include<bits/stdc++.h>   /// UVa 10130 SuperSale
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int p[1005],w[1005];
int dp[36];
void cal_dp(int n){
	memset(dp,0,sizeof(dp));
	for(int i=0;i<n;i++){
		for(int we=35;we>=0;we--){
			if(w[i]<=we){
				dp[we]=max(dp[we],dp[we-w[i]]+p[i]);
			}
		}
	}
}
int main(){
	int W,n,g,t;scanf("%d",&t);
	ll sum;
	while(t--){
		sum=0;
		scanf("%d",&n);
		for(int i=0;i<n;i++){
			scanf("%d%d",&p[i],&w[i]);
		}
		cal_dp(n);
		scanf("%d",&g);
		for(int i=1;i<=g;i++){
			scanf("%d",&W);
			sum+=dp[W];
		}
		printf("%lld\n",sum);
	}
	return 0;
}


// To find if largest sum <=given number in an array

#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int MAX=5*1e6+5;
int dp[MAX];
int arr[25];
void cal_dp(int n,int m){   // O(nm) time complexity and O(n) space complexity
	for(int i=0;i<m;i++){
		for(int w=n;w>=0;w--){
			if(arr[i]<=w){
				dp[w]=max(dp[w],dp[w-arr[i]]+arr[i]);
			}
		}
	}
}
int main(){  // n is given number m, is number if elements in the array...
	int n,m;
	while(true){
		scanf("%d %d",&n,&m);
		for(int i=0;i<m;i++){
			scanf("%d",&arr[i]);
		}
		memset(dp,0,sizeof(dp));
		cal_dp(n,m);
		cout<<dp[n]<<endl;
	}
	return 0;
}

/*
Given a list of nintegers, A={a1,a2,a3,...an}, and another integer k, representing the expected sum. Select zero or more numbers from A such that the sum of these numbers is as near as possible, but not exceeding, to the expected sum (k).
#include<bits/stdc++.h>
using namespace std;
int dp[2005];
int main(){
	int t;scanf("%d",&t);
	while(t--){
		int n,k;scanf("%d%d",&n,&k);
		memset(dp,0,sizeof(dp));
		vector<int>v;
		for(int i=0;i<n;i++){
			int d;scanf("%d",&d);
			v.push_back(d);
		}
		//sort(v.begin(),v.end());
		for(int i=1;i<=k;i++){
			for(int j=0;j<n;j++){
				if(i>=v[j])
					dp[i]=max(dp[i],v[j]+dp[i-v[j]]);
			}
		}
		cout<<dp[k]<<"\n";
	}
	return 0;
}
*/


/*
 for large Knapsack
int dp[2][10005];
      for(int i=0;i<=x;i++)
          dp[0][i]=0;
          for(int i=1;i<=n;i++)
          {
              for(int j=0;j<=x;j++)
              {

              dp[i%2][j]=dp[(i-1)%2][j];
              if(j>=arr[i])
              dp[i%2][j]=max(dp[i%2][j],(dp[(i-1)%2][j-arr[i]]+arr[i]));
              }
          }


*/


Following is subset sum problem subset[sum][i] tells if sum can be obtain by any subset of first i elements of array

bool isSubsetSum(int set[], int n, int sum)
{
    // The value of subset[i][j] will be true if there is a subset of set[0..j-1]
    //  with sum equal to i
    bool subset[sum+1][n+1];

    // If sum is 0, then answer is true
    for (int i = 0; i <= n; i++)
      subset[0][i] = true;

    // If sum is not 0 and set is empty, then answer is false
    for (int i = 1; i <= sum; i++)
      subset[i][0] = false;

     // Fill the subset table in botton up manner
     for (int i = 1; i <= sum; i++){
       for (int j = 1; j <= n; j++)
       {
         subset[i][j] = subset[i][j-1];
         if (i>= set[j-1])
           subset[i][j] = subset[i][j] || subset[i - set[j-1]][j-1];
       }
     }

    /* // uncomment this code to print table
     for (int i = 0; i <= sum; i++)
     {
       for (int j = 0; j <= n; j++)
          printf ("%4d", subset[i][j]);
       printf("\n");
     } */

     return subset[sum][n];
}




// Subset sum problem in 1D space


bool dp[10005];
int arr[105];
int main(){
 //freopen("input.in", "r", stdin);
 int n,t;
 cin>>t;
 while(t--)
 {
     for(int i=0;i<10001;i++)
        dp[i]=false;
     cin>>n;
     for(int i=0;i<n;i++)
     cin>>arr[i];

 dp[0]=true;
 for(int i=0;i<n;i++){
     for(int j=10000;j>=0;j--)
     {
         if((j-arr[i])>=0)
            dp[j]|=dp[j-arr[i]];
     }
 }
 int
