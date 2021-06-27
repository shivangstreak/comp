#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int arr[1005][3];
int dp1[2][3];
int main(){
        int t,n;scanf("%d",&t);
        while(t--){
               for(int i=0;i<2;i++)
                for(int j=0;j<3;j++)
                        dp1[i][j]=0;
               scanf("%d",&n);
               for(int i=0;i<n;i++){
                         for(int k=0;k<3;k++){
                                scanf("%d",&arr[i][k]);
                         }      
               }
               dp1[0][0]=arr[0][0];
               dp1[0][1]=arr[0][1];
               dp1[0][2]=arr[0][2];
               
               for(int i=1;i<n;i++){
                        dp1[i%2][0]=arr[i][0]+min(dp1[(i-1)%2][1],dp1[(i-1)%2][2]);
                        dp1[i%2][1]=arr[i][1]+min(dp1[(i-1)%2][0],dp1[(i-1)%2][2]);
                        dp1[i%2][2]=arr[i][2]+min(dp1[(i-1)%2][0],dp1[(i-1)%2][1]);                                                
               }
               printf("%d\n",min(dp1[(n-1)%2][0],min(dp1[(n-1)%2][1],dp1[(n-1)%2][2]))); 
        }
	return 0;
}	
