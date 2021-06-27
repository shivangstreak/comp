//Author : Ritik AKA Treeman
//DAIICT
#include <bits/stdc++.h>
using namespace std;
#define fast ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define ll  long long
#define all(v) v.begin(),v.end()
#define F first
#define S second
#define pb push_back
#define mp make_pair
#define pi pair<ll,ll>
#define REP(i,n) for(int i=0;i<n;i++)
#define deb(...) [](const auto&...x){ char c='='; cerr<<#__VA_ARGS__<<" "; ((cerr<<exchange(c,',')<<" "<<x),...); cerr<<"\n"; }(__VA_ARGS__);

struct segtree{
	int size;
	vector<int> T;
	void init(int n){
		size = 1;
		while(size < n)size *= 2;
		T.assign(2*size,0);
	}
	void build(int x, int lx, int rx, vector<int> &b){
		if(rx - lx == 1){
			if(lx < (int)b.size())
				T[x] = b[lx];
			return;
		}
		int m = (lx + rx)/2;
		build(2*x + 1,lx, m, b);
		build(2*x + 2,m, rx, b);
		T[x] = T[2*x + 1] + T[2*x + 2];
	}
	void build(vector<int> &b){
		build(0,0,size,b);
	}
	int get_kth(int x, int lx, int rx, int u){
		if(rx - lx == 1){
			return lx;
		}
		int m = (lx + rx)/2;
		if(u <= T[2*x + 1])
			return get_kth(2*x + 1, lx, m, u);
		else
			return get_kth(2*x + 2, m, rx, u - T[2*x + 1]);
	}
	int get_kth(int u){
		return get_kth(0,0,size,u);
	}
	void update(int x, int lx, int rx, int u, int v){
		if(rx - lx == 1){
			T[x] = v;
			return;
		}
		int m = (lx + rx)/2;
		if(u < m)
			update(2*x + 1, lx, m, u, v);
		else
			update(2*x + 2, m, rx, u, v);
		T[x] = T[2*x + 1] + T[2*x + 2];
	}
	void update(int u,int v){
		update(0,0,size,u,v);
	}
};
void run_case(){
	int n,i,j,k;
	cin >> n;
	vector<int> a(n),b(n,1);

	for(i=0;i<n;i++){
		cin >> a[i];
	}

	segtree st;
	st.init(n);
	st.build(b);

	vector<int> ans(n);
	for(i=0;i<n;i++){
		int ind = st.get_kth(a[i]);
		st.update(ind,0);
		ans[ind] = i+1;
	}

	for(i=0;i<n;i++)
		cout<<ans[i]<<" ";
	cout<<"\n";
}
 
int main(){
	fast;
	int t=1;
	while(t--){
		run_case();
	}
}
