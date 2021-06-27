#include<bits/stdc++.h>
using namespace std;
#define ll long long
int a[100005];
int main(){
	int n;scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	int mx=1;
	int so_far=1,prev=a[0];
	for(int i=1;i<n;i++){
		if(a[i]>=prev){
			so_far++;
			if(mx<so_far){
				mx=so_far;
			}
		}
		else{
			
			so_far=1;
		}
		prev=a[i];
	}
	printf("%d\n",mx);
	return 0;
}
