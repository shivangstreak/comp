#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
const int N=1e5+5;
int a[N],b[N];
int main(){
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		b[i]=a[i];
	}
	int l=-1,r=-1;
	sort(b+1,b+n+1);
	//cout<<"ther\n";
	for(int i=1;i<=n-1;i++){
		if(a[i]>a[i+1]){
			l=i;
			break;
		}
	}
	//cout<<"here\n";
	for(int i=n;i>=2;i--){
		if(a[i]<a[i-1]){
			r=i;
			break;
		}
	}
	//cout<<"where\n";
	int flag=0;
	//cout<<l<<" "<<r<<endl;
	if(l==-1 && r==-1){
		cout<<"yes\n1 1\n";
		return 0;
	}
	reverse(a+l,a+r+1);
	//cout<<"fuck off\n";
	for(int i=1;i<=n;i++){
		if(a[i]!=b[i]){
			flag=1;
			//cout<<"i is "<<i<<endl;
		//	cout<<a[i]<<" "<<b[i]<<endl;
			break;
		}
	}
	if(flag==1){
		printf("no\n");
	}
	else{
		printf("yes\n");
		printf("%d %d\n",l,r);
	}
	return 0;
}
