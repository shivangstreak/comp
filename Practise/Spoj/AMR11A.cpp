/*
	Base case is like :
		in last column (column C)we can not go right ,only downward so calculate 
		how much min strength harry need to so.	
		similarly in last row row R we can go only right so just calculate 	
		min strength Harry needs to do so..
* 	Using 2-D Matrix and then started with positon[R][C]. From 
*	there I can go upward and left. In each element of array put the minimum 
*	possible value to get the array[R][C]. In case, if we get the value <= 0 
*	substitute it by 1 because values <=0 are not allowed. Follow this 
*	procedure up to array[1][1] which is my final answer.
*/
#include<bits/stdc++.h>   // Magic Grid Spoj
using namespace std;
int dp[550][550];
int main(){
	int r,c,t;scanf("%d",&t);
	while(t--){		
		scanf("%d%d",&r,&c);
		for(int i=1;i<=r;i++){
			for(int j=1;j<=c;j++){
				scanf("%d",&dp[i][j]);
			}
		}	
		dp[r][c]=1;   // For optimal solution Harry need to have strength of 1 in the end dp[r][c]
		for(int i=r-1;i>=1;i--){
			dp[i][c]=dp[i+1][c]-dp[i][c];	//This is base case for Last column as harry can only go downward
			if(dp[i][c]<=0){
				dp[i][c]=1;
			}
		}
		for(int j=c-1;j>=1;j--){
			dp[r][j]=dp[r][j+1]-dp[r][j];  //This is base case for Last row as harry can only go right
			if(dp[r][j]<=0){
				dp[r][j]=1;
			}
		}
		for(int i=r-1;i>=1;i--){
			for(int j=c-1;j>=1;j--){
				dp[i][j]=min(dp[i+1][j]-dp[i][j],dp[i][j+1]-dp[i][j]);
				if(dp[i][j]<=0){
					dp[i][j]=1;
				}
			}
		}
		/*cout<<"dp matrix is\n";
		for(int i=1;i<=r;i++){
			for(int j=1;j<=c;j++){
				printf("%d ",dp[i][j]);
			}
			printf("\n");
		}
		cout<<"answer is\n";*/
		cout<<dp[1][1]<<"\n";	
	}
	return 0;
}
