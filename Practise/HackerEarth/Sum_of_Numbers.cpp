#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int arr[20];
int main(){
	int t,n,s;scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=0;i<n;i++){
			scanf("%d",&arr[i]);
		}
		scanf("%d",&s);
		if(s==0){
			printf("YES\n");
			continue;
		}
		int flag=0;
		for(int mask=1;mask< (1<<n) ;mask++){
			int sum=0;
			for(int j=0;j<n;j++){
				if(1<<j & mask){
					sum+=arr[j];
				}
			}
			if(sum==s){
				printf("YES\n");
				flag=1;
				break;
			}
		}
		if(flag==0){
			printf("NO\n");
		}
	}
	return 0;
}	
