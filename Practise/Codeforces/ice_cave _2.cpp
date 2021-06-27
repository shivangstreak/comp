#include<bits/stdc++.h>
using namespace std;
const int mx=505;
int flag=1;
char D[mx][mx];
int a,b,R,C,x,y;
void dfs(int i,int j){
	if(D[i][j]=='X'){
        if(i==x&&j==y){cout<<"YES";exit(0);}
     }
     else if(i>=0&&i<R&&j>=0&&j<C){
	  D[i][j]='X';
      dfs(i+1,j);
      dfs(i-1,j);
      dfs(i,j+1);
      dfs(i,j-1);
     }
}
int main(){
	scanf("%d%d",&R,&C);
	for(int i=0;i<R;i++){
		scanf("%s",D[i]);
	}
	scanf("%d%d%d%d",&a,&b,&x,&y);
	a--;b--;x--;y--;
	D[a][b]='.';
	dfs(a,b);
	if(flag==1){
		printf("NO\n");
	}
	return 0;
}
