#include<bits/stdc++.h>
using namespace std;
#define ll long long
string str_arr[30000];
ll a[30000];
ll temp[30000];
ll merge(int left,int mid,int right){
	int i=left,j=mid,k=left;
	ll inv_count=0;
	while(i<=mid-1 && j<=right){
		if(a[i]<=a[j]){
			temp[k++]=a[i++];
		}
		else{
			temp[k++]=a[j++];
			inv_count+=mid-i;
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
	int n,t;scanf("%d",&t);
	string str;
	while(t--){
		map<string,ll>m;
		scanf("%d",&n);	
		for(int i=0;i<n;i++){
			cin>>str;
			str_arr[i]=str;	
		}
		int u=1;
		for(int i=0;i<n;i++){
			cin>>str;
			m[str]=u++;
		}
		for(int i=0;i<n;i++){
			a[i]=m[str_arr[i]];
		}	
		cout<<inversion_count(0,n-1)<<"\n";
	}
	return 0;
}
