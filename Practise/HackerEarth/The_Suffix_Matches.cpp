#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=200005;
char str[N];
int q,d,len;
int Rank[20][N];
int SA[N];
struct Tuple
{
    int pos;
    int firstHalf,secondHalf;
}t[N+5];
bool compare(const Tuple &a , const Tuple &b)
{
    return a.firstHalf == b.firstHalf ?a.secondHalf < b.secondHalf :a.firstHalf < b.firstHalf;
}
void suffix_array(int length )
{
    int pos = 0;
    for(int i=0;i<length;i++)
        Rank[0][i] = str[i] - 'A';
    for(int cnt = 1,stp = 1;(cnt>>1) < length ; cnt<<=1,stp++)
    {
        for(int i = 0;i<length ; i++)
        {
            t[i].firstHalf = Rank[stp-1][i];
            t[i].secondHalf = i+cnt < length ? Rank[stp-1][i+cnt] : -1;
            t[i].pos = i;
        }
        sort(t,t+length,compare);
        int rnk = 0;
        for(int i = 0 ; i<length ; i++)
        {
            if((i > 0) && (t[i-1].firstHalf == t[i].firstHalf && t[i].secondHalf == t[i-1].secondHalf))
                rnk = Rank[stp][t[i-1].pos];
            else
                rnk = i;
            Rank[stp][t[i].pos] = rnk;
        }
    }
    pos = ceil(log(length)/log(2));
    for(int i=0;i<length;i++)
        SA[Rank[pos][i]] = i;
}
int LCP(int i,int j,int n){
    int res = 0;
    if(i==j)
        return n - i;
    for(int stp = ceil(log(n)/log(2)) ; stp>=0 && i < n && j < n ; stp--)
        if(Rank[stp][i] == Rank[stp][j])
        {
            res += 1<<stp;
            i += 1<<stp;
            j += 1<<stp;
        }
    return res;
}
int main(){
	scanf("%s",str);
	scanf("%d",&q);
	len=strlen(str);
	int start=0,end=len-1;
	while(start<end){
		swap(str[start],str[end]);
		start++;
		end--;
	}
	//cout<<str<<endl;
	suffix_array(len);
	while(q--){
		scanf("%d",&d);
		d=len-d;
		printf("%d\n",LCP(0,d,len));	
	}
	return 0;
}	
