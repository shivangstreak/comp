#include<bits/stdc++.h>
using namespace std;
#define ll long long
int arr[105];
int B[110][110];
int sum[110][110];
int best(int start,int end){
	if(start==end){
		return 0;
	}
	if(end==start+1){
		return arr[start]*arr[end];
	}
	int res,mn=B[start][end];
	if(mn==-1){
		for(int i=start;i+1<=end;i++){
			res=best(start,i)+best(i+1,end)+sum[start][i]*sum[i+1][end];
			if(mn==-1 || res<mn){
				mn=res;
			}
		}
		B[start][end]=mn;	
	}
	return B[start][end];
}
int main(){
	int n;;
	while(scanf("%d",&n)==1){
		for(int i=0;i<110;i++){
			for(int j=0;j<110;j++){
				B[i][j]=-1;
				sum[i][j]=0;
			}
		}
		for(int i=0;i<n;i++){
			scanf("%d",&arr[i]);
		}
		for(int i=0;i<n;i++){
			for(int j=i;j<n;j++){
				if(i==j){
					sum[i][j]=arr[i];
				}
				else{
					sum[i][j]=sum[i][j-1]+arr[j];
					if(sum[i][j]>=100){
						sum[i][j]=sum[i][j]%100;
					}
				}
			}
		}
		printf("%d\n",best(0,n-1));
	}
	return 0;
}
