#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int main(){
        int m,n;cin>>m;
        n=m;
        n--;
        n|=n>>1;
        n|=n>>2;
        n|=n>>4;
        n|=n>>8;
        n|=n>>16;
	      n++;
	cout<<"number greater than or equal to n which is power of two "<<n<<endl;

        n=m;
        n|=n>>1;
        n|=n>>2;
        n|=n>>4;
        n|=n>>8;
        n|=n>>16;

        cout<<"number less than or equal to n which is power of two "<<((n+1)>>1)<<endl;

	return 0;
}

/*
largest power of two smaller than or equal to n
ll reduce(ll n){
	for(int i=63;i>=0;i--){
		if((n & (1ll <<i))!=0){
			return 1ll << i;
		}
	}
	return 0;
}*/
