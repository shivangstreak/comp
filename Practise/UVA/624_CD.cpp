#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int arr[25];
int MAX_SUM;
int n,m;
int res_mask;
void select(int mask,int i,int sum){
	if(sum>n){
		return;
	}
	if(i>m){
		return;
	}
	if(sum>MAX_SUM){
		MAX_SUM=sum;
		res_mask=mask;
	}
	select(mask | 1<<i,i+1,sum+arr[i]);
	select(mask,i+1,sum);
}
int main(){	
	while(scanf("%d %d",&n,&m)==2){
		res_mask=0;
		MAX_SUM=0;
		int mx_sum;
		for(int i=0;i<m;i++){
			scanf("%d",&arr[i]);
		}
		select(0,0,0);
		for(int i=0;i<m;i++){
			if((res_mask>>i)&1){
				printf("%d ",arr[i]);
			}
		}
		printf("sum:%d\n",MAX_SUM);
	}
	return 0;
}
