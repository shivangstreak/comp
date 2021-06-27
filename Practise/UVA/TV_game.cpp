#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int mat[30][4];
int dp[30][35];
char str[15];
void init(){
        for(int i=0;i<30;i++){
                for(int j=0;j<35;j++){
                        dp[i][j]=-1;
                }
        }
}
int rec(int pos,int m){
        if(m==0){
                return mat[pos][2];
        }
        if(dp[pos][m]!=-1){
                return dp[pos][m];
        }
        else{
                return dp[pos][m]=rec(mat[pos][0],m-1)+rec(mat[pos][1],m-1);
        }
}
int main(){
        int n,m;
        while(scanf("%d\n",&n)!=EOF){
                init();
                //getchar();
                for(int i=0;i<n;i++){
                        scanf("%[^\n]%*c",str);
                        mat[str[0]-'A'][0]=str[2]-'A';
                        mat[str[0]-'A'][1]=str[4]-'A';
                        mat[str[0]-'A'][2]=(str[6]=='x')?1:0;
                }
                scanf("%d",&m);
                printf("%d\n",rec(0,m));        
        }        
	return 0;
}	
