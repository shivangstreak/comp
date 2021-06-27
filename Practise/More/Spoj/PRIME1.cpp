#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
	int t;scanf("%d",&t);
	while(t--){
		int p,m,n;scanf("%d%d",&m,&n);
		vector<bool>v;
		for(int i=0;i<=n+1;i++){
			v.push_back(true);
		}
		v[0]=false;v[1]=false;
	    int q=sqrt(n);
	    for(int i=2;i<q+1;i++){
	      if(!v[i]) continue;
	      int k=!(m/i)?2:(m/i)+1;
	      p=i*k;
	      for(int j=k;p<n+1;j++,p=i*j)
			v[p]=false;
	    }
		for(int i=m;i<=n;i++){
				if(v[i]==true){
					printf("%d\n",i);
				}
		}
		printf("\n");
	}
	return 0;
}
