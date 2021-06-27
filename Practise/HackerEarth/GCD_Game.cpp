#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
bool dp[1005][1005][2];
bool vis[1005][1005][2];
int GCD[1005][1005];
void CallGCD(){
        for(int i=0;i<1005;i++){
                for(int j=0;j<1005;j++){
                        GCD[i][j]= __gcd(i,j);
                }
        }
}
bool fxn(int A,int B,int turn){
        if(turn==0){
                if(A==1){
                        return false;
                }
        }
        if(turn==1){
                if(B==1){
                        return false;
                }
        }
        if(vis[A][B][turn]==true){
                return dp[A][B][turn];
        }
        bool ans=false;
        vis[A][B][turn]=true;        
        if(turn==0){
               ans|=!(fxn(A,B-1,1));
               if(GCD[A][B]>1){
                        ans|=!(fxn(A,B/(GCD[A][B]),1));
               } 
        }
        else{
                ans|=!(fxn(A-1,B,0));
                if(GCD[A][B]>1){
                        ans|=!(fxn(A/GCD[A][B],B,0));
                }
        }
        dp[A][B][turn]=ans;
        return ans;
}
int main(){
        int t,A,B;scanf("%d",&t);
        CallGCD();
        while(t--){
                for(int i=0;i<1005;i++){
                        for(int j=0;j<1005;j++){
                                for(int k=0;k<2;k++){
                                        dp[i][j][k]=false;
                                        vis[i][j][k]=false;
                                }       
                        }
                }
                scanf("%d%d",&A,&B);
                if(A==1 && B==1){
                        printf("Draw\n");
                }
                else if(A==1){
                        printf("Chandu Don\n");
                }
                else if(B==1){
                        printf("Arjit\n");
                }
                else{
                        if(fxn(A,B,0)){
                                printf("Arjit\n");                                
                        }
                        else{
                                printf("Chandu Don\n");
                        }
                }
        }
	return 0;
}	


