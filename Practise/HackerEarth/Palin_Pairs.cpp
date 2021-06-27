#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
string arr[100005];
int main(){
        faster;
        int n;
        cin>>n;
        string str,rev;
        map<string,vector<int>>m;
        map<string,bool>g;
        for(int i=0;i<n;i++){
                cin>>str;
                arr[i]=str;
                g[str]=false;
                m[str].pb(i);
        }        
        ll sum=0;
      	for(int i=0;i<n;i++){
      		if(g[arr[i]]==false){
      			rev=arr[i];
      			reverse(rev.begin(),rev.end());
      			sum+=(m[rev].size()) * (m[arr[i]].size());
      			g[arr[i]]=true;
      			g[rev]=true;
      		}
      	}
      	cout<<sum<<endl;
	return 0;
}	


