#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e6+5;
int main(){
	int sum=0,t;
	scanf("%d",&t);
	char str[N];
	int arr[N];
	while(t--){
		scanf("%s",str);
		int len=strlen(str);
		sum=0;
		for(int i=0;i<len;i++){
			if(str[i]=='R'){
				sum++;
				arr[i]=-1;
			}
			else{
				arr[i]=1;
			}
		}
		int curr=arr[0];
		int mx=arr[0];
		for(int i=1;i<len;i++){
			curr=max(arr[i]+curr,arr[i]);
			mx=max(curr,mx);
		}
		printf("%d\n",sum+mx);
	}
	return 0;
}	
