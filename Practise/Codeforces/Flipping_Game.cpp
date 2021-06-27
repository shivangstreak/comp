#include<bits/stdc++.h>
using namespace std;
int a[200],c[200];
int main(){
	int n;
	int sum=0;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",&a[i]);
		if(a[i]==1){
			c[i]=-1;
			sum++;
		}
		else{
			c[i]=1;
		}
	}
	/*for(int i=0;i<n;i++){
		cout<<c[i]<<" ";
	}
	cout<<endl;*/	
	int max_till_now=c[0];
	int current_max=c[0];
	for(int i=1;i<n;i++){
		current_max=max(c[i],current_max+c[i]);
		max_till_now=max(current_max,max_till_now);
	}
	//cout<<sum<<" "<<max_till_now<<endl;
	cout<<max_till_now+sum<<"\n";
	return 0;
}
