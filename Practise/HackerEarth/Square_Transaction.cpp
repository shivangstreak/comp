#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int arr[100005];
int main(){
	int t,q,a;scanf("%d",&t);
	for(int i=0;i<t;i++){
		scanf("%d",&arr[i]);
		if(i!=0){
			arr[i]+=arr[i-1];
		}
	}
	scanf("%d",&q);
	while(q--){
		scanf("%d",&a);
		int u=lower_bound(arr,arr+t,a)-arr;
		if(u==t){
			printf("-1\n");
		}
		else{
			printf("%d\n",u+1);
		}
	}
	return 0;
}	
