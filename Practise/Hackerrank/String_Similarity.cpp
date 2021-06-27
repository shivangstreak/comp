#include <bits/stdc++.h>
using namespace std;
#define MAX 100005
#define PB push_back
#define MP make_pair
#define ll long long int
int Rank[20][MAX];
int SA[MAX];
struct Tuple
{
    int pos;
    int firstHalf,secondHalf;
};
bool compare(const Tuple &a , const Tuple &b)
{
    return a.firstHalf == b.firstHalf ?a.secondHalf < b.secondHalf :a.firstHalf < b.firstHalf;
}
void suffix_array(Tuple t[] , char s[], int length )
{
    int pos = 0;
    for(int i=0;i<length;i++)
        Rank[0][i] = s[i] - 'A';
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
int LCP(int i,int j,int n)
{
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
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
    	memset(SA,0,sizeof(SA));
        char s[MAX];
        scanf("%s",s);
        int n = strlen(s);
        Tuple t[n + 9];
        suffix_array(t,s,n);
      	ll sum=0;
        for(int i=0;i<n;i++){
      //  cout<<LCP(0,i,n)<<endl;
       	      sum+=LCP(0,i,n);
        }
        cout<<sum<<endl;	
    }
    return 0;
}
