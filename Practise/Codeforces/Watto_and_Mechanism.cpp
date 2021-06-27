#include<bits/stdc++.h>
using namespace std;
#define pb push_back
const int N=1e5*8;
vector<string>v[N];
map<string,int>mymap;
int main(){
	string temp;
	int n,m;scanf("%d%d",&n,&m);
	char str[N];
	while(n--){
		cin>>temp;
		v[temp.length()].pb(temp);
	}
	while(m--){
		cin>>temp;
		if(mymap[temp]==1){
			printf("YES\n");
		}
		else if(mymap[temp]==2){
			printf("NO\n");
		}
		else{
			int flag=1,len=temp.length();
			int lenv=v[len].size();
			for(int kk=0;kk<lenv;kk++){
				int i=0,c=0;
				for(int j=0;j<len;j++){
					if(temp[j]!=v[len][kk][j]){
						c++;
					}
					if(c>1){
						break;
					}
				}
				if(c==1){
					mymap[temp]=1;
					flag=0;
					printf("YES\n");
					break;
				}
			}
			if(flag==1){
				mymap[temp]=2;
				printf("NO\n");
			}
		}
	}
	return 0;
}
