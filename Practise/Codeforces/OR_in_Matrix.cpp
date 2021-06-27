#include<bits/stdc++.h>
using namespace std;
#define ll long long
int a[150][150],b[150][150];
int m,n;
int f(int i,int j){
	int g=0;
	for(int k=0;k<m;k++){
		g|=a[k][j];
	}
	for(int k=0;k<n;k++){
		g|=a[i][k];
	}	
	return g;
}
int main(){
	scanf("%d%d",&m,&n);
		
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				a[i][j]=1;
			}		
		}	
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++){
			scanf("%d",&b[i][j]);
			if(b[i][j]==0){
				for(int k=0;k<m;k++){
					a[k][j]=0;
				}
				for(int k=0;k<n;k++){
					a[i][k]=0;
				}				
			}		
		}
	int flag=1;
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			if(b[i][j]!=f(i,j)){
				flag=0;
				break;
			}
		}
		if(flag==0){
			break;
		}
	}	
	if(flag==1){
		printf("YES\n");
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				printf("%d ",a[i][j]);
			}		
			printf("\n");
		}	
	}
	else{
		printf("NO\n");
	}
	return 0;
}
