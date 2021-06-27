#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int arr[2005][2005];
int dp[2005];
void init(){
        for(int i=0;i<2005;i++){
                dp[i]=0;
                for(int j=0;j<2005;j++){
                        arr[i][j]=0;                        
                }
        }
}
int main(){
        int c,t,h,f,k,d;
        scanf("%d",&c);
        while(c--){
                init();
                scanf("%d%d%d",&t,&h,&f);
                for(int i=0;i<t;i++){
                     scanf("%d",&k);
                     for(int j=0;j<k;j++){
                        scanf("%d",&d);
                        arr[i][d]++;
                     }   
                }
                for(int i=0;i<t;i++){
                        dp[h]=max(dp[h],arr[i][h]);
                }
                for(int i=h-1;i>=0;i--){
                        for(int j=0;j<t;j++){
                                arr[j][i]+=max(arr[j][i+1],(i+f<=h)?dp[i+f]:0);
                                dp[i]=max(dp[i],arr[j][i]);
                        }
                }    
                printf("%d\n",dp[0]);    
        }
        scanf("%d",&c);
	return 0;
}	
