#include<bits/stdc++.h>
using namespace std;
#define ll long long
class DSU{
	private:
		vector<ll> parent,size;
	public:
		DSU(int N) {
                parent.assign(N, 0);
                for (int i = 0; i < N; i++)
                        parent[i] = i;
                size.assign(N, 1);
        }
	    ll root(ll i){
		if(parent[i]!=i){
			parent[i]=root(parent[i]);
			}
			return parent[i];
		}
        bool isSameSet(int i, int j) {
                return root(i) == root(j);
        }	
		void Union(ll a,ll b){
			ll x=root(a);
			ll y=root(b);
			if (x==y)
				return;
			if(size[x]>size[y]){
				swap(x,y);
			}
			parent[x]=y;
			size[y]+=size[x];
		}
        int findSize(ll i) {
                return size[root(i)];
        }					
};
int main(){
	int t;scanf("%d",&t);
	while(t--){
		int n;scanf("%d",&n);
		DSU obj(n * 2);
		ll c=1;
		map<string,ll>m;
		char A[25],B[25];
		while(n--){
			scanf("%s %s",A,B);
			string str1=string(A),str2=string(B);
			if(m[str1]==0){
				m[str1]=c;
				c++;
			}
			if(m[str2]==0){
				m[str2]=c;
				c++;
			}
			obj.Union(m[str1],m[str2]);
			cout<<obj.findSize(m[str1])<<"\n";
		}
	}
	return 0;
}
