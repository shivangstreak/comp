#include<bits/stdc++.h>
using namespace std;
#define ll long long
int a[26];
int main(){
	string str;cin>>str;
	int k;cin>>k;
	int mx=INT_MIN;
	for(char i='a';i<='z';i++){
		int d;scanf("%d",&d);
		a[i-'a']=d;
		mx=max(mx,d);
	}
	ll sum=0;
	int c=1;
	for(auto x:str){
	//	cout<<c<<"  * "<<a[x-'a']<<endl;
		sum+=a[x-'a']*c;
		c++;
	}
	for(int i=0;i<k;i++){
	//	cout<<c<<"  * "<<mx<<endl;
		sum+=c*mx;
		c++;
	}
	cout<<sum<<endl;
	return 0;
}
