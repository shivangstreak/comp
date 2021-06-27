#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int a[N],b[N];
int main(){
	int d,n;scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",&d);
		a[i]=d;
	}
	int i;
	for(i=0;i<n-1;i++){
		if(a[i]>a[i+1]){
			break;
		}
	}
	if(i==n-1){
		printf("0\n");
		return 0;
	}
	int j=0;
	//cout<<"i is :- 	"<<i<<endl;
	for(int k=i+1;k<n;k++){
		b[j++]=a[k];
	}
	for(int k=0;k<=i;k++){
		b[j++]=a[k];
	}
	sort(a,a+n);

	/*cout<<"b is:-\n";
	for(int j=0;j<n;j++){
		cout<<b[j]<<" ";
	}
	cout<<endl;
	cout<<"a is:-\n";
	for(int j=0;j<n;j++){
		cout<<a[j]<<" ";
	}
	cout<<endl;*/
	int flag=0;
	for(int j=0;j<n;j++){
		if(a[j]!=b[j]){
			flag=1;
			break;
		}
	}
	if(flag==1){
		printf("-1\n");
	}
	else{
		printf("%d\n",n-1-i);
	}
	return 0;
}
