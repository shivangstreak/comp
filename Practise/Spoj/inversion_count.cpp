#include<bits/stdc++.h>  // Inversion Count in O(nLogn) time complexity!!!
using namespace std;
int temp[10];
int merge(int *a,int left,int mid,int right){
	int i=left;
	int j=mid;
	int k=left;
	int inv_count=0;
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
int inversion_count(int *a,int left,int right){
	int inv_count=0,mid;
	if(right>left){
		mid=(left+right)/2;
		inv_count+=inversion_count(a,left,mid);
		inv_count+=inversion_count(a,mid+1,right);
		inv_count+=merge(a,left,mid+1,right);
	}
	return inv_count;
}
int main(){
	//int a[]={ 2, 4, 1, 3, 5};
	//int a[]={1,2,3,4,5};	
	int a[]={4,5,6,3,1,2};
	cout<<inversion_count(a,0,sizeof(a)/sizeof(a[0])-1)<<endl;
	return 0;
}
