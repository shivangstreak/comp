#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
map<int,char>m;
int main(){
        int t;scanf("%d",&t);
        m[1]='m';
        m[2]='a';
        m[3]='n';
        m[4]='k';
        m[0]='u';
        while(t--){
                ll n;scanf("%lld",&n);
                char ch[10005];
                int kk=0;
                while(n>0){
                        int rem=n%5;
                        if(rem==0){
                                ch[kk++]='u';
                                n/=5;
                                n--;
                        }
                        else{
                                ch[kk++]=m[rem];
                                n/=5;
                        }
                }
                ch[kk]='\0';
                string res(ch);
                reverse(res.begin(),res.end());
                cout<<res<<"\n";
        }
	return 0;
}	
