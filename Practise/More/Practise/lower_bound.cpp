#include<bits/stdc++.h> // lower_bound c++ implementation
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int main(){
	int a[]={1,2,2,3,4,5};
	int l=0,hi=5,mid;
	int s=2;
	while(l<=hi){
		mid=l+(hi-l)/2;
		if(s>a[mid]){
			l=mid+1;
		}
		else{
			hi=mid-1;
		}
	}
	cout<<l<<endl;
	cout<<(lower_bound(a,a+6,2)-a)<<endl;
	return 0;
}	
