#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int arr[100005];
int main(){
	int t,n;scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=0;i<n;i++){
			scanf("%d",&arr[i]);
		}
		if(n&1){
			int x=0;
			for(int i=0;i<n;i++){
				if(!(i&1)){
					x^=arr[i];
				}
			}
			printf("%d\n",x);
		}
		else{
			printf("0\n");
		}
	}
	return 0;
}	
