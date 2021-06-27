#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;scanf("%d",&n);
    vector<int>v;
    for(int i=0;i<n;i++){
    	int d;scanf("%d",&d);
    	v.push_back(d);
    }	
	 if(n>2){
    	printf("-1\n-1\n");
    	for(int i=2;i<n;i++){
    		priority_queue<int>q;
    		for(int j=0;j<=i;j++){
    			q.push(v[j]);
    		}
    		int pro=1;
    		for(int i=0;i<3;i++){
    			int o=q.top();
    			q.pop();
    			pro*=o;
    		}
    		printf("%d\n",pro);
    	}    	
    }
    else{
    	for(int i=0;i<n;i++){
    		printf("-1\n");
    	}
    }
	return 0;
}
