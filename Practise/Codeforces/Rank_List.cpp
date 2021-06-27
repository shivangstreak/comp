#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,k;scanf("%d%d",&n,&k);
	vector< pair<int,int> >v;
	for(int i=0;i<n;i++){
		int a,b;scanf("%d%d",&a,&b);
		v.push_back(make_pair(a,b));
	}
	sort(v.begin(),v.end(),[](const pair<int,int>&a,const pair<int,int>&b){
		if(a.first==b.first){
			return a.second<b.second;
		}
		else{
			return a.first>b.first;
		}		
	});
	printf("%d\n",count(v.begin(),v.end(),v[k-1]));
	return 0;
}
