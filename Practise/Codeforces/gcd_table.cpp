#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=4e5+5;
int a[N];
int n,size;
map<int,int>m;
vector<int>all;
int main(){
	scanf("%d",&n);
	for(int i=0;i<n*n;i++){
		scanf("%d",&a[i]);	
		m[a[i]]++;
	}
	sort(a,a+n*n);
	for(int i=n*n-1;i>=0;i--){
		if(m[a[i]]>0){
			printf("%d ",a[i]);
			all.push_back(a[i]);
			size=all.size();
			for(int k=0;k<size-1;k++){
				m[__gcd(a[i],all[k])]-=2;
			}
			m[a[i]]--;
		}
	}
	printf("\n");
	return 0;
}

