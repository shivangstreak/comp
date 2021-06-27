/*
It is possible to do it in O(logr) time.

The maximum possible XOR of any two integers from an interval [l,r] can be determined from l⊕r, assuming l,r to be integers. This value is equal to 2^p−1, where p is the smallest value such that 2^p is larger than l⊕r.


*/
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int maximumXOR(int l, int r) {
    int q = l ^ r, a = 1;
    while(q){
        q /= 2;
        a <<= 1;
    }
    return --a;
}
int main(){
	int l,r;scanf("%d%d",&l,&r);
	printf("%d\n",maximumXOR(l,r));	
	return 0;
}	
