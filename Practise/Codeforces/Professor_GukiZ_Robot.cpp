#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int main(){
	faster;
	ll a,b,c,d;
	cin>>a>>b>>c>>d;
	cout<< (max(abs(a-c),abs(b-d))) <<"\n";
	return 0;
}
