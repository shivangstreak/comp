#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=3*1e5+5;
int arr[N];
vector<pair<int,int>>v;
int main(){
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&arr[i]);
	if(n==1){
		printf("-1\n");
		return 0;
	}
	int i=1;
	int c=0;
	int flag=0;
	while(i<=n){
		map<int,int>m;
		int l=i;
		while(i<=n){
			if(m[arr[i]]==1){
				flag=1;
				break;
			}
			m[arr[i]]=1;
			i++;
		}
		if(i<=n){
			v.pb({l,i});
		}
		i++;
	}
	if(flag==0){
		printf("-1\n");
		return 0;
	}
	int size=v.size();
	printf("%d\n",size);
	for(int j=0;j<size-1;j++){
		printf("%d %d\n",v[j].first,v[j].second);	
	}
	if(v[size-1].second!=n){
		v[size-1].second=n;
	}
	printf("%d %d\n",v[size-1].first,v[size-1].second);
	return 0;
}
