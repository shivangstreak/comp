#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
char str1[1005],str2[1005];
int dp[1005][1005];
int main(){
        while(true){
                scanf("%s",&str1);
                if(str1[0]=='#'){
                        break;
                }
                scanf("%s",&str2);
                int m=strlen(str1),n=strlen(str2);
                for(int i=0;i<=m;i++){
                        for(int j=0;j<=n;j++){
                           if(i==0 || j==0){
                                dp[i][j]=0;
                           }     
                           else if(str1[i-1]==str2[j-1]){
                                dp[i][j]=dp[i-1][j-1]+1;
                           }
                           else{
                                dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
                           }
                        }
                }
                printf("%d\n",(m-dp[m][n])*15+(n-dp[m][n])*30);
        }
	return 0;
}	
