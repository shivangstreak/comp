#include<bits/stdc++.h>
using namespace std;
bool chk(string a,string b){
	string t=b.substr(0,a.size());
	if(t==a){
		return true;
	}
	else{
		return false;
	}
}
int main(){
	int t;scanf("%d",&t);
	while(t--){
		int n;scanf("%d",&n);
		int a[n];
		for(int i=0;i<n;i++){
			scanf("%d",&a[i]);
		}
		sort(a,a+n);
		vector<string>str;
		for(auto x:a){
			string s="";
			while(x!=0){
				s+=x%10+'0';
				x/=10;
			}
			reverse(s.begin(),s.end());
			str.push_back(s);
		}
		int f=1;
		for(int i=0;i<n-1;i++){
			cout<<str[i]<<" "<<str[i+1]<<"\n";
			if(chk(str[i],str[i+1])){
				printf("NO\n");
				f=0;
				break;
			}
		}
		if(f==1){
			printf("YES\n");
		}
	}
	return 0;
}
