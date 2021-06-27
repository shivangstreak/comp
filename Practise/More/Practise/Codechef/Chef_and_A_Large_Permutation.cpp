#include <bits/stdc++.h>
using namespace std;
bool isSubsetSum(vector<int>&set, int n, int sum){
	bool subset[sum+1][n+1];
	for (int i = 0; i <= n; i++)
	subset[0][i] = true;
	for (int i = 1; i <= sum; i++)
	subset[i][0] = false;
	for (int i = 1; i <= sum; i++){
    	for (int j = 1; j <= n; j++){
    	    subset[i][j] =  subset[i][j-1];
    		if (i >= set[j-1])
    		subset[i][j] =  subset[i][j-1] || subset[i - set[j-1]][j-1];
    	}
	}
	return subset[sum][n];
}
int main() {
	int t;scanf("%d",&t);
	while(t--){
		int n,k,d;scanf("%d %d",&n,&k);
		//map<int,int>m;
		vector<int>v1;
		for(int i=0;i<k;i++){
			scanf("%d",&d);
			//m[d]=1;
			v1.push_back(d);
		}
		sort(v1.begin(),v1.end());
		int v1len=v1.size();
		vector<int>v;
		int o=0;
		for(int j=1;j<=n;j++){
			if(o<v1len && v1[o]==j){
				o++;
			}
			else{
				v.push_back(j);
			}
			/*if(m[j]==0){
				v.push_back(j);
			}*/
		}
		int start=1;
		int vlen=v.size();
		while(isSubsetSum(v,vlen,start)){
			start++;
		}
		if(start%2==0)
			cout<<"Mom"<<endl;
		else{
			cout<<"Chef"<<endl;
		}
	}
	return 0;
} 
