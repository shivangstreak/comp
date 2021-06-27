#include<bits/stdc++.h>
using namespace std;
int main(){
	bool a[101];
	memset(a,true,sizeof(a));
	for(int i=1;i<=101;i++){
		if(a[i]==true)
		for(int j=i*i;j<101;j+=i){
			a[j]=false;
		}
	}
	return 0;
}
