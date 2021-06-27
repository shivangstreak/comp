#include<bits/stdc++.h>  // Inversion Count in O(nLogn) time complexity!!!
using namespace std;
#define ll long long
ll temp[200000];
ll a[200000];
ll merge(int left,int mid,int right){
	int i=left;
	int j=mid;
	int k=left;
	ll inv_count=0;
	while(i<=mid-1 && j<=right){
		if(a[i]<=a[j]){
			temp[k++]=a[i++];
		}
		else{
			temp[k++]=a[j++];
			inv_count+=(mid-i);
		}
	}
	while(i<=mid-1){
		temp[k++]=a[i++];
	}
	while(j<=right){
		temp[k++]=a[j++];
	}
	for(int y=left;y<=right;y++){
		a[y]=temp[y];
	}
	return inv_count;
}
ll inversion_count(int left,int right){
	ll inv_count=0,mid;
	if(right>left){
		mid=(left+right)/2;
		inv_count+=inversion_count(left,mid);
		inv_count+=inversion_count(mid+1,right);
		inv_count+=merge(left,mid+1,right);
	}
	return inv_count;
}
int main(){
	int t;scanf("%d",&t);
	while(t--){
		int n;scanf("%d",&n);
		for(int i=0;i<n;i++){
			scanf("%lld",&a[i]);
		}
		cout<<inversion_count(0,n-1)<<"\n";
	}
	return 0;
}
