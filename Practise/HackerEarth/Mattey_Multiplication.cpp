#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
void ConvertToBinary(ll n,string &str){
        if(n/2!=0){
                ConvertToBinary(n/2,str);
        }
        str+=((n%2)+'0');
}
int main(){
        int t;scanf("%d",&t);
        ll n,m;
        while(t--){
                scanf("%lld%lld",&n,&m);
                string str="";
                ConvertToBinary(m,str);
                ll len=str.size();
                //cout<<str<<endl;
                for(ll i=0;i<len;i++){
                        if(str[i]=='1'){
                                if(i!=0){
                                        printf(" + ");
                                }
                                printf("(%lld<<%lld)",n,len-1-i);
                        }        
                }
                printf("\n");
        }
	return 0;
}	


