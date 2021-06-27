#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e5+5;
ll BITS[26][N];
int n;
void update(int indx,int val,int pos){
	while(indx<=n){
		BITS[pos][indx]+=val;
		indx+=indx&(-indx);
	}
}
ll giveSum(int indx,int pos){
	ll ans=0;
	while(indx>0){
		ans+=BITS[pos][indx];
		indx-=indx&(-indx);
	}
	return ans;
}
int main(){
	string str;
	int q,d,l,r;scanf("%d%d",&n,&q);
	cin>>str;
	string ch;
	for(int i=0;i<n;i++){
		update(i+1,1,str[i]-'a');
	}
	while(q--){
		cin>>d;
		if(d==1){
			cin>>l;
			cin>>ch;
			update(l,-1,str[l-1]-'a');
			update(l,1,ch[0]-'a');
			str[l-1]=ch[0];
		}
		else{
			cin>>l>>r;
			int Count=0;
			ll dummy;
			for(int i=0;i<26;i++){
				dummy=giveSum(r,i)-giveSum(l-1,i);
				if(dummy%2==1){
					Count++;
				}
			}  
			if(Count>1){
				printf("no\n");
			}
			else{
				printf("yes\n");
			}
		}
	}
	return 0;
}
