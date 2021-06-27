#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
char str[50009];
int Rank[20][50009];
int SA[50009];
struct entry{
	int first,second;
	int pos;
}L[1005];
bool cmp(const entry &A,const entry &B){
	return (A.first==B.first)? A.second<B.second : A.first<B.first;
}
void suffix_array(int length){
	for(int i=0;i<length;i++){
		Rank[0][i]=str[i]-'A';
	}
    for(int cnt = 1,stp = 1;(cnt>>1) < length ; cnt<<=1,stp++){
        for(int i = 0;i<length ; i++){
            L[i].first = Rank[stp-1][i];
            L[i].second = i+cnt < length ? Rank[stp-1][i+cnt] : -1;
            L[i].pos = i;
        }
        sort(L,L+length,cmp);
        int rnk = 0;
        for(int i = 0 ; i<length ; i++){
            if((i > 0) && (L[i-1].first == L[i].first && L[i].second == L[i-1].second))
                rnk = Rank[stp][L[i-1].pos];
            else
                rnk = i;
            Rank[stp][L[i].pos] = rnk;
        }
    }	
   int  pos = ceil(log(length)/log(2));
    for(int i=0;i<length;i++)
        SA[Rank[pos][i]] = i;
}
ll lcp(ll x ,ll y,ll n){
	if(x==y)
		return n-x;	
	ll res=0;
	for(int step=ceil(log(n)/log(2));step>=0 && x<n && y<n;step--){
		if(Rank[step][x]==Rank[step][y]){
			x+=1<<step;
			y+=1<<step;
			res+=(1<<step);		
		}
	}
	return res;
}
ll lcp_sum(int length){
    ll sum = 0;
    for(int i = 1 ; i < length ; i++)
        sum += (lcp(SA[i-1],SA[i],length));
    return sum;
}
int main(){
	int t;scanf("%d",&t);
	while(t--){
		scanf("%s",str);
		int length=strlen(str);
		suffix_array(length);
		ll lcpSum=lcp_sum(length);
		ll sumSuffix=0;
		for(int i=0;i<length;i++){
			sumSuffix+=SA[i];
		}
		ll length1=length*length;
		printf("%lld\n",length1-sumSuffix-lcpSum);
	}
	return 0;
}
