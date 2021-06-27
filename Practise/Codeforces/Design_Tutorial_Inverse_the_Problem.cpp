#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int MAX=1e9+5;
int arr[2005][2005];
int main(){
	int mn,n,temp;scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			scanf("%d",&arr[i][j]);
		}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if((i==j && arr[i][j]!=0) || (i!=j && arr[i][j]==0) || arr[i][j]!=arr[j][i]){
				printf("NO\n");
				return 0;
			}
		}
	}
	for(int i=1;i<=n;i++){
		mn=MAX;
		for(int j=1;j<=n;j++){
			if(i!=j && mn>arr[i][j]){
				mn=arr[i][j];
				temp=j;
			}
		}
		for(int j=1;j<=n;j++){
			if(i!=j && j!=temp && abs(arr[i][j]-arr[temp][j])!=arr[i][temp]){
					printf("NO\n");
					return 0;
			}
		}
	}
	printf("YES\n");		
	return 0;
}
